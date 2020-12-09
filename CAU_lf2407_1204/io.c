//DSP IO define and operation

#include "f2407.h"
#include "dpram.h"


extern struct DATA_UP moni_data;
extern void delay(unsigned int);
extern void inline int_dis(void);
extern void inline int_enable(void);

/*IO initialize*/
void IO_Init(void){

	MCRA = 0x0007;//XINT1,scitxd and scirxd enable
	MCRB = 0x00C0;//cantx and canrx enable
	MCRC = 0x0000;//IOPE IOPF Enable I/O
	
	PADATDIR = 0x0000;
	PBDATDIR = 0x9F80;
	PCDATDIR = 0xF720;
	PEDATDIR = 0x0000;
	PFDATDIR = 0x3838;
}


/*LED driver function*/
//dir:0-off 1-on
void LED_IO(unsigned int led,unsigned int dir){

	if(dir)//on
		PBDATDIR &= led;
	else//off
		PBDATDIR |= led;
}


/*read VCP's status*/
//.0-a up
//.1-a down
//.2-a TCR overload
//.3-b up
//.4-b down
//.5-b TCR overload
//.6-c up
//.7-c down
//.8-c TCR overload
//.9-CPLD normal
//.10-CPU normal
//.11-system active
//.12-system pasive
//.13-st
//.14-pll ok
//.15-erro
unsigned int read_s(void){

	unsigned int temp;
	
	temp = 0;
	
	if(moni_data.ab_AC_protect) temp |= 0x0001;
	if(moni_data.bc_AC_protect) temp |= 0x0002;
	if(moni_data.ca_AC_protect) temp |= 0x0004;
	if(moni_data.dc_protect) temp |= 0x0008;
	if(moni_data.dc_over_voltaged) temp |= 0x0010;
	if(moni_data.power_fault) temp |= 0x0020;
	if(moni_data.pulse_lose_protect) temp |= 0x0040;
	if(moni_data.cooling_fault) temp |= 0x0080;
	if(moni_data.other_fault) temp |= 0x0100;
	if(moni_data.start_stop) temp |= 0x0200;

	temp |= 0x0400;//CPU ok

	temp |= (0xF8 & PADATDIR) << 8;//ERRO,PLLERR,ST,PAS,ACT
	temp ^= 0x4000;//get PLLOK logic
	
	return(temp);
}


/*switch out function*/
void switch_out(void){

	if(((0x40&PBDATDIR)>>4)^(0x04&PFDATDIR))//CAN load auto
		PFDATDIR |= 0x0020;//
	else
		PFDATDIR &= 0xFFDF;//
		
	if(0x0020&PBDATDIR)
		PBDATDIR |= 0x0002;
	else
		PBDATDIR &= 0xFFFD;
}

/*synchronous data timing*/
//sdata-the data want to write,it is align left edges 32 bits
//len-operation code length
//dout=1 read data;dout=0 no read data
unsigned int syn_data(unsigned long sdata,unsigned int len,unsigned int dout){
	
	unsigned int i,result=0;
	
	int_dis();
	
	PCDATDIR = PCDATDIR & 0xFFEF;//SCLK=0
	PCDATDIR = PCDATDIR & 0xFFDF;//CS=0
	for(i=len;i>0;i--){
		PCDATDIR = PCDATDIR & 0xFFEF;//SCLK=0
		if(0x80000000 & sdata){//bit31=1
			PCDATDIR = PCDATDIR | 0x0004;//SI=1
		}
		else{//bit31=0
			PCDATDIR = PCDATDIR & 0xFFFB;//SI=0
		}
		PCDATDIR = PCDATDIR | 0x0010;//SCLK=1
		sdata = sdata << 1;
		if((dout==1)&&(i<9)){//data out
			if(0x0008 & PCDATDIR){//SO=1

				result = result | 0x0001;
			}
			else{//SO=0
				result = result & 0xFFFE;
			}
			result = result << 1;
		}
	}
	PCDATDIR = PCDATDIR & 0xFFEF;//SCLK=0
	PCDATDIR = PCDATDIR | 0x0020;//CS=1
	if(dout==1){
		result = result >> 1;	
	}
	
	int_enable();
	
	return(result);
}

//end
