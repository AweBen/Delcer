//eeprom accessing function

#include "eeprom.h"


extern unsigned int syn_data(unsigned long,unsigned int,unsigned int);
extern void delay(unsigned int);


/*initialize*/
void eeprom_ini(void){

	wr_status(0x80);//0x000~0x3FF do not protect
	
}

/*read a float*/
float rd_float(unsigned int addr){
	
	union{
		float fvar;
		unsigned int intvar[2];
	}conv;
	
	conv.intvar[0] = rd_word(addr);
	conv.intvar[1] = rd_word(addr+1);
	
	return(conv.fvar);
}

/*write a float*/
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

/*read a word*/
//for example:3344h saved in 10H and 11H,then 33 in 10H and 44 in 11H
unsigned int rd_word(unsigned int addr){

	unsigned long temp=0;
	unsigned int result=0;
	
	while(0x01 & rd_status());//wait the device ready
	temp = READ;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	result = syn_data(temp,32,1);//read high byte
	result = result << 8;
	addr++;
	temp = READ;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	result = result | syn_data(temp,32,1);
	return(result);
}

/*write a word*/
void wr_word(unsigned int addr,unsigned int dwd){

	unsigned long temp=0;
	unsigned int tmp;
	
	wr_enable();
	tmp = dwd;
	tmp = tmp >> 8;
	tmp = tmp & 0x00FF;
	temp = WRITE;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	temp = temp | tmp;
	while((0x03 & rd_status()) != 0x02);//judge the RDY and WEN bit	
	syn_data(temp,32,0);//write high 8 bits
	delay(7000);//waiting data program
	addr++;
	tmp = dwd;
	tmp = tmp & 0x00FF;
	temp = WRITE;
	temp = temp << 16;
	temp = temp | addr;
	temp = temp << 8;
	temp = temp | tmp;
	wr_enable();
	while((0x03 & rd_status()) != 0x02);//judge the RDY and WEN bit		
	syn_data(temp,32,0);//write low 8 bits
	delay(7000);//waiting data program
	wr_disable();
}

/*write enable latch*/
void wr_enable(void){

	unsigned long temp=0;
	
	temp = WREN;
	temp = temp << 24;
	syn_data(temp,8,0);
}

/*write disable latch*/
void wr_disable(void){

	unsigned long temp=0;
	
	temp = WRDI;
	temp = temp << 24;
	syn_data(temp,8,0);
}

/*read status register*/
unsigned int rd_status(void){

	unsigned long temp=0;
	unsigned int sta;
	
	temp = RDSR;
	temp = temp << 24;
	sta = syn_data(temp,16,1);
	return(sta);
}

/*write status register*/
//sta_data low 8 bits availabel
void wr_status(unsigned int sta_data){

	unsigned long temp=0;
	
	wr_enable();//call WREN function must!
	temp = WRSR;
	temp = temp << 8;
	sta_data = sta_data & 0x00FF;	
	temp = temp | sta_data;
	temp = temp << 16;
	syn_data(temp,16,0);
}

//end