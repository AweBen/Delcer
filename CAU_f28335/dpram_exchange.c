/**/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_GlobalPrototypes.h"
#include "DSP2833x_Dma_defines.h"
#include "dpram.h"
#include "adc_28335.h"
#include "cpld.h"



#define BUF_SIZE_DN	43//receive buffer size, 44-1 = 43

#pragma DATA_SECTION(data_down,"DMARAMDN");
#pragma DATA_SECTION(dpram_down_dma,"DPRAM_DN_DATA");
#pragma DATA_SECTION(sem1_port,"SEM1");

volatile struct DATA_DN data_down;
volatile unsigned int dpram_down_dma[BUF_SIZE_DN];
volatile unsigned int sem1_port;
volatile unsigned int *DMACH5Dest;
volatile unsigned int *DMACH5Source;



#define BUF_SIZE_UP 68//send buffer size, 69-1 = 68

#pragma DATA_SECTION(data_up,"DMARAMUP");
#pragma DATA_SECTION(dpram_up_dma,"DPRAM_UP_DATA");
#pragma DATA_SECTION(sem0_port,"SEM0");

volatile struct DATA_UP data_up;
volatile unsigned int dpram_up_dma[BUF_SIZE_UP];
volatile unsigned int sem0_port;
volatile unsigned int *DMACH6Dest;
volatile unsigned int *DMACH6Source;


#pragma DATA_SECTION(adc_28335_result,"ADC28335");
volatile struct I_TCR adc_28335_result;


volatile unsigned int *DMACH4Dest;
volatile unsigned int *DMACH4Source;


extern volatile struct CPLD_EXCHG cpld_exchange;
extern volatile unsigned int control_a,control_b,control_c;
extern volatile float cond_a,cond_b,cond_c;
extern unsigned int a_up_alarm,b_up_alarm,c_up_alarm;
extern unsigned int a_down_alarm,b_down_alarm,c_down_alarm;


/****************************Function 1******************************************/
// Configure the timing paramaters for Zone 6.
void init_zone6(void){

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
    // XCLKOUT = XTIMCLK 
    XintfRegs.XINTCNF2.bit.CLKMODE = 0;   

    // Zone 6------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING6.bit.XWRLEAD = 1;
    XintfRegs.XTIMING6.bit.XWRACTIVE = 2;
    XintfRegs.XTIMING6.bit.XWRTRAIL = 1;
    // Zone read timing
    XintfRegs.XTIMING6.bit.XRDLEAD = 1;
    XintfRegs.XTIMING6.bit.XRDACTIVE = 3;
    XintfRegs.XTIMING6.bit.XRDTRAIL = 0;
    
    // don't double all Zone read/write lead/active/trail timing 
    XintfRegs.XTIMING6.bit.X2TIMING = 0;
 
    // Zone will not sample XREADY signal  
    XintfRegs.XTIMING6.bit.USEREADY = 0;
    XintfRegs.XTIMING6.bit.READYMODE = 0;
 
    // 1,1 = x16 data bus
    // 0,1 = x32 data bus
    // other values are reserved
    XintfRegs.XTIMING6.bit.XSIZE = 3;
    EDIS; 
   //Force a pipeline flush to ensure that the write to 
   //the last register configured occurs before returning.  
   asm(" RPT #7 || NOP"); 
}

/****************************Function 2******************************************/
//download data from LF2407.
/*Initialize DMA ch5 Tables*/
void initial_dma_ch5(void){// Configure DMA Channel
	
	data_down.basisa = 0.0;//clear buffer.
	data_down.basisb = 0.0;
	data_down.basisc = 0.0;
	data_down.contrl_word = 0;
	data_down.downa = 0;
	data_down.downb = 0;
	data_down.downc = 0;
	data_down.kda = 0.0;
	data_down.kdb = 0.0;
	data_down.kdc = 0.0;
	data_down.kia = 0.0;
	data_down.kib = 0.0;
	data_down.kic = 0.0;
	data_down.kpa = 0.0;
	data_down.kpb = 0.0;
	data_down.kpc = 0.0;
	data_down.ovld_value = 0;
	data_down.scale = 0.0;
	data_down.upa = 0;
	data_down.upb = 0;
	data_down.upc = 0;
	data_down.manual_Ba = 0.0;
	data_down.manual_Bb = 0.0;
	data_down.manual_Bc = 0.0;

 	DMACH5Dest = &data_down.upa;
	DMACH5Source = &dpram_down_dma[0];
	DMACH5AddrConfig(DMACH5Dest,DMACH5Source);
	DMACH5BurstConfig(21,2,2);//(BURST_size[N-1],src_RURST_step[2],dst_BURST_step[2])
	DMACH5TransferConfig(1,2,2);//(TRANSFER_size[M-1],src_BURST_step[2],dst_BURST_step[2])
	//44 words need transfer, [N]22 * [M]2 = 44
	DMACH5WrapConfig(0xFFFF,0,0xFFFF,0);//disable Wrap function
	DMACH5ModeConfig(DMA_TINT2,//select TINT2 source.
		PERINT_ENABLE,//interrupt trigger enabled.
		ONESHOT_ENABLE,//
		CONT_DISABLE,//continuous disable.
		SYNC_DISABLE,//just for ADC sync,disable it in here.
		SYNC_SRC,//just for ADC application.
		OVRFLOW_DISABLE,//overflow interrupt disabled.
		THIRTYTWO_BIT,//32-bit data transfer size.
		CHINT_END,//generate interrupt at end of transfer.
		CHINT_ENABLE//interrupt ensabled.
	);
	StartDMACH5();

}

