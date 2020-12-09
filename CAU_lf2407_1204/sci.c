//SCI server function

#include "f2407.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"
#include "cau_lf2407.h"
#include "string.h"
#include "dpram.h"


char c_row[] = "\n\r";
char c_return[] = "\r";
char table[] = "\t";
char space[] = "-";
char separator[] = "  \t|\t";
char vcp[] = "VCP:>";
char vcpset[] = "VCP.edit:>";
char fail_in[] = "Failed input!\n\r";
char description[] = "Research and development Dept. of XPR\n\r";
char connected[] = "Valve Control Protection is connected!\n\r";
char state_val[] = "VCP state word:0x";
char set_str[] = "set\r";
char quit_str[] = "quit\r";
char list_str[] = "list\r";
char node_str[] = "node\r";
char mode_str[] = "mode\r";
char mon_str[] = "mon\r";
char limen_str[] = "ovld\r";
char cancel_str[] = "cancel\r";
char kpa_str[] = "kpa\r";
char kpb_str[] = "kpb\r";
char kpc_str[] = "kpc\r";
char kia_str[] = "kia\r";
char kib_str[] = "kib\r";
char kic_str[] = "kic\r";
char kda_str[] = "kda\r";
char kdb_str[] = "kdb\r";
char kdc_str[] = "kdc\r";
char upa_str[] = "upa\r";
char upb_str[] = "upb\r";
char upc_str[] = "upc\r";
char downa_str[] = "downa\r";
char downb_str[] = "downb\r";
char downc_str[] = "downc\r";
char offseta_str[] = "basisa\r";
char offsetb_str[] = "basisb\r";
char offsetc_str[] = "basisc\r";
char scale_str[] = "scale\r";
char susceptance_manual_A_str[] = "sma\r";
char susceptance_manual_B_str[] = "smb\r";
char susceptance_manual_C_str[] = "smc\r";
char password[] = "1234\r";
char tips_l1[] = "node\tmode\tscale\tovld\tupa\tupb\tupc\n\r";
char tips_l2[] = "downa\tdownb\tdownc\tbasisa\tbasisb\tbasicc\tkpa\n\r";
char tips_l3[] = "kpb\tkpc\tkia\tkib\tkic\tkda\tkdb\n\r";
char tips_l4[] = "kdc\tsma\tsmb\tsmc\n\r";
char pass[] = "password:";
char current_value[] = "The current value:";
char node_disp[] = "Equip Node:";
char limen_disp[] = "OverLoad:";
char scale_disp[] = "Scale:";
char manual_Ba_disp[] = "Manual Sus AB:";
char manual_Bb_disp[] = "Manual Sus BC:";
char manual_Bc_disp[] = "Manual Sus CA:";
char offset_a_disp[] = "Bas A:";
char offset_b_disp[] = "Bas B:";
char offset_c_disp[] = "Bas C:";
char p_a_disp[] = "Kp A:";
char p_b_disp[] = "Kp B:";
char p_c_disp[] = "Kp C:";
char i_a_disp[] = "Ki A:";
char i_b_disp[] = "Ki B:";
char i_c_disp[] = "Ki C:";
char d_a_disp[] = "Kd A:";
char d_b_disp[] = "Kd B:";
char d_c_disp[] = "Kd C:";
char up_a_disp[] = "Up A:";
char up_b_disp[] = "Up B:";
char up_c_disp[] = "Up C:";
char down_a_disp[] = "Down A:";
char down_b_disp[] = "Down B:";
char down_c_disp[] = "Down C:";
char mode_disp[] = "Control mode:";
char phase_a_disp[] = "[A] ";
char phase_b_disp[] = "[B] ";
char phase_c_disp[] = "[C] ";
char alpha_disp[] = "Alpha:";
char up_disp[] = "Up embit:";
char down_disp[] = "Dn embit:";
char suscpt_disp[] = "Manu Sus:";
char basis_disp[] = "Basis:";
char kp_disp[] = "KP value:";
char ki_disp[] = "KI value:";
char kd_disp[] = "KD value:";
char para_input[] = "Input the parameters name:";
char new_value[] = "Input a new value[0,65535]:";
char new_fvalue[] = "Input a new value[xxxx.xxx]:";
char inv_pass[] = "Invalid password";
char input_erro[]= "Invalid data";
char invalid_com[] = "Invalid command";
char disconnect[] = "You can disconnect the cable now...";
char moni_suspend[] = "Monitoring suspend!";
char mon_title[] = "    [AC Voltage.peak]        [Load Current.peak]        [TCR Current]\n\r";
char mon_table[] = " AB:     BC:     CA:         A:     B:     C:        AB:     BC:     CA:";
char mon_pos_1[] = "\r\t\b\b\b\b";
char mon_pos_2[] = "\r\t\t\b\b\b\b";
char mon_pos_3[] = "\r\t\t\t\b\b\b\b";
char mon_pos_4[] = "\r\t\t\t\t\b";
char mon_pos_5[] = "\r\t\t\t\t\t\b\b";
char mon_pos_6[] = "\r\t\t\t\t\t\t\b\b\b";
char mon_pos_7[] = "\r\t\t\t\t\t\t\t";
char mon_pos_8[] = "\r\t\t\t\t\t\t\t\t";
char mon_pos_9[] = "\r\t\t\t\t\t\t\t\t\t";


