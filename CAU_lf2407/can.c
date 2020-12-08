//CAN bus emission function
#include "f2407.h"
#include "dpram.h"


union{
	float fvar;
	unsigned int intvar[2];
}conv;

extern int node;
extern unsigned int canr_flag;
extern unsigned int cans_flag;
extern unsigned int state;
extern unsigned int ua_rms,ub_rms,uc_rms,ia_rms,ib_rms,ic_rms;
extern unsigned int ua_rms,ub_rms,uc_rms,ia_rms,ib_rms,ic_rms;

extern unsigned int alpha_a,alpha_b,alpha_c;

extern unsigned int up_a,up_b,up_c;
extern unsigned int down_a,down_b,down_c;
extern unsigned int basisa_int,basisb_int,basisc_int;
extern unsigned int ref_value;


//extern float cond_a,cond_b,cond_c;

extern unsigned int canr[5];
extern unsigned int cans[5];

extern volatile struct DATA_UP moni_data;
extern volatile struct DATA_DN order_data;

extern unsigned long gps_time;
extern unsigned long rel_time;
extern unsigned long can_id;

extern void clean_IFR(void);
extern void disable_WD(void);
extern unsigned int avera(unsigned int,unsigned int);


/*can receiver use mailbox0*/
long can_isr(unsigned int *canr){

	long id = 0;

	canr[0] = CANMBX0A;
	canr[1] = CANMBX0B;
	canr[2] = CANMBX0C;
	canr[3] = CANMBX0D;
	
	id = CANMSGID0H & 0x1FFF;//get ID
	id = id << 16;
	id |= CANMSGID0L;
	
	if(0x1000 & CANRCR){//is remote frame
		canr[4] = 1;
	}
	else{//is data frame
		canr[4] = 0;
	}
	CANRCR=0x1010;//clear RFP0 and RMP0(message receive hung bit of mailbox0)

	clean_IFR();
//	int_enable();

	return id;	
}

/*can emmiter use mailbox4*/
void can_send(unsigned int *cans,unsigned long can_id){

	unsigned int wd_var = 10;
	
	disable_WD();
	
	CANMDER=0x00;
	
	CANMBX4A = ((cans[0] & 0x0ff00) >> 8) + ((cans[0] & 0x0ff) << 8);
	CANMBX4B = ((cans[1] & 0x0ff00) >> 8) + ((cans[1] & 0x0ff) << 8);	
	CANMBX4C = ((cans[2] & 0x0ff00) >> 8) + ((cans[2] & 0x0ff) << 8);	
	CANMBX4D = ((cans[3] & 0x0ff00) >> 8) + ((cans[3] & 0x0ff) << 8);	
	
	CANMSGID4H = 0xC000;
	CANMSGID4H |= (can_id >> 16 & 0x1FFF);
	CANMSGID4L = can_id & 0x0FFFF;

	CANMDER=0x11;

	CANTCR=0x40;//emmiter 4# mailbox request

	while((0 == (CANTCR & 0x04000)) && (0 != wd_var--));//waitting for 4# mailbox emmiter finish

	CANTCR=0x4000;//clear TA4
	
}

/*CAN modulor initializtion*/
void CAN_Init(void){

	CANMDER=0x00;//inhibit all mailbox
	CANIFR=0xFFFF;//
	CANLAM0H=0x9FFF;//set mask register for mailbox0&1
	CANLAM0L=0xFFFF;
	
	CANMCR=0x1000;//write BCR request
	while((CANGSR&0x10)==0);//waiting for BCR write enable
	CANBCR2=0x4;//BRP:4
	CANBCR1=0x11;//TSEG2:1 TSEG1:2 SAM:0 SJW:0 SBG:0
	CANMCR=CANMCR&0xEFFF;//end of BCR write operation
	while(CANGSR&0x10);//waiting for BCR write disable
	CANMDER=0x00;//inhibit all mailbox
	CANMCR=0x0100;//DSP request data operation
	CANMSGID0H=0xDFFF;//IDE=1:2.0B AME=1:use mask code AAM=0:inhibit acknowledge remove frame
	CANMSGID0L=0xFFFF;//ID=0x1FFF FFFF
	CANMSGCTRL0=0x8;//data length is 8
	CANMBX0A=0;//clear data of mailbox0
	CANMBX0B=0;
	CANMBX0C=0;
	CANMBX0D=0;
	CANMSGID4H=0xDFFF;
	CANMSGID4L=0xFFFF;
	CANMSGCTRL4=0x08;
	CANMBX4A=0;
	CANMBX4B=0;
	CANMBX4C=0;
	CANMBX4D=0;
	CANMCR=0x0480;//DBO=1:data sequence 0~7 ABO=1:resume BUS aotu
	CANMDER=0x11;//mailbox 0 is receiver,mailbox 4 is emmiter
	CANIMR=0xE1FF;//mailbox 4&0 interrupt enable
	CANIFR=0xFFFF;
}