/****************************Function 3******************************************/
//download data from LF2407.
/*start a DMA access*/
//execute time:0.608us
void trig_dma_ch5(void){

	sem1_port = 0;//take resource.

	if(0x0000 == sem1_port){//get resouce succes.others should be 0xFFFF.
		EALLOW;
		DmaRegs.CH5.CONTROL.bit.PERINTFRC = 0x1;//start DMA CH5.
		EDIS;
	}
}


/****************************Function 4******************************************/
//download data from LF2407.
interrupt void local_DINTCH5_ISR(void){// DMA Channel 5

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;// To receive more interrupts from this PIE group, acknowledge this interrupt 

	sem1_port = 1;//release the resource.
	StartDMACH5();

//   asm ("      ESTOP0");//halt
//   for(;;);
}

/****************************Function 5******************************************/
//upload data to LF2407 used.
void initial_dma_ch6(void){// Configure DMA Channel
	
	data_up.state_tirg = cpld_exchange.impress;//should read from CPLD.
	data_up.state_vect = 0;

	data_up.cond_a = 0.0;//the following, monitor data realtime
	data_up.cond_b = 0.0;
	data_up.cond_c = 0.0;

	data_up.vavle_ctrl_a = 0;//
	data_up.vavle_ctrl_b = 0;
	data_up.vavle_ctrl_c = 0;

	data_up.uab_peak = 0;//
	data_up.ubc_peak = 0;
	data_up.uca_peak = 0;
	data_up.ia_peak = 0;
	data_up.ib_peak = 0;
	data_up.ic_peak = 0;

	data_up.i_tcr_a = 0;//
	data_up.i_tcr_b = 0;
	data_up.i_tcr_c = 0;

	data_up.a_up = 0;//alarm varible.
	data_up.b_up = 0;
	data_up.c_up = 0;
	data_up.a_down = 0;
	data_up.b_down = 0;
	data_up.c_down = 0;
	data_up.a_ovld = 0;
	data_up.b_ovld = 0;
	data_up.c_ovld = 0;

	//reback data.don`t refreshing in progress
	data_up.upa = data_down.upa;//
	data_up.upb = data_down.upb;
	data_up.upc = data_down.upc;
	data_up.downa = data_down.downa;
	data_up.downb = data_down.downb;
	data_up.downc = data_down.downc;

	data_up.ovld_value = data_down.ovld_value;
	data_up.state_vect = data_down.contrl_word;//indicate dynamic or fix input alpha mode.

	data_up.kpa = data_down.kpa;//
	data_up.kpb = data_down.kpb;
	data_up.kpc = data_down.kpc;
	data_up.kia = data_down.kia;
	data_up.kib = data_down.kib;
	data_up.kic = data_down.kic;
	data_up.kda = data_down.kda;
	data_up.kdb = data_down.kdb;
	data_up.kdc = data_down.kdc;
	data_up.scale = data_down.scale;
	data_up.basisa = data_down.basisa;
	data_up.basisb = data_down.basisb;
	data_up.basisc = data_down.basisc;
	data_up.manual_Ba = data_down.manual_Ba;
	data_up.manual_Bb = data_down.manual_Bb;
	data_up.manual_Bc = data_down.manual_Bc;

 	DMACH6Dest = &dpram_up_dma[0];
	DMACH6Source = &data_up.state_tirg;
	DMACH6AddrConfig(DMACH6Dest,DMACH6Source);
	DMACH6BurstConfig(22,2,2);//(BURST_size[N-1],src_RURST_step[2],dst_BURST_step[2])
	DMACH6TransferConfig(2,2,2);//(TRANSFER_size[M-1],src_BURST_step[2],dst_BURST_step[2])
	//68 words need transfer, [N]23 * [M]3 = 69
	DMACH6WrapConfig(0xFFFF,0,0xFFFF,0);//disable Wrap function
	DMACH6ModeConfig(DMA_TINT2,//select TINT2 source.
		PERINT_ENABLE,//interrupt trigger enabled.
		ONESHOT_ENABLE,//
		CONT_DISABLE,//continuous disable.
		SYNC_DISABLE,//just for ADC sync,disable it in here.
		SYNC_SRC,//just for ADC application.
		OVRFLOW_DISABLE,//overflow interrupt disabled.
		THIRTYTWO_BIT,//32-bit data transfer size.
		CHINT_END,//generate interrupt at end of transfer.
		CHINT_ENABLE//interrupt ensabled.
	);
	StartDMACH6();

}