char sci_receive[20];
char send[40];
unsigned int sci_i = 0;
unsigned int pass_flag = 0;//function flag
unsigned int para_sele = 0;//patameter edit flag


extern unsigned int node;
extern unsigned int up_a,up_b,up_c;
extern unsigned int up_a_u,up_b_u,up_c_u;	//no use,because slaver CPU not refresh on time.
extern unsigned int down_a,down_b,down_c;
extern unsigned int down_a_u,down_b_u,down_c_u;
extern unsigned int state;
extern unsigned int alpha_a,alpha_b,alpha_c;
extern unsigned int basisa_int,basisb_int,basisc_int;
extern struct DATA_DN order_data;
extern struct DATA_UP moni_data;
extern unsigned int mon_cmd;


extern void wr_word(unsigned int addr,unsigned int dwd);
extern void wr_float(unsigned int,float);
extern unsigned int rd_word(unsigned int);
extern float rd_float(unsigned int);
extern void disable_WD(void);
extern void clean_IFR(void);
extern void inline int_enable(void);
extern void delay(unsigned int);



/*series port initialize*/
void SCI_INIT(void){

	SCICCR = 0x7;//8 bits data
    SCICTL1 = 0x13;
	SCICTL2 = 0x02;
	SCIHBAUD = 0x0;//baud rate 19200
    SCILBAUD = 0xC2;
	SCICTL1 = 0x33;//
	SCIPRI = 0x61;//
}

/*send out a character*/
//send		the char to be send out
void UartSent(char send){
	
	unsigned long i;
	
//	disable_WD();
	
	while(!(SCICTL2 & 0x80));
	SCITXBUF = send;
	
	clean_IFR();
//	int_enable();
}

/*send out a string function*/
//send		the string to be send out
void UartSent_str(char *send){

	unsigned int i;
	
//	disable_WD();
	
	for(i=0;i<(strlen(send));i++) UartSent(send[i]);
	
//	int_enable();
}

/*receive a character and echo it*/
//receive-character received
//flag-control word
void UartRec(char *receive,unsigned int flag){
	
//	disable_WD();
	*receive =  SCIRXBUF;//save the character received
	clean_IFR();
	int_enable();
	if(1 == flag){
		UartSent('*');//password hidden
	}
	else{
		UartSent(*receive);//echo the character received
	}
}


/*ascii to integer function*/
//str		the ascii code to be convert
//*pint 	the dec result[0,65535]
unsigned int strtoint(char *str,unsigned int *pint){
	
	unsigned int i,r;
	unsigned long sum;
	
	sum = 0;
	for(i = 0;i < (strlen(str)-1);i++){
		if((str[i]<48) || (str[i]>57) || (strlen(str)>6)){//invalid number char
			r = 0;//convert invalid flag
			break;
		}
		else{
			r = 1;//
			switch(strlen(str)-i){
			case 2:
				sum += (str[i]-48);
				break;
			case 3:
				sum += 10*(str[i]-48);
				break;
			case 4:
				sum += 100*(str[i]-48);
				break;
			case 5:
				sum += 1000*(str[i]-48);
				break;
			case 6:
				sum += 10000*(str[i]-48);
				break;
			default: break;
			}
		}
	}
	
	if(sum > 65535) r = 0;
	else *pint = sum;
	
	return(r);
}

