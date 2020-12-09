#line 10 "eeprom.h"
void wr_enable(void);
void wr_disable(void);
unsigned int rd_status(void);
void wr_status(unsigned int sta_data);
unsigned int rd_word(unsigned int);
float rd_float(unsigned int);
void wr_word(unsigned int,unsigned int);
void wr_float(unsigned int,float);#line 6 "eeprom.c"
extern unsigned int syn_data(unsigned long,unsigned int,unsigned int);
extern void delay(unsigned int);


 
void eeprom_ini(void){

	wr_status(0x80);
	
}

 
float rd_float(unsigned int addr){
	
	union{
		float fvar;
		unsigned int intvar[2];
	}conv;
	
	conv.intvar[0] = rd_word(addr);
	conv.intvar[1] = rd_word(addr+1);
	
	return(conv.fvar);
}

 
void wr_float(unsigned int addr,float fvar){
	
	union{
		float fvar;
		unsigned int intvar[2];
	}conv;
	
	conv.fvar = fvar;
	wr_word(addr,conv.intvar[0]);
	delay(7000);
	wr_word(addr+1,conv.intvar[1]);
}

 

unsigned int rd_word(unsigned int addr){

	unsigned long temp=0;
	unsigned int result=0;
	
	while(0x01 & rd_status());
	temp = 0x03;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	result = syn_data(temp,32,1);
	result = result << 8;
	addr++;
	temp = 0x03;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	result = result | syn_data(temp,32,1);
	return(result);
}

 
void wr_word(unsigned int addr,unsigned int dwd){

	unsigned long temp=0;
	unsigned int tmp;
	
	wr_enable();
	tmp = dwd;
	tmp = tmp >> 8;
	tmp = tmp & 0x00FF;
	temp = 0x02;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	temp = temp | tmp;
	while((0x03 & rd_status()) != 0x02);
	syn_data(temp,32,0);
	delay(7000);
	addr++;
	tmp = dwd;
	tmp = tmp & 0x00FF;
	temp = 0x02;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	temp = temp | tmp;
	wr_enable();
	while((0x03 & rd_status()) != 0x02);
	syn_data(temp,32,0);
	delay(7000);
	wr_disable();
}

 
void wr_enable(void){

	unsigned long temp=0;
	
	temp = 0x06;
	temp = temp << 24;
	syn_data(temp,8,0);
}

 
void wr_disable(void){

	unsigned long temp=0;
	
	temp = 0x04;
	temp = temp << 24;
	syn_data(temp,8,0);
}

 
unsigned int rd_status(void){

	unsigned long temp=0;
	unsigned int sta;
	
	temp = 0x05;
	temp = temp << 24;
	sta = syn_data(temp,16,1);
	return(sta);
}

 

void wr_status(unsigned int sta_data){

	unsigned long temp=0;
	
	wr_enable();
	temp = 0x01;
	temp = temp << 8;
	sta_data = sta_data & 0x00FF;	
	temp = temp | sta_data;
	temp = temp << 16;
	syn_data(temp,16,0);
}