/****************************Function 6******************************************/
//upload data to LF2407 used.
//execute time:1.528us
void trig_dma_ch6(void){

	sem0_port = 0;//take resource.

	if(0x0000 == sem0_port){//get resouce succes.others should be 0xFFFF.
		EALLOW;
		DmaRegs.CH6.CONTROL.bit.PERINTFRC = 0x1;//start DMA CH6.
		EDIS;
	}
}

/****************************Function 7******************************************/
//upload data to LF2407 used.
interrupt void local_DINTCH6_ISR(void){// DMA Channel 6

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;// To receive more interrupts from this PIE group, acknowledge this interrupt 

	sem0_port = 1;//release the resource.
	StartDMACH6();

//   asm ("      ESTOP0");//halt
//   for(;;);
}

/****************************Function 8******************************************/
//Adc_28335 converter used.
void initial_dma_ch4(void){// Configure DMA Channel

	DMACH4Dest = &adc_28335_result.tcr_iab_1;//Point DMA destination to the beginning of the array
	DMACH4Source = &AdcMirror.ADCRESULT0;//Point DMA source to ADC result register base
	DMACH4AddrConfig(DMACH4Dest,DMACH4Source);
	DMACH4BurstConfig(15,1,1);//(BURST_size[N-1],src_RURST_step[1],dst_BURST_step[1])
	DMACH4TransferConfig(0,0,0);//(TRANSFER_size[M-1],src_BURST_step[1],dst_BURST_step[1])
	DMACH4WrapConfig(0xFFFF,0,0xFFFF,0);//(src_WRAP_size,src_WRAP_step,dst_WRAP_size,dst_WRAP_step)disable Wrap function
	DMACH4ModeConfig(DMA_SEQ1INT,//trig source is SEQ1 of ADC.
		PERINT_ENABLE,//
		ONESHOT_DISABLE,//
		CONT_DISABLE,//
		SYNC_DISABLE,//
		SYNC_SRC,//
		OVRFLOW_DISABLE,//
		SIXTEEN_BIT,//
		CHINT_END,//
		CHINT_ENABLE);//
	StartDMACH4();
}

/****************************Function 9******************************************/
// Adc_28335 converter used.
interrupt void local_DINTCH4_ISR(void){//
  
// To receive more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
	StartDMACH4();

	data_up.i_tcr_a = adc_28335_result.tcr_iab_3;//
	data_up.i_tcr_b = adc_28335_result.tcr_ibc_3;
	data_up.i_tcr_c = adc_28335_result.tcr_ica_3;

}


/****************************Function 10******************************************/
//generate event according to state.
//execute time:0.376us
void event_generate(void){//

	data_up.vavle_ctrl_a = control_a;
	data_up.vavle_ctrl_b = control_b;
	data_up.vavle_ctrl_c = control_c;

	data_up.cond_a = cond_a;
	data_up.cond_b = cond_b;
	data_up.cond_c = cond_c;

	data_up.a_up = a_up_alarm;
	data_up.b_up = b_up_alarm;
	data_up.c_up = c_up_alarm;

	data_up.a_down = a_down_alarm;
	data_up.b_down = b_down_alarm;
	data_up.c_down = c_down_alarm;

	data_up.state_vect = data_down.contrl_word;//indicate dynamic or fix input alpha mode.

}



//end of file


