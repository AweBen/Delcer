/**/
#include "adc_7656.h"


volatile unsigned int addr_cnt;

volatile float phasic_ua[QUARTER_SIZE];
volatile float phasic_ub[QUARTER_SIZE];
volatile float phasic_uc[QUARTER_SIZE];
volatile float phasic_ia[QUARTER_SIZE];
volatile float phasic_ib[QUARTER_SIZE];
volatile float phasic_ic[QUARTER_SIZE];

volatile float *pt_ua;
volatile float *pt_ub;
volatile float *pt_uc;
volatile float *pt_ia;
volatile float *pt_ib;
volatile float *pt_ic;

volatile struct UI_VECT_ABC ui_vector_6abc;

extern volatile struct UI_ABC ui_abc;


extern float filter_ua(float);
extern float filter_ub(float);
extern float filter_uc(float);
extern float filter_ia(float);
extern float filter_ib(float);
extern float filter_ic(float);



/**/
//execute time:94.4us with filter.
//execute time:4.14us without filter.
//input one AC signal,output two AC signals with verticalble.
//step 1: filter AC signal;
//step 2: generate 2 AC signals.
//be insure QUARTER_SIZE point is 1/4 wave.
void vertical_abc(void){

	if(addr_cnt < QUARTER_SIZE - 1){

		ui_vector_6abc.ua_n = *pt_ua;
		*pt_ua = (float)ui_abc.ua;//filter_ua(ui_abc.ua);//ua input.
		ui_vector_6abc.ua_p = *pt_ua;

		ui_vector_6abc.ub_n = *pt_ub;
		*pt_ub = (float)ui_abc.ub;//filter_ub(ui_abc.ub);//ub input.
		ui_vector_6abc.ub_p = *pt_ub;

		ui_vector_6abc.uc_n = *pt_uc;
		*pt_uc = (float)ui_abc.uc;//filter_uc(ui_abc.uc);//uc input.
		ui_vector_6abc.uc_p = *pt_uc;

		ui_vector_6abc.ia_n = *pt_ia;
		*pt_ia = (float)ui_abc.ia;//filter_ia(ui_abc.ia);//ia input.
		ui_vector_6abc.ia_p = *pt_ia;

		ui_vector_6abc.ib_n = *pt_ib;
		*pt_ib = (float)ui_abc.ib;//filter_ib(ui_abc.ib);//ib input.
		ui_vector_6abc.ib_p = *pt_ib;

		ui_vector_6abc.ic_n = *pt_ic;
		*pt_ic = (float)ui_abc.ic;//filter_ic(ui_abc.ic);//ic input.
		ui_vector_6abc.ic_p = *pt_ic;

		addr_cnt ++;//loop point application.
		pt_ua ++;//loop point application.
		pt_ub ++;//loop point application.
		pt_uc ++;//loop point application.
		pt_ia ++;//loop point application.
		pt_ib ++;//loop point application.
		pt_ic ++;//loop point application.
	}
	else{

		ui_vector_6abc.ua_n = *pt_ua;
		*pt_ua = (float)ui_abc.ua;//filter_ua(ui_abc.ua);//ua input.
		ui_vector_6abc.ua_p = *pt_ua;

		ui_vector_6abc.ub_n = *pt_ub;
		*pt_ub = (float)ui_abc.ub;//filter_ub(ui_abc.ub);//ub input.
		ui_vector_6abc.ub_p = *pt_ub;

		ui_vector_6abc.uc_n = *pt_uc;
		*pt_uc = (float)ui_abc.uc;//filter_uc(ui_abc.uc);//uc input.
		ui_vector_6abc.uc_p = *pt_uc;

		ui_vector_6abc.ia_n = *pt_ia;
		*pt_ia = (float)ui_abc.ia;//filter_ia(ui_abc.ia);//ia input.
		ui_vector_6abc.ia_p = *pt_ia;

		ui_vector_6abc.ib_n = *pt_ib;
		*pt_ib = (float)ui_abc.ib;//filter_ib(ui_abc.ib);//ib input.
		ui_vector_6abc.ib_p = *pt_ib;

		ui_vector_6abc.ic_n = *pt_ic;
		*pt_ic = (float)ui_abc.ic;//filter_ic(ui_abc.ic);//ic input.
		ui_vector_6abc.ic_p = *pt_ic;

		addr_cnt = 0;//loop point application.
		pt_ua = &phasic_ua[0];//loop point application.
		pt_ub = &phasic_ub[0];//loop point application.
		pt_uc = &phasic_uc[0];//loop point application.
		pt_ia = &phasic_ia[0];//loop point application.
		pt_ib = &phasic_ib[0];//loop point application.
		pt_ic = &phasic_ic[0];//loop point application.
	}
}


/*initialize phasic array*/
void phasic_ui_ini(void){

	unsigned int i;

	for(i = 0;i < QUARTER_SIZE;i ++){
		phasic_ua[i] = 0;
		phasic_ub[i] = 0;
		phasic_uc[i] = 0;
		phasic_ia[i] = 0;
		phasic_ib[i] = 0;
		phasic_ic[i] = 0;
	}

	addr_cnt = 0;
	pt_ua = &phasic_ua[0];
	pt_ub = &phasic_ub[0];
	pt_uc = &phasic_uc[0];
	pt_ia = &phasic_ia[0];
	pt_ib = &phasic_ib[0];
	pt_ic = &phasic_ic[0];
}

/*just for testing prupose.*/
void procces_test(void){



}


//end of file.



