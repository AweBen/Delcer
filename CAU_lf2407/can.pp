#line 216 "f2407.h"
ioport unsigned portffff;         
 

ioport unsigned portff0f; 
ioport unsigned port0; 
ioport unsigned port1; 
ioport unsigned port2; 
ioport unsigned port3; 
ioport unsigned port4;   
 
#line 4 "can.c"
union{
	float fvar;
	unsigned int intvar[2];
}conv;

extern int node;
extern unsigned int canr_flag;
extern unsigned int cans_flag;
extern unsigned int state;
extern unsigned int ua,ub,uc,ia,ib,ic;

extern unsigned int alpha_a,alpha_b,alpha_c;
extern unsigned int tcr_a,tcr_b,tcr_c;
extern unsigned int up_a,up_b,up_c;
extern unsigned int down_a,down_b,down_c;
extern unsigned int offset_a,offset_b,offset_c;
extern unsigned int ref_value;
extern float scale;
extern float kp_a,kp_b,kp_c;
extern float ki_a,ki_b,ki_c;
extern float kd_a,kd_b,kd_c;
extern float cond_a,cond_b,cond_c;

extern unsigned int canr[5];
extern unsigned int cans[5];

extern unsigned long gps_time;
extern unsigned long rel_time;
extern unsigned long can_id;

extern void clean_IFR(void);
extern void disable_WD(void);
extern unsigned int avera(unsigned int,unsigned int);


 
long can_isr(unsigned int *canr){

	long id = 0;

	canr[0] = *((volatile int *)0x7204);
	canr[1] = *((volatile int *)0x7205);
	canr[2] = *((volatile int *)0x7206);
	canr[3] = *((volatile int *)0x7207);
	
	id = *((volatile int *)0x7201)&0x1FFF;
	id = id << 16;
	id |= *((volatile int *)0x7200);
	
	if(0x1000 & *((volatile int *)0x7102))
		canr[4] = 1;
	else
		canr[4] = 0;
	*((volatile int *)0x7102)=0x0010;

	clean_IFR();


	return id;	
}

 
void can_send(unsigned int *cans,unsigned long can_id){

	unsigned int wd_var = 10;
	
	disable_WD();
	
	*((volatile int *)0x7100)=0x00;
	
	*((volatile int *)0x7224) = ((cans[0] & 0x0ff00) >> 8) + ((cans[0] & 0x0ff) << 8);
	*((volatile int *)0x7225) = ((cans[1] & 0x0ff00) >> 8) + ((cans[1] & 0x0ff) << 8);	
	*((volatile int *)0x7226) = ((cans[2] & 0x0ff00) >> 8) + ((cans[2] & 0x0ff) << 8);	
	*((volatile int *)0x7227) = ((cans[3] & 0x0ff00) >> 8) + ((cans[3] & 0x0ff) << 8);	
	
	*((volatile int *)0x7221) = 0xC000;
	*((volatile int *)0x7221) |= (can_id >> 16 & 0x1FFF);
	*((volatile int *)0x7220) = can_id & 0x0FFFF;

	*((volatile int *)0x7100)=0x11;

	*((volatile int *)0x7101)=0x40;

	while((0 == (*((volatile int *)0x7101) & 0x04000)) && (0 != wd_var--));

	*((volatile int *)0x7101)=0x4000;
	
}

 
void CAN_Init(void){

	*((volatile int *)0x7100)=0x00;
	*((volatile int *)0x7109)=0xFFFF;
	*((volatile int *)0x710b)=0x9FFF;
	*((volatile int *)0x710c)=0xFFFF;
	
	*((volatile int *)0x7103)=0x1000;
	while((*((volatile int *)0x7107)&0x10)==0);
	*((volatile int *)0x7104)=0x4;
	*((volatile int *)0x7105)=0x11;
	*((volatile int *)0x7103)=*((volatile int *)0x7103)&0xEFFF;
	while(*((volatile int *)0x7107)&0x10);
	*((volatile int *)0x7100)=0x00;
	*((volatile int *)0x7103)=0x0100;
	*((volatile int *)0x7201)=0xDFFF;
	*((volatile int *)0x7200)=0xFFFF;
	*((volatile int *)0x7202)=0x8;
	*((volatile int *)0x7204)=0;
	*((volatile int *)0x7205)=0;
	*((volatile int *)0x7206)=0;
	*((volatile int *)0x7207)=0;
	*((volatile int *)0x7221)=0xDFFF;
	*((volatile int *)0x7220)=0xFFFF;
	*((volatile int *)0x7222)=0x08;
	*((volatile int *)0x7224)=0;
	*((volatile int *)0x7225)=0;
	*((volatile int *)0x7226)=0;
	*((volatile int *)0x7227)=0;
	*((volatile int *)0x7103)=0x0480;
	*((volatile int *)0x7100)=0x11;
	*((volatile int *)0x710a)=0xE1FF;
	*((volatile int *)0x7109)=0xFFFF;
}

 
void clear_rcan(void){

	unsigned int temp;
	
	temp = *((volatile int *)0x7109);
	*((volatile int *)0x7109) =temp;
}






 

