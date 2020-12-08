//############################################################################

#include "DSP2833x_Device.h"// Headerfile Include File
#include "DSP2833x_Examples.h" // Examples Include File
#include "dpram.h"
#include "adc_28335.h"

// Specify LED Toggle Rate 
#define PWM1_TIMER_TBPRD 41825  // ePWM1 Timer Period (LED Toggle 1 sec)
//#define PWM1_TIMER_TBPRD 20926  // ePWM1 Timer Period (LED Toggle .5 sec)
//#define PWM1_TIMER_TBPRD 10463   // ePWM1 Timer Period (LED Toggle .25 sec)

extern volatile struct DATA_DN data_down;

// Prototype statements for functions found within this file.
interrupt void Calculate_Realtime(void);
interrupt void epwm1_timer_isr(void);
void InitEPwmTimer(void);


extern void init_zone6(void);
extern void init_zone7(void);
extern interrupt void local_DINTCH5_ISR(void);
extern void initial_dma_ch5(void);
extern void trig_dma_ch5(void);
extern interrupt void local_DINTCH6_ISR(void);
extern void initial_dma_ch6(void);
extern void trig_dma_ch6(void);
extern void ADC_28335_config(void);
extern interrupt void local_DINTCH4_ISR(void);
extern void Start_Adc_SEQ(void);
extern void initial_dma_ch4(void);
extern void ADC_7656_config(void);
extern void ADC_7656_reset(void);
extern void ADC_7656_start(void);
extern void ADC_7656_read(void);
extern void GPIO_config(void);
extern void phasic_ui_ini(void);
extern void reactive_pw_ini(void);
extern void Reactive_PW_Calcu(void);
extern void event_generate(void);
extern void ovld_check(void);
extern void get_peak(void);
extern void control_out(void);


extern void procces_test(void);//



void main(void){

	InitSysCtrl();

	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;// HSPCLK = SYSCLKOUT/ADC_MODCLK
	EDIS;

	DINT;//Disable Global interrupt INTM
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	EALLOW;	// Allow access to EALLOW protected registers
	PieVectTable.XINT1 = &Calculate_Realtime;//main process in ISR.
	PieVectTable.EPWM1_INT = &epwm1_timer_isr;//debugg process in ISR.
	PieVectTable.DINTCH4 = &local_DINTCH4_ISR;//DMA channel 4 ISR.
	PieVectTable.DINTCH5 = &local_DINTCH5_ISR;//DMA channel 5 ISR.
	PieVectTable.DINTCH6 = &local_DINTCH6_ISR;//DMA channel 6 ISR.
	EDIS;   // Disable access to EALLOW protected registers
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
	IER |= M_INT7;//Enable INT7 (DINTCH4,DINTCH5,DINTCH6 DMA intrrupte). 

	InitEPwmTimer();
	InitAdc();
	ADC_28335_config();
	ADC_7656_config();

   // Configure GPIO32 as output for test.
	EALLOW;
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;
	EDIS;

	DMAInitialize();
	init_zone6();//for dpram and AD7656.
	init_zone7();//for alpha order output.
	initial_dma_ch4();//TCR current measure used.
	initial_dma_ch5();//download data from dpram.
	ADC_7656_reset();
	GPIO_config();

	EINT;//Enable Global interrupt INTM
	ERTM;//Enable Global realtime interrupt DBGM
	EnableInterrupts();

	do{//waiting for lf2407 be ready.
		trig_dma_ch5();//down data from main CPU(TMS320LF2407).
		phasic_ui_ini();//initialize vertical generate array.
		reactive_pw_ini();//initialize reactive power calculation array.
	} while(0x4567 != data_down.f28335_run);
	
	initial_dma_ch6();//upload data to dpram.

	procces_test();//just for testing.




	IER |= M_INT1;//Enable INT1 (.4 XINT1).
//	IER |= M_INT3;//Enable CPU INT3 which is connected to EPWM1 INT.

	for(;;){};//waiting interrupt.

} //end main


/***************************************control functions**************************************/
//execute time:12us.
//interrupt period is 20us.1000 points sample in one wave when 50Hz.
interrupt void Calculate_Realtime(void){

	DINT;//Disable Global interrupt INTM

	ADC_7656_start();//step 1: starting AD conveter.
	get_peak();///**0.28us**/
	Start_Adc_SEQ();/**0.11us**/
	trig_dma_ch5();/**0.66us**///down data from main CPU(TMS320LF2407).
	trig_dma_ch6();/**1.568us**///upload data to main CPU(TMS320LF2407).
	ovld_check();/**0.51us**/
	event_generate();/**0.41us**/
		event_generate();
		event_generate();
		event_generate();//for wait AD conveter time,addition this function.2017.11.23
	/*total time is 3.562us about,and AD conveter period is 3us*/
	ADC_7656_read();//step 2: get AD converter result.
	Reactive_PW_Calcu();/**7.5us**///step 3: calculate reactive power of 3 phase.
	control_out();/**3.2us**///step 4: get alpha value according as nonlinear table,output alpha order.

//	GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;// Toggle LED

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;// Acknowledge this interrupt to get more from group 1
	EINT;//Enable Global interrupt INTM
	//acknowledge DMA interrupt event.

//	asm ("      ESTOP0");//halt
}


/*********************************monitoring functions******************************************/
//for debbug popurse.
interrupt void epwm1_timer_isr(void){

	EPwm1Regs.ETCLR.bit.INT = 1;//Clear INT flag for this timer
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;//Acknowledge this interrupt to receive more interrupts from group 3

	GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;// Toggle LED

	//
	ADC_7656_start();//step 1: starting AD conveter.

	//test programs execute time part.
	//test begin.
	get_peak();
	Start_Adc_SEQ();
	trig_dma_ch5();//down data from main CPU(TMS320LF2407).
	trig_dma_ch6();//upload data to main CPU(TMS320LF2407).
	ovld_check();
	event_generate();
	Reactive_PW_Calcu();//step 3: calculate reactive power of 3 phase.
	control_out();//step 4: get alpha value according as nonlinear table,output alpha order.
	//test end.

	ADC_7656_read();//step 2: get AD converter result.


//	asm ("      ESTOP0");//halt

}


/**/
void InitEPwmTimer(void){

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;// Stop all the TB clocks
	EDIS;

	EPwm1Regs.TBPRD = PWM1_TIMER_TBPRD;//ePWM1 Timer Period 
	EPwm1Regs.TBCTL.bit.CLKDIV = 7;//CLKDIV = /128
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 7;// HSPCLKDIV = /14
	EPwm1Regs.TBCTL.bit.CTRMODE = 0;// Count up
	EPwm1Regs.ETSEL.bit.INTSEL = 1;// Select INT on Zero event
	EPwm1Regs.ETSEL.bit.INTEN = 1;// Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = 1;// Generate INT on 1st event

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;// Start all the timers synced
	EDIS;

	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;//Enable EPWM INT1 in the PIE: Group 3 interrupt 1
}






//end of file




