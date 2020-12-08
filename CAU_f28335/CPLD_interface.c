/**/
#include "cpld.h"

#pragma DATA_SECTION(cpld_exchange,"CPLD_VAR");
volatile struct CPLD_EXCHG cpld_exchange;

/****************************Function 1******************************************/
//TCR phase AB overload.
void TCR_AB_Ovld(void){

	GpioDataRegs.GPADAT.bit.GPIO19 = 1;
}

/****************************Function 2******************************************/
//TCR phase BC overload.
void TCR_BC_Ovld(void){

	GpioDataRegs.GPADAT.bit.GPIO18 = 1;
}

/****************************Function 3******************************************/
//TCR phase CA overload.
void TCR_CA_Ovld(void){

	GpioDataRegs.GPADAT.bit.GPIO17 = 1;
}

/****************************Function 4******************************************/
//FC increase.
void FC_increase_doing(void){

	GpioDataRegs.GPADAT.bit.GPIO16 = 1;


}

/****************************Function 5******************************************/
//FC reduce.
void FC_reduce_doing(void){

	GpioDataRegs.GPADAT.bit.GPIO16 = 1;


}






/****************************Function 6******************************************/
// Configure the timing paramaters for Zone 7.
void init_zone7(void){

	EALLOW;
    // Make sure the XINTF clock is enabled
	SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;
	EDIS; 
	// Configure the GPIO for XINTF with a 16-bit data bus
	// This function is in DSP2833x_Xintf.c
	InitXintf16Gpio();

    // All Zones---------------------------------
    // Timing for all zones based on XTIMCLK = SYSCLKOUT 
	EALLOW;
    XintfRegs.XINTCNF2.bit.XTIMCLK = 0;
    // Buffer up to 3 writes
    XintfRegs.XINTCNF2.bit.WRBUFF = 3;
    // XCLKOUT is enabled
    XintfRegs.XINTCNF2.bit.CLKOFF = 0;
    // XCLKOUT = 1/2*XTIMCLK 
    XintfRegs.XINTCNF2.bit.CLKMODE = 1;



    // Zone 7------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING7.bit.XWRLEAD = 1;
    XintfRegs.XTIMING7.bit.XWRACTIVE = 2;
    XintfRegs.XTIMING7.bit.XWRTRAIL = 1;
    // Zone read timing
    XintfRegs.XTIMING7.bit.XRDLEAD = 1;
    XintfRegs.XTIMING7.bit.XRDACTIVE = 3;
    XintfRegs.XTIMING7.bit.XRDTRAIL = 0;
    
    // don't double all Zone read/write lead/active/trail timing 
    XintfRegs.XTIMING7.bit.X2TIMING = 0;
 
    // Zone will not sample XREADY signal  
    XintfRegs.XTIMING7.bit.USEREADY = 0;
    XintfRegs.XTIMING7.bit.READYMODE = 0;
 
    // 1,1 = x16 data bus
    // 0,1 = x32 data bus
    // other values are reserved
    XintfRegs.XTIMING7.bit.XSIZE = 3;
    EDIS; 
   //Force a pipeline flush to ensure that the write to 
   //the last register configured occurs before returning.  
   asm(" RPT #7 || NOP"); 
}


/****************************Function 7******************************************/
/**/
void GPIO_config(void){// Specific ADC setup for this example:

	EALLOW;
	//TCR phase AB overload.
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO19 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;//set output mode.
	//TCR phase BC overload.
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO18 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;//set output mode.
	//TCR phase CA overload.
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO17 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;//set output mode.
	//FC increase.
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO16 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;//set output mode.
	//FC reduce.
	GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;//enable pullup.
	GpioDataRegs.GPADAT.bit.GPIO15 = 0;//load output latch.
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;//GPIOx = GPIOx.
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;//set output mode.

	//PLL ok input.
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;// Enable pullup on GPIO12
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;// GPIO12 = GPIO12
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;// GPIO12 = input
	//RST_n input.
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;// Enable pullup on GPIO13
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;// GPIO13 = GPIO13
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;// GPIO13 = input
	//spare input.
	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;// Enable pullup on GPIO14
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;// GPIO14 = GPIO14
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;// GPIO14 = input

	// Make GPIO9 the input source for XINT1
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;// GPIO9 = GPIO9
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;// GPIO9 = input
	GpioIntRegs.GPIOXINT1SEL.all = 9;// Xint1 connected to GPIO9
	XIntruptRegs.XINT1CR.bit.POLARITY = 0;//Xint1 interrupte generate on falling edge.
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;

	EDIS;
}
//end of file