void can_server(void){

	can_id = can_isr(canr);
	if(0 == canr[4]){
		switch(can_id & 0xFFFF0000){
			case 0x120000:
			
				gps_time = canr[0];
				gps_time = gps_time << 8;
				gps_time = gps_time | canr[1];
				gps_time = gps_time << 8;
				gps_time = gps_time | canr[2];
				gps_time = gps_time << 8;
				gps_time = gps_time | canr[3];
				
				break;
				
				default: break;
		}
	}
	else if(node == (can_id & 0x0F)){
		switch(0xFFFFFF00 & can_id){
			case 0x220100:
				cans[0] = 0x01;
				cans[1] = state;
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221000:
				conv.fvar = cond_a;
				cans[0] = ua;
				cans[1] = ia;
				cans[2] = conv.intvar[1];
				cans[3] = conv.intvar[0];
				break;
			case 0x221100:
				conv.fvar = cond_b;
				cans[0] = ub;
				cans[1] = ib;
				cans[2] = conv.intvar[1];
				cans[3] = conv.intvar[0];
				break;
			case 0x221200:
				conv.fvar = cond_c;
				cans[0] = uc;
				cans[1] = ic;
				cans[2] = conv.intvar[1];
				cans[3] = conv.intvar[0];
				break;
			case 0x221300:
				cans[0] = alpha_a;
				cans[1] = tcr_a;
				cans[2] = up_a;
				cans[3] = down_a;
				break;
			case 0x221400:
				cans[0] = alpha_b;
				cans[1] = tcr_b;
				cans[2] = up_b;
				cans[3] = down_b;
				break;
			case 0x221500:
				cans[0] = alpha_c;
				cans[1] = tcr_c;
				cans[2] = up_c;
				cans[3] = down_c;
				break;
			case 0x221600:
				cans[0] = offset_a;
				cans[1] = offset_b;
				cans[2] = offset_c;
				cans[3] = 0;
				break;
			case 0x221700:
				conv.fvar = kp_a;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221800:
				conv.fvar = kp_b;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221900:
				conv.fvar = kp_c;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;	
			case 0x221A00:
				conv.fvar = ki_a;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221B00:
				conv.fvar = ki_b;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221C00:
				conv.fvar = ki_c;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;				
			case 0x221D00:
				conv.fvar = kd_a;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221E00:
				conv.fvar = kd_b;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x221F00:
				conv.fvar = kd_c;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x222000:
				conv.fvar = scale;
				cans[0] = conv.intvar[1];
				cans[1] = conv.intvar[0];
				cans[2] = 0;
				cans[3] = 0;
				break;
			case 0x222100:
				cans[0] = node;
				cans[1] = ref_value;
				cans[2] = 0;
				cans[3] = 0;
				break;
			default: break;
		}
		cans_flag = 1;
		can_send(cans,can_id);
	}
}



