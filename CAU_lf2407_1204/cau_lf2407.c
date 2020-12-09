/***********************************************************************
  Copyright (C), 2008-2009.
  File name:vcp.c
  Author:Gan Chen
  Version:V1.0
  Date:2009.06.29
  Description:vcp main control function.
  History:        

************************************************************************/
#include "f2407.h"
#include "cau_lf2407.h"
#include "dpram.h"


unsigned int node = 0;//
unsigned int time_step = 0;
unsigned int state;
unsigned int canr_flicke_times = 0;
unsigned int cans_flicke_times = 0;
unsigned int led = 0xFFFF;
unsigned int canr_flag = 0;
unsigned int cans_flag = 0;
unsigned int run_flag = 1;
unsigned int cans_led_previous = 1;
unsigned int canr_led_previous = 1;
unsigned int canr[5];
unsigned int cans[5];
unsigned int mon_cmd = 0;
unsigned int mon_disp_flag = 0;
unsigned int mon_toggle = 0;

unsigned long rel_time = 0;
unsigned long can_id = 0;
unsigned long gps_time = 0;

extern volatile struct DATA_DN order_data;
extern volatile struct DATA_DN_NEW order_data_new;
extern unsigned int up_a,up_b,up_c;
extern unsigned int down_a,down_b,down_c;
extern unsigned int basisa_int,basisb_int,basisc_int;


/*function declear*/
void task_executive(void);
extern void sci_server(void);
extern void clear_rcan(void);
extern void can_server(void);
extern unsigned int read_s(void);
extern unsigned int rd_word(unsigned int);
extern float rd_float(unsigned int);
extern void eeprom_ini(void);
extern void IO_Init(void);
extern void SCI_INIT(void);
extern void LED_IO(unsigned int,unsigned int);
extern void CAN_Init(void);
extern void can_send(unsigned int *cans,unsigned long can_id);
extern void monitor_data(void);
extern void put_data(void);
extern void switch_out(void);
extern void serieal_logo(void);
extern void mon_disp(void);

/*function define*/
/*disable all interrupt*/  
void inline int_dis(void){

	asm(" setc INTM");//close interrupt enable
	asm(" setc SXM");//data will expond before input CALU
}
   
/*intrrupt allow*/
void inline int_enable(void){

	asm(" clrc INTM"); 
} 

/*clear int2,int3,int5*/
void clean_IFR(void){

	IFR = 0xFFFF;
}

/*disable WDT*/
void disable_WD(void){

	WDCR = 0x0E8;//
}

/*initiazation WD*/
void wd_ini(void){

	WDCR = 0x0AA;//8.7 ms
}

void inline kick_dog(void){

	WDKEY = 0x55;
	WDKEY = 0xAA;
} 

/*delay*/
void delay(unsigned int count){

	while(count--);
	
}

/********************GISR START*************************************/

void interrupt nothing(void){

   int_enable();
   return;
}

void interrupt int5_server(void){

	switch(PIVR){
	
		case 6://SCI receive interrupt with low priority
			int_enable();
			sci_server();
			break;

		case 64://can interrupt with low priority
			clear_rcan();//clear CAN receive interrupt flag
			int_enable();
			canr_flag = 1;
			can_server();
			break;
			
		default: break;
	}
	
	return;
}

void interrupt int2_server(void){

	switch(PIVR){
	
		case 39://
			T1CNT = 0x00;
			EVAIFRA = 0x0080;//clear the T1PINT FLAG bit	

			rel_time++;
			task_executive();//main body of task.
			break;
		default: break;
	}
	
	int_enable();
	return;
}

void interrupt int1_server(void){

	int temp;

	switch(PIVR){
	
		case 1://GPS interrupte
			temp = XINT1CR;
			XINT1CR = temp;//clear the XINT1 flag
			
			rel_time = gps_time;
			
			break;
		
		default: break;
	}
	
	int_enable();
	return;
}

/********************GISR END***************************************/

/********************INI START**************************************/
/*timer1 initialize*/
void timer1int(void){

	EVAIMRA = 0x0080;//T1PINT ENABLE
	EVAIFRA = 0x0080;//clear the T1PINT bit
	T1CON   = 0x140C;//counter increase
	T1PER   = 0x494A;//GP Timer 1 period register,same as T1PR.set 10ms.
	T1CNT   = 0x00;
}

