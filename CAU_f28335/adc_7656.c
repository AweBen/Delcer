/**/
#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_GlobalPrototypes.h"
#include "dpram.h"
#include "adc_7656.h"

#define RMS_CAL_POINT	4000	//10 waves.for RMS caculation.


#pragma DATA_SECTION(adc_7656_result_port,"AD7656_CS");
volatile signed int adc_7656_result_port;


volatile struct UI_ABC ui_abc;
volatile struct UI_PEAK ui_peak;

extern volatile struct DATA_UP data_up;


void get_peak(void);
extern void DSP28x_usDelay(Uint32 Count);


/**/
void ADC_7656_read(void){

	ui_abc.uc = adc_7656_result_port;
	ui_abc.ub = adc_7656_result_port;
	ui_abc.ua = adc_7656_result_port;
	ui_abc.ic = adc_7656_result_port;
	ui_abc.ib = adc_7656_result_port;
	ui_abc.ia = adc_7656_result_port;

	GpioDataRegs.GPADAT.bit.GPIO1 = 0;
}


/**/
void ADC_7656_start(void){

	GpioDataRegs.GPADAT.bit.GPIO1 = 1;
}


/**/
void ADC_7656_config(void){// Specific ADC setup for this example:

	EALLOW;
	//AD START signal.set GPIO_1 to output mode.
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO1 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;//set output mode.
	//AD RESET signal.set GPIO_2 to output mode.
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO2 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;//set output mode.
	EDIS;
}


/**/
void ADC_7656_reset(void){

	GpioDataRegs.GPADAT.bit.GPIO2 = 1;
	DSP28x_usDelay(200);//6.64us
	GpioDataRegs.GPADAT.bit.GPIO2 = 0;

}


/**/
//maxim execute time is 0.28us.fact measure result.
void get_peak(void){

	if(RMS_CAL_POINT > ui_peak.cnt){//
		ui_peak.cnt ++;

		if(ui_abc.ua > ui_peak.ua_peak){
			ui_peak.ua_peak = ui_abc.ua;
		}
		if(ui_abc.ub > ui_peak.ub_peak){
			ui_peak.ub_peak = ui_abc.ub;
		}
		if(ui_abc.uc > ui_peak.uc_peak){
			ui_peak.uc_peak = ui_abc.uc;
		}
	}
	else{//reset maxim value;
		ui_peak.cnt = 0;

		data_up.uab_peak = ui_peak.ua_peak;//uab PEAK.
		ui_peak.ua_peak = 0;
		data_up.ubc_peak = ui_peak.ub_peak;//ubc PEAK.
		ui_peak.ub_peak = 0;
		data_up.uca_peak = ui_peak.uc_peak;//uca PEAK.
		ui_peak.uc_peak = 0;
	}
}





//end of file