/*integer to ascii function*/
//data		interger(dec) data
//str		the ascii code to be saved[xxxxx]
//return	0-convert failed;1-convert success
unsigned int inttostr(unsigned int data,char *str){

	unsigned int d;
	
	if(data < 10){
		str[0] = data + 48;
		str[1] = '\0';
		d = 1;
	}
	else if(data < 100){
		str[0] = data/10 + 48;
		str[1] = (data%10) +48;
		str[2] = '\0';
		d = 1;
	}
	else if(data < 1000){
		str[0] = data/100 + 48;
		d = data % 100;
		str[1] = d/10 + 48;
		str[2] = (d%10) + 48;
		str[3] = '\0';
		d = 1;
	}
	else if(data < 10000){
		str[0] = data/1000 + 48;
		d = data % 1000;
		str[1] = d/100 + 48;
		d = d % 100;
		str[2] = d/10 + 48;
		str[3] = (d%10) + 48;
		str[4] = '\0';
		d = 1;
	}
	else if(data <= 65535){
		str[0] = data/10000 + 48;
		d = data % 10000;
		str[1] = d/1000 + 48;
		d = data % 1000;
		str[2] = d/100 + 48;
		d = d % 100;
		str[3] = d/10 + 48;
		str[4] = (d%10) + 48;
		str[5] = '\0';
		d = 1;
	}
	else{//data great than 65536
		d = 0;
	}
	return(d);
}

/*hex data to ascii function*/
//data		the data will be convert
//str		the ascii code to be saved
//return	0-convert failed;1-convert success
unsigned int hextostr(unsigned int data,char *str){

	char temp;
	unsigned int rt;
	
	if(data>65535 || data<0) rt = 0;
	else{
		temp = (data >> 12) & 0x0F;
		if(temp > 9) str[0] = temp + 55;
		else str[0] = temp + 48;
		temp = (data >> 8) & 0x0F;
		if(temp > 9) str[1] = temp + 55;
		else str[1] = temp + 48;
		temp = (data >> 4) & 0x0F;
		if(temp > 9) str[2] = temp + 55;
		else str[2] = temp + 48;			
		temp = data & 0x0F;
		if(temp > 9) str[3] = temp + 55;
		else str[3] = temp + 48;	
		str[4] = '\0';
		rt = 1;
	}
	
	return(rt);
}


