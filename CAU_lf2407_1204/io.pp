#line 216 "f2407.h"
ioport unsigned portffff;         
 

ioport unsigned portff0f; 
ioport unsigned port0; 
ioport unsigned port1; 
ioport unsigned port2; 
ioport unsigned port3; 
ioport unsigned port4;   
 
#line 5 "io.c"
extern void delay(unsigned int);
extern void inline int_dis(void);
extern void inline int_enable(void);

 
void IO_Init(void){

	*((volatile int *)0x7090) = 0x0007;
	*((volatile int *)0x7092) = 0x00C0;
	*((volatile int *)0x7094) = 0x0000;
	
	*((volatile int *)0x7098) = 0x0000;
	*((volatile int *)0x709A) = 0x9F80;
	*((volatile int *)0x709C) = 0xF720;
	*((volatile int *)0x7095) = 0x0000;
	*((volatile int *)0x7096) = 0x3838;
}


 

void LED_IO(unsigned int led,unsigned int dir){

	if(dir)
		*((volatile int *)0x709A) &= led;
	else
		*((volatile int *)0x709A) |= led;
}


 
















unsigned int read_s(void){

	unsigned int temp;
	
	temp = ((0xFF & *((volatile int *)0x7095))
			| ((0xD8 & *((volatile int *)0x7098)) << 8)
			| ((0x03 & *((volatile int *)0x7096)) << 8)
			| ((0x20 & *((volatile int *)0x709A)) << 8)
			| ((0x20 & *((volatile int *)0x7096)) << 5));
		
	return(temp);
}


 
void switch_out(void){

	if(((0x40&*((volatile int *)0x709A))>>4)^(0x04&*((volatile int *)0x7096)))
		*((volatile int *)0x7096) |= 0x0020;
	else
		*((volatile int *)0x7096) &= 0xFFDF;
		
	if(0x0020&*((volatile int *)0x709A))
		*((volatile int *)0x709A) |= 0x0002;
	else
		*((volatile int *)0x709A) &= 0xFFFD;
}

 



unsigned int syn_data(unsigned long sdata,unsigned int len,unsigned int dout){
	
	unsigned int i,result=0;
	
	int_dis();
	
	*((volatile int *)0x709C) = *((volatile int *)0x709C) & 0xFFEF;

	*((volatile int *)0x709C) = *((volatile int *)0x709C) & 0xFFDF;

	for(i=len;i>0;i--){
		*((volatile int *)0x709C) = *((volatile int *)0x709C) & 0xFFEF;

		if(0x80000000 & sdata){
			*((volatile int *)0x709C) = *((volatile int *)0x709C) | 0x0004;
		}
		else{
			*((volatile int *)0x709C) = *((volatile int *)0x709C) & 0xFFFB;
		}

		*((volatile int *)0x709C) = *((volatile int *)0x709C) | 0x0010;

		sdata = sdata << 1;
		if((dout==1)&&(i<9)){
			if(0x0008 & *((volatile int *)0x709C)){

				result = result | 0x0001;
			}
			else{
				result = result & 0xFFFE;
			}
			result = result << 1;
		}

	}
	*((volatile int *)0x709C) = *((volatile int *)0x709C) & 0xFFEF;

	*((volatile int *)0x709C) = *((volatile int *)0x709C) | 0x0020;

	if(dout==1){
		result = result >> 1;	
	}
	
	int_enable();
	
	return(result);
}


