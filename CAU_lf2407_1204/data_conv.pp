#line 63 "user_io.h"
ioport	unsigned	portf000;


#line 5 "data_conv.c"
unsigned int ua,ub,uc,ia,ib,ic;
unsigned int state_vect;
unsigned int alpha_a,alpha_b,alpha_c;
unsigned int tcr_a,tcr_b,tcr_c;
unsigned int up_a,up_b,up_c,down_a,down_b,down_c;
unsigned int up_a_u,up_b_u,up_c_u,down_a_u,down_b_u,down_c_u;

unsigned int state_reg;
unsigned int cmd_reg_d = 0,cmd_reg_u;
unsigned int offset_a,offset_b,offset_c;

float scale;
float scale_u;
float kp_a,kp_b,kp_c;
float kp_a_u,kp_b_u,kp_c_u;
float ki_a,ki_b,ki_c;
float ki_a_u,ki_b_u,ki_c_u;
float kd_a,kd_b,kd_c;
float kd_a_u,kd_b_u,kd_c_u;
float cond_a,cond_b,cond_c;

extern void delay(unsigned int);


 
void monitor_data(void){

	ua = *((volatile unsigned int *)0xF100);
	delay(10);
	ub = *((volatile unsigned int *)0xF101);
	delay(10);
	uc = *((volatile unsigned int *)0xF102);
	delay(10);
	ia = *((volatile unsigned int *)0xF103);
	delay(10);
	ib = *((volatile unsigned int *)0xF104);
	delay(10);
	ic = *((volatile unsigned int *)0xF105);
	delay(10);
	state_vect = *((volatile unsigned int *)0xF10C);
	delay(10);
	alpha_a = *((volatile unsigned int *)0xF10D);
	delay(10);
	alpha_b = *((volatile unsigned int *)0xF10E);
	delay(10);
	alpha_c = *((volatile unsigned int *)0xF10F);
	delay(10);
	tcr_a = *((volatile unsigned int *)0xF110);
	delay(10);
	tcr_b = *((volatile unsigned int *)0xF111);
	delay(10);
	tcr_c = *((volatile unsigned int *)0xF112);
	delay(10);
	up_a_u = *((volatile unsigned int *)0xF113);
	delay(10);
	up_b_u = *((volatile unsigned int *)0xF114);
	delay(10);
	up_c_u = *((volatile unsigned int *)0xF115);
	delay(10);
	down_a_u = *((volatile unsigned int *)0xF116);
	delay(10);
	down_b_u = *((volatile unsigned int *)0xF117);
	delay(10);
	down_c_u = *((volatile unsigned int *)0xF118);
	delay(10);
	kp_a_u = *((volatile float *)0xF130);
	delay(10);
	kp_b_u = *((volatile float *)0xF132);
	delay(10);
	kp_b_u = *((volatile float *)0xF134);
	delay(10);
	ki_a_u = *((volatile float *)0xF136);
	delay(10);
	ki_b_u = *((volatile float *)0xF138);
	delay(10);
	ki_b_u = *((volatile float *)0xF13A);
	delay(10);
	kd_a_u = *((volatile float *)0xF13C);
	delay(10);
	kd_b_u = *((volatile float *)0xF13E);
	delay(10);
	kd_b_u = *((volatile float *)0xF140);
	delay(10);
	state_reg = *((volatile unsigned int *)0xF119);
	delay(10);
	scale_u = *((volatile float *)0xF142);
	delay(10);
	cond_a = *((volatile float *)0xF144);
	delay(10);
	cond_b = *((volatile float *)0xF146);
	delay(10);
	cond_c = *((volatile float *)0xF148);
}

 
void put_data(void){

	*((volatile unsigned int *)0xF800) = up_a;
	delay(10);
	*((volatile unsigned int *)0xF801) = up_b;
	delay(10);
	*((volatile unsigned int *)0xF802) = up_c;
	delay(10);
	*((volatile unsigned int *)0xF803) = down_a;
	delay(10);
	*((volatile unsigned int *)0xF804) = down_b;
	delay(10);
	*((volatile unsigned int *)0xF805) = down_c;
	delay(10);
	*((volatile float *)0xF840) = kp_a;
	delay(10);
	*((volatile float *)0xF842) = kp_b;
	delay(10);
	*((volatile float *)0xF844) = kp_c;	
	delay(10);
	*((volatile float *)0xF846) = ki_a;
	delay(10);
	*((volatile float *)0xF848) = ki_b;
	delay(10);
	*((volatile float *)0xF84A) = ki_c;
	delay(10);
	*((volatile float *)0xF84C) = kd_a;
	delay(10);
	*((volatile float *)0xF84E) = kd_b;
	delay(10);
	*((volatile float *)0xF850) = kd_c;
	delay(10);
	*((volatile unsigned int *)0xF806) = cmd_reg_d;
	delay(10);
	*((volatile unsigned int *)0xF807) = offset_a;
	delay(10);
	*((volatile unsigned int *)0xF808) = offset_b;
	delay(10);
	*((volatile unsigned int *)0xF809) = offset_c;
	delay(10);
	*((volatile float *)0xF852) = scale;
}


