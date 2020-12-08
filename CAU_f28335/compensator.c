/*caculate compensator*/
#include "math.h"
#include "float.h"
#include "adc_7656.h"
#include "dpram.h"

volatile unsigned int integral_cnt;

volatile signed long integral_rpw_a[HALF_HITS];
volatile signed long integral_rpw_b[HALF_HITS];
volatile signed long integral_rpw_c[HALF_HITS];

volatile signed long *pt_integral_a;
volatile signed long *pt_integral_b;
volatile signed long *pt_integral_c;

volatile float cond_a,cond_b,cond_c;
volatile signed long sum_a,sum_b,sum_c;

float calcu_a(void);
float calcu_b(void);
float calcu_c(void);

extern volatile struct UI_VECT_ABC ui_vector_6abc;
extern volatile struct DATA_DN data_down;

extern void vertical_abc(void);

/*initialize reactive power array*/
void reactive_pw_ini(void){

	unsigned int i;

	cond_a = 0.0;
	cond_b = 0.0;
	cond_c = 0.0;
	sum_a = 0;
	sum_b = 0;
	sum_c = 0;

	for(i = 0;i < HALF_HITS;i ++){
		integral_rpw_a[i] = 0;
		integral_rpw_b[i] = 0;
		integral_rpw_c[i] = 0;
	}

	integral_cnt = 0;
	pt_integral_a = &integral_rpw_a[0];
	pt_integral_b = &integral_rpw_b[0];
	pt_integral_c = &integral_rpw_c[0];
}


/**********************Calling it in interrupt servce progress***********************/
//execute time:128us with filter.
//execute time:35.4us without filter.
//reactive power calculate funciton.
//caculate conductance based on ua_p,ua_n... ,then output conductance of 3 phase.
//How to use?
//Call this function after read the AD7656.
void Reactive_PW_Calcu(void){

	signed long erro_a,erro_b,erro_c;

	vertical_abc();//get 6 set vertical vector.

	erro_a = *pt_integral_a;
	erro_b = *pt_integral_b;
	erro_c = *pt_integral_c;

	if(integral_cnt < HALF_HITS - 1){

		*pt_integral_a = (signed long) (10000.0 * calcu_a());//input.
		*pt_integral_b = (signed long) (10000.0 * calcu_b());//input.
		*pt_integral_c = (signed long) (10000.0 * calcu_c());//input.

		erro_a = *pt_integral_a - erro_a;
		erro_b = *pt_integral_b - erro_b;
		erro_c = *pt_integral_c - erro_c;

		integral_cnt ++;//loop point application.
		pt_integral_a ++;//loop point application.
		pt_integral_b ++;
		pt_integral_c ++;

	}
	else{

		*pt_integral_a = (signed long) (10000.0 * calcu_a());//input.
		*pt_integral_b = (signed long) (10000.0 * calcu_b());//input.
		*pt_integral_c = (signed long) (10000.0 * calcu_c());//input.

		erro_a = *pt_integral_a - erro_a;
		erro_b = *pt_integral_b - erro_b;
		erro_c = *pt_integral_c - erro_c;

		integral_cnt = 0;//loop point application.
		pt_integral_a = &integral_rpw_a[0];//loop point application.
		pt_integral_b = &integral_rpw_b[0];//loop point application.
		pt_integral_c = &integral_rpw_c[0];//loop point application.
	}

	sum_a += erro_a;
	sum_b += erro_b;
	sum_c += erro_c;

	cond_a = data_down.scale * (0.0001 * (float)sum_a);
	cond_b = data_down.scale * (0.0001 * (float)sum_b);
	cond_c = data_down.scale * (0.0001 * (float)sum_c);
}


/*phase A compensator caculate functions*/
//execute time:
float calcu_a(void){

//	float k;
	
/*	k = (uc_p*ia_p
			+ uc_n*ia_n
			- ub_p*ib_p
			- ub_n*ib_n) * scale;*/

	return((ui_vector_6abc.ub_p * ui_vector_6abc.ib_p
			+ ui_vector_6abc.ub_n * ui_vector_6abc.ib_n
			+ ui_vector_6abc.uc_p * ui_vector_6abc.ia_p
			+ ui_vector_6abc.uc_n * ui_vector_6abc.ia_n
			/*+ k*/)
			/(ui_vector_6abc.ua_p * ui_vector_6abc.ua_p
			 + ui_vector_6abc.ua_n * ui_vector_6abc.ua_n));
}

/*phase B compensator caculate functions*/
//execute time:
float calcu_b(void){

//	float k;
	
/*	k = (ua_p*ib_p
			+ ua_n*ib_n
			- uc_p*ic_p
			- uc_n*ic_n) * scale;*/

	return((ui_vector_6abc.uc_p * ui_vector_6abc.ic_p
			+ ui_vector_6abc.uc_n * ui_vector_6abc.ic_n
			+ ui_vector_6abc.ua_p * ui_vector_6abc.ib_p
			+ ui_vector_6abc.ua_n * ui_vector_6abc.ib_n
			/*+ k*/)
			/(ui_vector_6abc.ub_p * ui_vector_6abc.ub_p
			 + ui_vector_6abc.ub_n * ui_vector_6abc.ub_n));
}

/*phase C compensator caculate functions*/
//execute time:
float calcu_c(void){

//	float k;
	
/*	k = (ub_p*ic_p
			+ ub_n*ic_n
			- ua_p*ia_p
			- ua_n*ia_n) * scale;*/

	return((ui_vector_6abc.ua_p * ui_vector_6abc.ia_p
			+ ui_vector_6abc.ua_n * ui_vector_6abc.ia_n
			+ ui_vector_6abc.ub_p * ui_vector_6abc.ic_p
			+ ui_vector_6abc.ub_n * ui_vector_6abc.ic_n
			/*+ k*/)
			/(ui_vector_6abc.uc_p * ui_vector_6abc.uc_p
			 + ui_vector_6abc.uc_n * ui_vector_6abc.uc_n));
}






/*end of file*/