/*float to ascii function*/
//data		float data
//str		the ascii code to be saved[xxxx.xxx]
void floattostr(float data,char *str){
	
	unsigned long int temp;
	
	if(data < 0){
		data = fabs(data);
		str[0] = '-';
	}
	else{
		str[0] = '+';
	}
	temp = (unsigned long int)1000 * data;
	if(temp < 1){//deta
		str[0] = '0';
		str[1] = '.';
		str[2] = '0';
		str[3] = '\0';
	}
	else if(temp < 10){//0.00x
		str[1] = '0';
		str[2] = '.';
		str[3] = '0';
		str[4] = '0';
		str[5] = temp + 48;
		str[6] = '\0';
	}
	else if(temp < 100){//0.0xx
		str[1] = '0';
		str[2] = '.';
		str[3] = '0';
		str[4] = temp/10 + 48;
		str[5] = temp%10 + 48;
		str[6] = '\0';
	}		
	else if(temp < 1000){//0.xxx
		str[1] = '0';
		str[2] = '.';
		str[3] = temp/100 +48;
		temp = temp % 100;
		str[4] = temp/10 + 48;
		str[5] = temp%10 + 48;
		str[6] = '\0';
	}
	else if(temp < 10000){//x.xxx
		str[1] = temp/1000 + 48;
		temp = temp % 1000;
		str[2] = '.';
		str[3] = temp/100 + 48;
		temp = temp % 100;
		str[4] = temp/10 +48;
		str[5] = temp%10 + 48;
		str[6] = '\0';
	}
	else if(temp < 100000){//xx.xxx
		str[1] = temp/10000 + 48;
		temp = temp % 10000;
		str[2] = temp/1000 + 48;
		temp = temp % 1000;
		str[3] = '.';
		str[4] = temp/100 + 48;
		temp = temp % 100;
		str[5] = temp/10 +48;
		str[6] = temp%10 + 48;
		str[7] = '\0';
	}
	else if(temp < 1000000){//xxx.xxx
		str[1] = temp/100000 + 48;
		temp = temp % 100000;
		str[2] = temp/10000 + 48;
		temp = temp % 10000;
		str[3] = temp/1000 + 48;
		temp = temp % 1000;
		str[4] = '.';
		str[5] = temp/100 + 48;
		temp = temp % 100;
		str[6] = temp/10 +48;
		str[7] = temp%10 + 48;
		str[8] = '\0';
	}
	else if(temp < 10000000){//xxxx.xxx
		str[1] = temp/1000000 + 48;
		temp = temp % 1000000;
		str[2] = temp/100000 + 48;
		temp = temp % 100000;
		str[3] = temp/10000 + 48;
		temp = temp % 10000;
		str[4] = temp/1000 + 48;
		temp = temp % 1000;
		str[5] = '.';
		str[6] = temp/100 + 48;
		temp = temp % 100;
		str[7] = temp/10 +48;
		str[8] = temp%10 + 48;
		str[9] = '\0';
	}
	else{//float more than valid value
		str[0] = 'e';
		str[1] = 'r';
		str[2] = 'r';
		str[3] = 'o';
		str[4] = 'r';
		str[5] = '\0';
	}
}

/*display a para and talbe*/
//input:	str		the string to be display
//			value	the value to be display
//display a para from current cursor and table
void one_para_disp(char *str,unsigned int value){

	strcpy(send,str);
	UartSent_str(send);
	
	if(inttostr(value,send))
		UartSent_str(send);
	else
		UartSent_str("!");
}

/*display a float and talbe*/
//input:	str		the string to be display
//			value	the value to be display
//display a float from current cursor and table	
void float_disp(char *str,float value){
	
	strcpy(send,str);
	UartSent_str(send);
	
	floattostr(value,send);
	UartSent_str(send);
}

/*display all the value function*/
void value_display(void){

	strcpy(send,state_val);//line 1:state word display.
	UartSent_str(send);
	if(hextostr(state,send))
		UartSent_str(send);
	else
		UartSent_str("255");
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 2:alpha_a=xxx alpha_b=xxx alpha_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,alpha_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_a_disp,alpha_a);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_b_disp,alpha_b);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_c_disp,alpha_c);//C
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 3:can node display.
	UartSent_str(send);
	strcpy(send,space);
	UartSent_str(send);
	one_para_disp(node_disp,node);//node
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 4:mode display.
	UartSent_str(send);
	strcpy(send,space);
	UartSent_str(send);
	one_para_disp(mode_disp,order_data.contrl_word);
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 5:scale value display.
	UartSent_str(send);
	strcpy(send,space);
	UartSent_str(send);
	float_disp(scale_disp,order_data.scale);
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 6:overload value display.
	UartSent_str(send);
	strcpy(send,space);
	UartSent_str(send);
	one_para_disp(limen_disp,order_data.ovld_value);
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 7:up_a=xxx up_b=xxx up_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,up_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_a_disp,up_a);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_b_disp,up_b);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_c_disp,up_c);//C
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 8:down_a=xxx down_b=xxx down_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,down_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_a_disp,down_a);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_b_disp,down_b);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_c_disp,down_c);//C
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 9:Suspct_a=xxx Suspct_b=xxx Suspct_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,suscpt_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_a_disp,order_data.manual_Ba);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_b_disp,order_data.manual_Bb);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_c_disp,order_data.manual_Bc);//C
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 10:basis_a=xxx basis_b=xxx basis_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,basis_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_a_disp,basisa_int);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_b_disp,basisb_int);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	one_para_disp(phase_c_disp,basisc_int);//C
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 11:p_a=xxx p_b=xxx p_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,kp_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_a_disp,order_data.kpa);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_b_disp,order_data.kpb);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_c_disp,order_data.kpc);//C
	strcpy(send,c_row);
	UartSent_str(send);

	strcpy(send,vcp);//line 12:i_a=xxx i_b=xxx i_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,ki_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_a_disp,order_data.kia);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_b_disp,order_data.kib);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_c_disp,order_data.kic);//C
	strcpy(send,c_row);
	UartSent_str(send);


	strcpy(send,vcp);//line 13:d_a=xxx d_b=xxx d_c=xxx
	UartSent_str(send);
	strcpy(send,space);//'-'
	UartSent_str(send);
	strcpy(send,kd_disp);//string display.
	UartSent_str(send);
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_a_disp,order_data.kda);//A
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_b_disp,order_data.kdb);//B
	strcpy(send,c_return);//'return'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	strcpy(send,table);//'table'
	UartSent_str(send);
	float_disp(phase_c_disp,order_data.kdc);//C
	strcpy(send,c_row);
	UartSent_str(send);



	strcpy(send,vcp);
	UartSent_str(send);
}

