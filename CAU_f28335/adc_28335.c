/**/
#include "DSP2833x_Adc.h"
#include "adc_28335.h"
#include "dpram.h"

#define OVLD_CYCLE 1000

extern void TCR_AB_Ovld(void);
extern void TCR_BC_Ovld(void);
extern void TCR_CA_Ovld(void);



struct OVLD_CNT{

	unsigned int a_tcr_ovld_count;
	unsigned int b_tcr_ovld_count;
	unsigned int c_tcr_ovld_count;
};
volatile struct OVLD_CNT ovld_cnt;

extern volatile struct DATA_UP data_up;


void ADC_28335_config(void){// Specific ADC setup for this example:

	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;//sampling window.
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;//16 Mode
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;//SEQ1 intruppt enable.
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;//reset to CONV00.
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ADCINB5;//ADC input channel select.
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ADCINB5;
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ADCINB5;
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ADCINB5;
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = ADCINB5;

	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = ADCINB6;
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = ADCINB6;
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = ADCINB6;
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = ADCINB6;
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = ADCINB6;

	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = ADCINB7;
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = ADCINB7;
	AdcRegs.ADCCHSELSEQ4.bit.CONV12 = ADCINB7;
	AdcRegs.ADCCHSELSEQ4.bit.CONV13 = ADCINB7;
	AdcRegs.ADCCHSELSEQ4.bit.CONV14 = ADCINB7;
	AdcRegs.ADCCHSELSEQ4.bit.CONV15 = ADCINA7;//connect to groud.


	AdcRegs.ADCREFSEL.bit.REF_SEL = 0;

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 15;

}

/**/
//execute time:0.072us
void Start_Adc_SEQ(void){

	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;

}



/*TCR overload checking*/
//execute time:0.698us
void ovld_check(void){
	
	if(data_up.i_tcr_a < data_up.ovld_value){
		ovld_cnt.a_tcr_ovld_count = 0;
	}
	else{
		ovld_cnt.a_tcr_ovld_count ++;
	}
	
	if(data_up.i_tcr_b < data_up.ovld_value){
		ovld_cnt.b_tcr_ovld_count = 0;
	}
	else{
		ovld_cnt.b_tcr_ovld_count ++;
	}
	
	if(data_up.i_tcr_c < data_up.ovld_value){
		ovld_cnt.c_tcr_ovld_count = 0;
	}
	else{
		ovld_cnt.c_tcr_ovld_count ++;
	}
	
	//overload actions,TRIP output and event send out.
	if(ovld_cnt.a_tcr_ovld_count > OVLD_CYCLE){
		data_up.a_ovld = 1;
		TCR_AB_Ovld();
	}

	if(ovld_cnt.b_tcr_ovld_count > OVLD_CYCLE){
		data_up.b_ovld = 1;
		TCR_BC_Ovld();
	}

	if(ovld_cnt.c_tcr_ovld_count > OVLD_CYCLE){
		data_up.c_ovld = 1;
		TCR_CA_Ovld();
	}
}



//end of flie