/*clear CAN receive interrupt falg*/
void clear_rcan(void){

	unsigned int temp;
	
	temp = CANIFR;
	CANIFR =temp;
}


/*history event server*/
//all history events send out one by one each fixed time
void can_server(void){

	can_id = can_isr(canr);
	if(node == (can_id & 0x0F)){//node is right
		if(0 == canr[4]){//data frame
			switch(can_id & 0xFFFFFF00){
				case 0x120000://GPS time data
					gps_time = canr[0];
					gps_time = gps_time << 8;
					gps_time = gps_time | canr[1];
					gps_time = gps_time << 8;
					gps_time = gps_time | canr[2];
					gps_time = gps_time << 8;
					gps_time = gps_time | canr[3];
					break;
				case 0x220100://mode set
					order_data.contrl_word = canr[0];
					break;
				case 0x220200://AB TCR valve susceptance manual input
					order_data.manual_Ba = (float)canr[0];
					break;
				case 0x220300://BC TCR valve susceptance manual input
					order_data.manual_Bb = (float)canr[0];
					break;
				case 0x220400://CA TCR valve susceptance manual input
					order_data.manual_Bc = (float)canr[0];
					break;

				default: break;
			}//switch end
		}
		else{//remote frame
			switch(0xFFFFFF00 & can_id){
				case 0x220100://vcp state answer
					cans[0] = 0x01;
					cans[1] = state;
					cans[2] = 0;
					cans[3] = 0;
					break;
				case 0x221000://voltage & status
					cans[0] = moni_data.uab_peak;
					cans[1] = moni_data.ubc_peak;
					cans[2] = moni_data.uca_peak;
					cans[3] = state;
					break;
				case 0x221100://current
					cans[0] = moni_data.ia_peak;
					cans[1] = moni_data.ib_peak;
					cans[2] = moni_data.ic_peak;
					cans[3] = 0;
					break;
				case 0x221200://TCR current
					cans[0] = moni_data.i_tcr_a;
					cans[1] = moni_data.i_tcr_b;
					cans[2] = moni_data.i_tcr_c;
					cans[3] = 0;
					break;
				case 0x221300://alpha
					cans[0] = alpha_a;
					cans[1] = alpha_b;
					cans[2] = alpha_c;
					cans[3] = 0;
					break;
				case 0x221400://AB reactive power & basis
					conv.fvar = moni_data.cond_a;
					cans[0] = conv.intvar[1];
					cans[1] = conv.intvar[0];
					conv.fvar = (float)order_data.basisa;
					cans[2] = conv.intvar[1];
					cans[3] = conv.intvar[0];
					break;
				case 0x221500://BC reactive power & basis
					conv.fvar = moni_data.cond_b;
					cans[0] = conv.intvar[1];
					cans[1] = conv.intvar[0];
					conv.fvar = (float)order_data.basisb;
					cans[2] = conv.intvar[1];
					cans[3] = conv.intvar[0];
					break;
				case 0x221600://CA reactive power & basis
					conv.fvar = moni_data.cond_c;
					cans[0] = conv.intvar[1];
					cans[1] = conv.intvar[0];
					conv.fvar = (float)order_data.basisc;
					cans[2] = conv.intvar[1];
					cans[3] = conv.intvar[0];
					break;
				case 0x221700://mode indicate
					cans[0] = moni_data.state_vect;
					cans[1] = 0;
					cans[2] = 0;
					cans[3] = 0;
					break;
				case 0x221800://AB susceptance manual input
					conv.fvar = order_data.manual_Ba;
					cans[0] = conv.intvar[1];
					cans[1] = conv.intvar[0];
					break;
				case 0x221900://BC susceptance manual input
					conv.fvar = order_data.manual_Bb;
					cans[0] = conv.intvar[1];
					cans[1] = conv.intvar[0];
					break;
				case 0x221A00://CA susceptance manual input
					conv.fvar = order_data.manual_Bc;
					cans[0] = conv.intvar[1];
					cans[1] = conv.intvar[0];
					break;

				default: break;
			}
			cans_flag = 1;
			can_send(cans,can_id);
		}//end remote frame echo
	}//end node pass
}

//end file