/*varalbe inilail*/
void var_ini(void){
	
	unsigned int i;
	
	for(i=0;i<5;i++){
		canr[i] = 0;
		cans[i] = 0;
	}
	
	mon_cmd = 0;//monitor varible flag
	mon_disp_flag = 0;//monitor function in progress flag
	order_data.contrl_word = 0;	//mode
	order_data.rsvd1 = 0;
	order_data.rsvd2 = 0;
	order_data.rsvd3 = 0;
	order_data.f28335_run = 0x4567;	//Slaver CPU runing command word
	order_data.manual_Ba = 0.0;
	order_data.manual_Bb = 0.0;
	order_data.manual_Bc = 0.0;

	up_a = rd_word(UP_A_ADDR);
	up_b = rd_word(UP_B_ADDR);
	up_c = rd_word(UP_C_ADDR);
	down_a = rd_word(DOWN_A_ADDR);
	down_b = rd_word(DOWN_B_ADDR);
	down_c = rd_word(DOWN_C_ADDR);	
	order_data.kpa = rd_float(P_A_ADDR);
	order_data.kpb = rd_float(P_B_ADDR);
	order_data.kpc = rd_float(P_C_ADDR);
	order_data.kia = rd_float(I_A_ADDR);
	order_data.kib = rd_float(I_B_ADDR);
	order_data.kic = rd_float(I_C_ADDR);
	order_data.kda = rd_float(D_A_ADDR);
	order_data.kdb = rd_float(D_B_ADDR);
	order_data.kdc = rd_float(D_C_ADDR);
	basisa_int = rd_word(OFFSET_A_ADDR);
	basisb_int = rd_word(OFFSET_B_ADDR);
	basisc_int = rd_word(OFFSET_C_ADDR);
	order_data.scale = rd_float(SCALE_ADDR);
	order_data.ovld_value = rd_word(LIMEN_ADDR);
	node = rd_word(NODE_ADDR);

	order_data.basisa = (float)basisa_int;
	order_data.basisb = (float)basisb_int;
	order_data.basisc = (float)basisc_int;
}

/********************INI END****************************************/  
/*runing LED indication funtion,period=1s*/
void runing_led(void){

	if(run_flag){//send alive message per one secend
   		run_flag = 0;
	   	can_id = (0x8100000+node);//CAN alive message.
   		cans[0] = 0;
   		cans[1] = 0;
   		cans[2] = 0;
   		cans[3] = 0;
		can_send(cans,can_id);
		cans_flag = 1;
			
		led = RUN_LED_ON;
		LED_IO(led,1);
   	}
   	else{
   		run_flag = 1;
   		led = RUN_LED_OFF;
		LED_IO(led,0);
   	}
}

/*CAN receiv & emit LED indication,peroid= 200ms*/
void can_indication_led(void){

	if(cans_flag){
		if(cans_led_previous){
			cans_led_previous = 0;
			led = CANS_LED_ON;
			LED_IO(led,1);
		}
		else{
			cans_led_previous = 1;
			led = CANS_LED_OFF;
			LED_IO(led,0);
		}

		if(FLICKE_TIMES <= cans_flicke_times++){
			cans_led_previous = 1;
			cans_flicke_times = 0;
			cans_flag = 0;
		}
	}

	if(canr_flag){
		if(canr_led_previous){
			canr_led_previous = 0;
			led = CANR_LED_ON;
			LED_IO(led,1);
		}
		else{
			canr_led_previous = 1;
			led = CANR_LED_OFF;
			LED_IO(led,0);
		}

		if(FLICKE_TIMES <= canr_flicke_times++){
			canr_led_previous = 1;
			canr_flicke_times = 0;
			canr_flag = 0;
		}
	}
}

/*main function*/
void main(void){
	
	asm(" setc SXM");
	asm(" clrc OVM");//
	asm(" clrc CNF");//set B0 as data
	int_dis();
	SCSR1 = 0x83FF;//clk x 2
	IMR = 0x0013;//enable INT5 INT2 INT1
	XINT1CR = 0x0001;//enable XINT1 with high priority,it be used for time synchronization.
	
	disable_WD();
	
	CAN_Init();
    SCI_INIT();
    timer1int();
    IO_Init();
    eeprom_ini();
    var_ini();
//	wd_ini();//8.7 ms
	
	T1CON = T1CON | 0x0040;//strat T1
	IFR = 0xFFFF;
	int_enable();//interrupt enable
//	kick_dog();

	while(1){

		if(1 == mon_toggle){
			if((1 == mon_cmd)&&(0 == mon_disp_flag)){
				mon_disp_flag = 1;//monitor function in progress
				mon_disp();
			}
		}
		else{
			mon_disp_flag = 0;//monitor precess must be finished
		}

//		kick_dog();
	}
}//end main

/*task executive,it based on the 10ms interrupt refence*/
//used varible:
//rel_time base	10ms
//
void task_executive(void){

	//0,5,10,15,20,25,30...
	if(0== (rel_time % 5)){//course 0, 50ms event.
		can_indication_led();//communication led flick.
	}

	//9,19,29,39,49,59...
	else if(0 == ((rel_time + 1) % 10)){//course 1, 100ms event.
		switch_out();//CAN load aotu.
	}

	//8,18,28,38,48,58...
	else if(0 == ((rel_time + 2) % 10)){//course 2, 100ms event.
		monitor_data();//upload data form dpram.
	}

	//7,17,27,37,47,57...
	else if(0 == ((rel_time + 3) % 10)){//course 3, 100ms event.
		put_data();//download data to dpram.
	}

	//6,16,26,36,46,56...
	else if(0 == ((rel_time + 4) % 10)){//course 4, 100ms event.
		state = read_s();
	}

	//44,94,144,194,244...
	else if(0 == ((rel_time + 6) % 50)){//course 5, 500ms event.
		if(0 == mon_toggle){
			mon_toggle = 1;
		}
		else{
			mon_toggle = 0;
		}
/*		if((1 == mon_cmd)&&(0 == mon_disp_flag)){
			mon_disp_flag = 1;//monitor program start
			mon_disp();
			mon_disp_flag = 0;//monitor program end
		}*/
	}

	//91,191,291,391,491,591...
	else if(0 == ((rel_time + 9) % 100)){//course 9, 1s event.
		runing_led();
	}

}

//end file