/*edit the parameter*/
/*discern order,such as node,kpa,kpb,kpc ect.*/
void edit_para(void){

	if(!strcmp(node_str,sci_receive)){//node edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(node_disp,node);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 1;//node save flag
	}
	else if(!strcmp(limen_str,sci_receive)){//overload limen edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(limen_disp,order_data.ovld_value);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 2;//limen save flag
	}
	else if(!strcmp(kpa_str,sci_receive)){//kpa edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(p_a_disp,order_data.kpa);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 3;//kp_a save flag
	}
	else if(!strcmp(kpb_str,sci_receive)){//kpb edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(p_b_disp,order_data.kpb);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 4;//kp_b save flag
	}
	else if(!strcmp(kpc_str,sci_receive)){//kpc edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(p_c_disp,order_data.kpc);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 5;//kp_c save flag
	}

	else if(!strcmp(kia_str,sci_receive)){//kia edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(i_a_disp,order_data.kia);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 6;//ki_a save flag
	}
	else if(!strcmp(kib_str,sci_receive)){//kib edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(i_b_disp,order_data.kib);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 7;//ki_b save flag
	}
	else if(!strcmp(kic_str,sci_receive)){//kic edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(i_c_disp,order_data.kic);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 8;//ki_c save flag
	}
	else if(!strcmp(kda_str,sci_receive)){//kda edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(d_a_disp,order_data.kda);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 9;//kd_a save flag
	}
	else if(!strcmp(kdb_str,sci_receive)){//kdb edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(d_b_disp,order_data.kdb);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 10;//kd_b save flag
	}
	else if(!strcmp(kdc_str,sci_receive)){//kdc edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(d_c_disp,order_data.kdc);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 11;//kd_c save flag
	}
	else if(!strcmp(upa_str,sci_receive)){//upa edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(up_a_disp,up_a);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 12;//upa save flag
	}
	else if(!strcmp(upb_str,sci_receive)){//upb edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(up_b_disp,up_b);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 13;//upb save flag
	}
	else if(!strcmp(upc_str,sci_receive)){//upc edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(up_c_disp,up_c);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 14;//upc save flag
	}
	else if(!strcmp(downa_str,sci_receive)){//downa edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(down_a_disp,down_a);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 15;//downa save flag
	}
	else if(!strcmp(downb_str,sci_receive)){//downb edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(down_b_disp,down_b);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 16;//downb save flag
	}
	else if(!strcmp(downc_str,sci_receive)){//downc edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(down_c_disp,down_c);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 17;//downc save flag
	}
	else if(!strcmp(offseta_str,sci_receive)){//basisa edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(offset_a_disp,basisa_int);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 18;//basisa save flag
	}
	else if(!strcmp(offsetb_str,sci_receive)){//basisb edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(offset_a_disp,basisb_int);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);

		pass_flag = 3;
		para_sele = 19;//offsetb save flag
	}
	else if(!strcmp(offsetc_str,sci_receive)){//offsetc edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(offset_c_disp,basisc_int);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 20;//offsetc save flag
	}
	else if(!strcmp(scale_str,sci_receive)){//scale edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(scale_disp,order_data.scale);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 21;//scale save flag
	}
	else if(!strcmp(mode_str,sci_receive)){//mode edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(mode_disp,order_data.contrl_word);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_value);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 22;//don't need save it.
	}
	else if(!strcmp(susceptance_manual_A_str,sci_receive)){//susceptance manual AB edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(manual_Ba_disp,order_data.manual_Ba);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 23;//manual_Ba save flag
	}
	else if(!strcmp(susceptance_manual_B_str,sci_receive)){//susceptance manual BC edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(manual_Bb_disp,order_data.manual_Bb);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 24;//manual_Bb save flag
	}
	else if(!strcmp(susceptance_manual_C_str,sci_receive)){//susceptance manual CA edit
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(manual_Bc_disp,order_data.manual_Bc);
		
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		strcpy(send,new_fvalue);
		UartSent_str(send);
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
		
		pass_flag = 3;
		para_sele = 25;//manual_Bc save flag
	}


	else if(!strcmp(quit_str,sci_receive)){//return to list command view
		strcpy(send,vcp);
		UartSent_str(send);
		pass_flag = 0;
		para_sele = 0;
	}	
	else{//invalid input
		sci_i = 0;
		strcpy(send,vcpset);
		UartSent_str(send);
		strcpy(send,fail_in);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
	}	
}
/*save the parameter to eeprom*/
/*discern 0~9 or cancle*/
void save_para(void){

	unsigned int temp;
	float ftemp;
	
	switch(para_sele){
		case 1://save node
			if(strtoint(sci_receive,&temp)){//save the new value and display it
				wr_word(NODE_ADDR,temp);
				node = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(node_disp,node);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{//the input data invalid
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 2://save tcr current overload value
			if(strtoint(sci_receive,&temp)){
				wr_word(LIMEN_ADDR,temp);
				order_data.ovld_value = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(limen_disp,order_data.ovld_value);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}		
			break;
		case 3://save kpa
			ftemp = atof(sci_receive);
			wr_float(P_A_ADDR,ftemp);
			order_data.kpa = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(p_a_disp,order_data.kpa);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 4://save kpb
			ftemp = atof(sci_receive);
			wr_float(P_B_ADDR,ftemp);
			order_data.kpb = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(p_b_disp,order_data.kpb);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 5://save kpc
			ftemp = atof(sci_receive);
			wr_float(P_C_ADDR,ftemp);
			order_data.kpc = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(p_c_disp,order_data.kpc);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 6://save kia
			ftemp = atof(sci_receive);
			wr_float(I_A_ADDR,ftemp);
			order_data.kia = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(i_a_disp,order_data.kia);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 7://save kib
			ftemp = atof(sci_receive);
			wr_float(I_B_ADDR,ftemp);
			order_data.kib = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(i_b_disp,order_data.kib);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 8://save kic
			ftemp = atof(sci_receive);
			wr_float(I_C_ADDR,ftemp);
			order_data.kic = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(i_c_disp,order_data.kic);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 9://save kda
			ftemp = atof(sci_receive);
			wr_float(D_A_ADDR,ftemp);
			order_data.kda = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(d_a_disp,order_data.kda);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 10://save kdb
			ftemp = atof(sci_receive);
			wr_float(D_B_ADDR,ftemp);
			order_data.kdb = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(d_b_disp,order_data.kdb);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 11://save kdc
			ftemp = atof(sci_receive);
			wr_float(D_C_ADDR,ftemp);
			order_data.kdc = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(d_c_disp,order_data.kdc);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 12://save upa
			if(strtoint(sci_receive,&temp)){
				wr_word(UP_A_ADDR,temp);
				up_a = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(up_a_disp,up_a);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}		
			break;
		case 13://save upb
			if(strtoint(sci_receive,&temp)){
				wr_word(UP_B_ADDR,temp);
				up_b = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(up_b_disp,up_b);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}		
			break;
		case 14://save upc
			if(strtoint(sci_receive,&temp)){
				wr_word(UP_C_ADDR,temp);
				up_c = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(up_c_disp,up_c);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}		
			break;
		case 15://save downa
			if(strtoint(sci_receive,&temp)){
				wr_word(DOWN_A_ADDR,temp);
				down_a = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(down_a_disp,down_a);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}		
			break;
		case 16://save downb
			if(strtoint(sci_receive,&temp)){
				wr_word(DOWN_B_ADDR,temp);
				down_b = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(down_b_disp,down_b);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 17://save downc
			if(strtoint(sci_receive,&temp)){
				wr_word(DOWN_C_ADDR,temp);
				down_c = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(down_c_disp,down_c);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 18://save basisa
			if(strtoint(sci_receive,&temp)){
				wr_word(OFFSET_A_ADDR,temp);
				basisa_int = temp;
				order_data.basisa = (float)basisa_int;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(offset_a_disp,basisa_int);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 19://save basisb
			if(strtoint(sci_receive,&temp)){
				wr_word(OFFSET_B_ADDR,temp);
				basisb_int = temp;
				order_data.basisb = (float)basisb_int;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(offset_b_disp,basisb_int);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 20://save basisc
			if(strtoint(sci_receive,&temp)){
				wr_word(OFFSET_C_ADDR,temp);
				basisc_int = temp;
				order_data.basisc = (float)basisc_int;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(offset_c_disp,basisc_int);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 21://save scale
			ftemp = atof(sci_receive);
			wr_float(SCALE_ADDR,ftemp);
			order_data.scale = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(scale_disp,order_data.scale);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 22://mode
			if(strtoint(sci_receive,&temp)){
//				wr_word(DOWN_C_ADDR,temp);//don't need save in eeprom.
				order_data.contrl_word = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(mode_disp,order_data.contrl_word);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			else{
				strcpy(send,input_erro);
				UartSent_str(send);
				strcpy(send,c_row);
				UartSent_str(send);
			}
			break;
		case 23://save manual input susceptance(B) phase AB
			ftemp = atof(sci_receive);
//			wr_float(SCALE_ADDR,ftemp);//don't need save in eeprom.
			order_data.manual_Ba = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(manual_Ba_disp,order_data.manual_Ba);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 24://save manual input susceptance(B) phase BC
			ftemp = atof(sci_receive);
//			wr_float(SCALE_ADDR,ftemp);//don't need save in eeprom.
			order_data.manual_Bb = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(manual_Bb_disp,order_data.manual_Bb);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 25://save manual input susceptance(B) phase CA
			ftemp = atof(sci_receive);
//			wr_float(SCALE_ADDR,ftemp);//don't need save in eeprom.
			order_data.manual_Bc = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(manual_Bc_disp,order_data.manual_Bc);
			strcpy(send,c_row);
			UartSent_str(send);
			break;

		default: break;
	}
}

/*series server function*/
void sci_server(void){

	unsigned int temp;
	
	UartRec(&sci_receive[sci_i++],pass_flag);
	sci_receive[sci_i] = '\0';
	
	if('\r' == sci_receive[sci_i-1]){//the character received is ENTER
		sci_i = 0;//laber clear
		strcpy(send,c_row);
		UartSent_str(send);//new line and rerurn
		switch(pass_flag){
			case 0://hello server
				if((!strcmp(set_str,sci_receive))&&(!mon_cmd)){//set command
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,pass);
					UartSent_str(send);
					pass_flag = 1;//enter the password dialog
				}
				else if((!strcmp(list_str,sci_receive))&&(!mon_cmd)){//list command
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,space);
					UartSent_str(send);
					value_display();
				}
				else if((!strcmp(mon_str,sci_receive))&&(!mon_cmd)){//mon command
					mon_cmd = 1;
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,mon_title);//
					UartSent_str(send);
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,mon_table);//
					UartSent_str(send);
				}
				else if((!strcmp(quit_str,sci_receive))&&(!mon_cmd)){//quit command
					strcpy(send,disconnect);
					UartSent_str(send);
					pass_flag = 0;
				}
				else{//others
					if(1 == mon_cmd){//monitoring suspend
						mon_cmd = 0;
						strcpy(send,vcp);
						UartSent_str(send);
						strcpy(send,moni_suspend);//
						UartSent_str(send);
						strcpy(send,c_row);
						UartSent_str(send);
						strcpy(send,vcp);
						UartSent_str(send);
					}
					else{//invalid command
						strcpy(send,vcp);
						UartSent_str(send);
						strcpy(send,invalid_com);//
						UartSent_str(send);
						strcpy(send,c_row);
						UartSent_str(send);
						strcpy(send,vcp);
						UartSent_str(send);
					}	
				}
				
				break;
			case 1://password server
				if(!strcmp(password,sci_receive)){//password corrocet
					strcpy(send,vcpset);
					UartSent_str(send);
					
					strcpy(send,tips_l1);
					UartSent_str(send);
					strcpy(send,vcpset);
					UartSent_str(send);
					strcpy(send,tips_l2);
					UartSent_str(send);
					strcpy(send,vcpset);
					UartSent_str(send);
					strcpy(send,tips_l3);
					UartSent_str(send);
					strcpy(send,vcpset);
					UartSent_str(send);
					strcpy(send,tips_l4);
					UartSent_str(send);
					strcpy(send,vcpset);
					UartSent_str(send);
					
					strcpy(send,para_input);
					UartSent_str(send);
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,vcpset);
					UartSent_str(send);
					pass_flag = 2;//enter the set dialog
				}
				else{//password invalid description
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,inv_pass);
					UartSent_str(send);
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,pass);
					UartSent_str(send);
				}
				break;
			case 2://edit parameter
				edit_para();
				break;
			case 3://save parameter
				if(!strcmp(cancel_str,sci_receive)){//cancel command
					strcpy(send,vcpset);
					UartSent_str(send);
					para_sele = 0;
					pass_flag = 2;//quit parameter save function
				}
				else if(strlen(sci_receive) > 1){
					strcpy(send,vcpset);
					UartSent_str(send);
					save_para();
					strcpy(send,vcpset);
					UartSent_str(send);
				}
				else{//enter only,nothing
					strcpy(send,vcpset);
					UartSent_str(send);
				}
				break;
			default: break;
		}	
	}
	
	if(sci_i > 9){//the valid command length is less than 10 characters
		sci_i = 0;
		strcpy(send,c_row);
		UartSent_str(send);
		strcpy(send,vcp);
		UartSent_str(send);
		strcpy(send,fail_in);
		UartSent_str(send);
		strcpy(send,vcp);
		UartSent_str(send);
	}
	
}

/**/
void mon_disp(void){

	strcpy(send,mon_pos_1);
	UartSent_str(send);
	if(inttostr(moni_data.uab_peak,send)) UartSent_str(send);//Vab peak
	strcpy(send,mon_pos_2);
	UartSent_str(send);
	if(inttostr(moni_data.ubc_peak,send)) UartSent_str(send);//Vbc peak
	strcpy(send,mon_pos_3);
	UartSent_str(send);
	if(inttostr(moni_data.uca_peak,send)) UartSent_str(send);//Vca peak

	strcpy(send,mon_pos_4);
	UartSent_str(send);
	if(inttostr(moni_data.ia_peak,send)) UartSent_str(send);//Load Ia peak
	strcpy(send,mon_pos_5);
	UartSent_str(send);
	if(inttostr(moni_data.ib_peak,send)) UartSent_str(send);//Load Ib peak
	strcpy(send,mon_pos_6);
	UartSent_str(send);
	if(inttostr(moni_data.ic_peak,send)) UartSent_str(send);//Load Ic peak

	strcpy(send,mon_pos_7);
	UartSent_str(send);
	if(inttostr(moni_data.i_tcr_a,send)) UartSent_str(send);//TCR Iab
	strcpy(send,mon_pos_8);
	UartSent_str(send);
	if(inttostr(moni_data.i_tcr_b,send)) UartSent_str(send);//TCR Ibc
	strcpy(send,mon_pos_9);
	UartSent_str(send);
	if(inttostr(moni_data.i_tcr_c,send)) UartSent_str(send);//TCR Ica

}

//end