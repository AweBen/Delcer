#line 216 "f2407.h"
ioport unsigned portffff;         
 

ioport unsigned portff0f; 
ioport unsigned port0; 
ioport unsigned port1; 
ioport unsigned port2; 
ioport unsigned port3; 
ioport unsigned port4;   
 
#line 14 "stdlib.h"
typedef unsigned size_t;
#line 19
typedef char wchar_t;





int           atoi(const char *_st);
long          atol(const char *_st);
double        atof(const char *_st);

double        strtod (const char *_st, char **_endptr);
long          strtol (const char *_st, char **_endptr, int _base);
unsigned long strtoul(const char *_st, char **_endptr, int _base);

typedef struct _div_t  { int  quot, rem; } div_t;
typedef struct _ldiv_t { long quot, rem; } ldiv_t;
div_t         div(int _numer, int _denom);
ldiv_t        ldiv(long _numer, long _denom);


int           rand(void);
void          srand(unsigned _seed);

void         *calloc(size_t _num, size_t _size);
void          free(void *_ptr);
void         *malloc(size_t _size);
void          minit(void);
void         *realloc(void *_ptr, size_t _size);



void          abort(void);
void          exit(int _status);
int           atexit(void (*_func)(void));

int           abs(int _i);
long          labs(long _l);

void qsort(void *_base,
           size_t _nmemb, 
           size_t _size,
           int (*_compar)(const void *, const void *));

void *bsearch(const void *_key,
	      const void *_abase,
	      size_t     _nmemb,
	      size_t     _size,
	      int (*_compar)(const void *, const void *));

char *getenv(const char *_name);

#line 16 "C:/ti/c2400/cgtools/include\ctype.h"
extern unsigned char _ctypes_[];

#line 27
 int isalnum(int _c);
 int isalpha(int _c);
 int iscntrl(int _c);
 int isdigit(int _c);
 int isgraph(int _c);
 int islower(int _c);
 int isprint(int _c);
 int ispunct(int _c);
 int isspace(int _c);
 int isupper(int _c);
 int isxdigit(int _c);
 int isascii(int _c);

 int toupper(int _c);
 int tolower(int _c);
 int toascii(int _c);

 
 
 
#line 19 "C:/ti/c2400/cgtools/include\math.h"
         double asin(double _x);
         double acos(double _x);
         double atan(double _x);
         double atan2(double _y, double _x);
 double ceil(double _x);
         double cos(double _x);
         double cosh(double _x);
         double exp(double _x);
         double fabs(double _x);
 double floor(double _x);
 double fmod(double _x, double _y);
         double frexp(double _x, int *_exp);
         double ldexp(double _x, int _exp);
         double log(double _x);
         double log10(double _x);
         double modf(double _x, double *_iptr);
         double pow(double _x, double _y);
         double sin(double _x);
         double sinh(double _x);
         double sqrt(double _x);
         double tan(double _x);
         double tanh(double _x);

#line 23 "C:/ti/c2400/cgtools/include\string.h"
 void  *memchr  (const void *_s,        int   _c,  size_t _n);
 int    memcmp  (const void *_s1, const void *_s2, size_t _n);
 void  *memcpy  (      void *_s1, const void *_s2, size_t _n);
         void  *memmove (      void *_s1, const void *_s2, size_t _n);
 void  *memset  (      void *_s,        int   _c,  size_t _n);

 char  *strcat  (      char *_s1, const char *_s2);
 char  *strchr  (const char *_s,        int   _c);
 int    strcmp  (const char *_s1, const char *_s2);
         int    strcoll (const char *_s1, const char *_s2);
 char  *strcpy  (      char *_s1, const char *_s2);
         size_t strcspn (const char *_s1, const char *_s2);
         char  *strerror(      int   _errno);
 size_t strlen  (const char *_s1);
         char  *strncat (      char *_s1, const char *_s2, size_t _n);
         int    strncmp (const char *_s1, const char *_s2, size_t _n);
         char  *strncpy (      char *_s1, const char *_s2, size_t _n);
         char  *strpbrk (const char *_s1, const char *_s2);
 char  *strrchr (const char *_s1,       int   _c);
         size_t strspn  (const char *_s1, const char *_s2);
         char  *strstr  (const char *_s1, const char *_s2);
         char  *strtok  (      char *_s1, const char *_s2);
         size_t strxfrm (      char *_s1, const char *_s2, size_t _n);

#line 10 "sci.c"
char c_row[] = "\n\r";
char table[] = "\t|\t";
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
char limen_str[] = "thre\r";
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
char password[] = "1234\r";
char tips_l1[] = "node\tkpa\tkpb\tkpc\tkia\tkib\tkic\n\r";
char tips_l2[] = "kda\tkdb\tkdc\tthre\tupa\tupb\tupc\n\r";
char tips_l3[] = "downa\tdownb\tdownc\tbasisa\tbasisb\tbasicc\tscale\n\r";
char pass[] = "password:";
char current_value[] = "The current value:";
char node_disp[] = "equip node:";
char limen_disp[] = "threshold:";
char scale_disp[] = "scale:";
char offset_a_disp[] = "basis_a:";
char offset_b_disp[] = "basis_b:";
char offset_c_disp[] = "basis_c:";
char p_a_disp[] = "kp_a:";
char p_b_disp[] = "kp_b:";
char p_c_disp[] = "kp_c:";
char i_a_disp[] = "ki_a:";
char i_b_disp[] = "ki_b:";
char i_c_disp[] = "ki_c:";
char d_a_disp[] = "kd_a:";
char d_b_disp[] = "kd_b:";
char d_c_disp[] = "kd_c:";
char up_a_disp[] = "up_a:";
char up_b_disp[] = "up_b:";
char up_c_disp[] = "up_c:";
char down_a_disp[] = "down_a:";
char down_b_disp[] = "down_b:";
char down_c_disp[] = "down_c:";
char para_input[] = "Input the parameters name:";
char new_value[] = "Input a new value[0,65535]:";
char new_fvalue[] = "Input a new value[xxxx.xxx]:";
char inv_pass[] = "Invalid password";
char input_erro[]= "Invalid data";
char invalid_com[] = "Invalid command";
char disconnect[] = "You can disconnect the cable now...";


char sci_receive[20];
char send[40];
unsigned int sci_i = 0;
unsigned int pass_flag = 255;
unsigned int para_sele = 0;


extern unsigned int node;
extern unsigned int ref_value;
extern unsigned int offset_a,offset_b,offset_c;
extern unsigned int up_a,up_b,up_c;
extern unsigned int down_a,down_b,down_c;
extern unsigned int state;
extern float scale;
extern float kp_a,kp_b,kp_c;
extern float ki_a,ki_b,ki_c;
extern float kd_a,kd_b,kd_c;


extern void wr_word(unsigned int addr,unsigned int dwd);
extern void wr_float(unsigned int,float);
extern unsigned int rd_word(unsigned int);
extern float rd_float(unsigned int);
extern void disable_WD(void);
extern void clean_IFR(void);
extern void inline int_enable(void);
extern void delay(unsigned int);

 
void SCI_INIT(void){

	*((volatile int *)0x7050) = 0x7;
    *((volatile int *)0x7051) = 0x13;
	*((volatile int *)0x7054) = 0x02;
	*((volatile int *)0x7052) = 0x0;
    *((volatile int *)0x7053) = 0xC2;
	*((volatile int *)0x7051) = 0x33;
	*((volatile int *)0x705F) = 0x61;
}

 

void UartSent(char send){
	
	unsigned long i;
	

	
	while(!(*((volatile int *)0x7054) & 0x80));
	*((volatile int *)0x7059) = send;
	
	clean_IFR();

}

 

void UartSent_str(char *send){

	unsigned int i;
	

	
	for(i=0;i<(strlen(send));i++) UartSent(send[i]);
	

}

 


void UartRec(char *receive,unsigned int flag){
	

	*receive =  *((volatile int *)0x7057);
	clean_IFR();
	int_enable();
	if(1 == flag){
		UartSent('*');
	}
	else{
		UartSent(*receive);
	}
}


 


unsigned int strtoint(char *str,unsigned int *pint){
	
	unsigned int i,r;
	unsigned long sum;
	
	sum = 0;
	for(i = 0;i < (strlen(str)-1);i++){
		if((str[i]<48) || (str[i]>57) || (strlen(str)>6)){
			r = 0;
			break;
		}
		else{
			r = 1;
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
	else{
		d = 0;
	}
	return(d);
}

 



unsigned int hextostr(unsigned int data,char *str)
{
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
	if(temp < 1){
		str[0] = '0';
		str[1] = '.';
		str[2] = '0';
		str[3] = '\0';
	}
	else if(temp < 10){
		str[1] = '0';
		str[2] = '.';
		str[3] = '0';
		str[4] = '0';
		str[5] = temp + 48;
		str[6] = '\0';
	}
	else if(temp < 100){
		str[1] = '0';
		str[2] = '.';
		str[3] = '0';
		str[4] = temp/10 + 48;
		str[5] = temp%10 + 48;
		str[6] = '\0';
	}		
	else if(temp < 1000){
		str[1] = '0';
		str[2] = '.';
		str[3] = temp/100 +48;
		temp = temp % 100;
		str[4] = temp/10 + 48;
		str[5] = temp%10 + 48;
		str[6] = '\0';
	}		
	else if(temp < 10000){
		str[1] = temp/1000 + 48;
		temp = temp % 1000;
		str[2] = '.';
		str[3] = temp/100 + 48;
		temp = temp % 100;
		str[4] = temp/10 +48;
		str[5] = temp%10 + 48;
		str[6] = '\0';
	}		
	else if(temp < 100000){
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
	else if(temp < 1000000){
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
	else if(temp < 10000000){
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
	else{
		str[0] = 'e';
		str[1] = 'r';
		str[2] = 'r';
		str[3] = 'o';
		str[4] = 'r';
		str[5] = '\0';
	}
}

 



void one_para_disp(char *str,unsigned int value){

	strcpy(send,str);
	UartSent_str(send);
	
	if(inttostr(value,send))
		UartSent_str(send);
	else
		UartSent_str("!");
}

 



void float_disp(char *str,float value){
	
	strcpy(send,str);
	UartSent_str(send);
	
	floattostr(value,send);
	UartSent_str(send);
}

 
void value_display(void){

	strcpy(send,current_value);
	UartSent_str(send);
	strcpy(send,c_row);
	UartSent_str(send);
	
	one_para_disp(node_disp,node);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(limen_disp,ref_value);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(scale_disp,scale);
	strcpy(send,c_row);
	UartSent_str(send);
	
	one_para_disp(offset_a_disp,offset_a);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(offset_b_disp,offset_b);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(offset_c_disp,offset_c);
	strcpy(send,c_row);
	UartSent_str(send);
	
	float_disp(p_a_disp,kp_a);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(p_b_disp,kp_b);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(p_c_disp,kp_c);
	strcpy(send,c_row);
	UartSent_str(send);
	
	float_disp(i_a_disp,ki_a);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(i_b_disp,ki_b);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(i_c_disp,ki_c);
	strcpy(send,c_row);
	UartSent_str(send);
	
	float_disp(d_a_disp,kd_a);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(d_b_disp,kd_b);
	strcpy(send,table);
	UartSent_str(send);
	float_disp(d_c_disp,kd_c);
	strcpy(send,c_row);
	UartSent_str(send);
	
	one_para_disp(up_a_disp,up_a);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(up_b_disp,up_b);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(up_c_disp,up_c);
	strcpy(send,c_row);
	UartSent_str(send);
	
	one_para_disp(down_a_disp,down_a);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(down_b_disp,down_b);
	strcpy(send,table);
	UartSent_str(send);
	one_para_disp(down_c_disp,down_c);
	strcpy(send,c_row);
	UartSent_str(send);
	
	strcpy(send,vcp);
	UartSent_str(send);
}

 
 
void edit_para(void){

	if(!strcmp(node_str,sci_receive)){
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
		para_sele = 1;
	}
	else if(!strcmp(limen_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(limen_disp,ref_value);
		
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
		para_sele = 2;
	}
	else if(!strcmp(kpa_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(p_a_disp,kp_a);
		
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
		para_sele = 3;
	}
	else if(!strcmp(kpb_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(p_b_disp,kp_b);
		
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
		para_sele = 4;
	}
	else if(!strcmp(kpc_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(p_c_disp,kp_c);
		
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
		para_sele = 5;
	}

	else if(!strcmp(kia_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(i_a_disp,ki_a);
		
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
		para_sele = 6;
	}
	else if(!strcmp(kib_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(i_b_disp,ki_b);
		
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
		para_sele = 7;
	}
	else if(!strcmp(kic_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(i_c_disp,ki_c);
		
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
		para_sele = 8;
	}
	else if(!strcmp(kda_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(d_a_disp,kd_a);
		
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
		para_sele = 9;
	}
	else if(!strcmp(kdb_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(d_b_disp,kd_b);
		
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
		para_sele = 10;
	}
	else if(!strcmp(kdc_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(d_c_disp,kd_c);
		
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
		para_sele = 11;
	}
	else if(!strcmp(upa_str,sci_receive)){
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
		para_sele = 12;
	}
	else if(!strcmp(upb_str,sci_receive)){
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
		para_sele = 13;
	}
	else if(!strcmp(upc_str,sci_receive)){
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
		para_sele = 14;
	}
	else if(!strcmp(downa_str,sci_receive)){
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
		para_sele = 15;
	}
	else if(!strcmp(downb_str,sci_receive)){
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
		para_sele = 16;
	}
	else if(!strcmp(downc_str,sci_receive)){
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
		para_sele = 17;
	}
	else if(!strcmp(offseta_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(offset_a_disp,offset_a);
		
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
		para_sele = 18;
	}
	else if(!strcmp(offsetb_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(offset_b_disp,offset_b);
		
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
		para_sele = 19;
	}
	else if(!strcmp(offsetc_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		one_para_disp(offset_c_disp,offset_c);
		
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
		para_sele = 20;
	}
	else if(!strcmp(scale_str,sci_receive)){
		strcpy(send,vcpset);
		UartSent_str(send);
		
		float_disp(scale_disp,scale);
		
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
		para_sele = 21;
	}
	else if(!strcmp(quit_str,sci_receive)){
		strcpy(send,vcp);
		UartSent_str(send);
		pass_flag = 0;
		para_sele = 0;
	}	
	else{
		sci_i = 0;
		strcpy(send,vcpset);
		UartSent_str(send);
		strcpy(send,fail_in);
		UartSent_str(send);
		strcpy(send,vcpset);
		UartSent_str(send);
	}	
}
 
 
void save_para(void){

	unsigned int temp;
	float ftemp;
	
	switch(para_sele){
		case 1:
			if(strtoint(sci_receive,&temp)){
				wr_word(120,temp);
				node = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(node_disp,node);
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
		case 2:
			if(strtoint(sci_receive,&temp)){
				wr_word(118,temp);
				ref_value = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(limen_disp,ref_value);
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
		case 3:
			ftemp = atof(sci_receive);
			wr_float(204,ftemp);
			kp_a = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(p_a_disp,kp_a);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 4:
			ftemp = atof(sci_receive);
			wr_float(208,ftemp);
			kp_b = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(p_b_disp,kp_b);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 5:
			ftemp = atof(sci_receive);
			wr_float(212,ftemp);
			kp_c = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(p_c_disp,kp_c);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 6:
			ftemp = atof(sci_receive);
			wr_float(216,ftemp);
			ki_a = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(i_a_disp,ki_a);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 7:
			ftemp = atof(sci_receive);
			wr_float(220,ftemp);
			ki_b = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(i_b_disp,ki_b);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 8:
			ftemp = atof(sci_receive);
			wr_float(224,ftemp);
			ki_c = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(i_c_disp,ki_c);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 9:
			ftemp = atof(sci_receive);
			wr_float(228,ftemp);
			kd_a = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(d_a_disp,kd_a);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 10:
			ftemp = atof(sci_receive);
			wr_float(232,ftemp);
			kd_b = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(d_b_disp,kd_b);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 11:
			ftemp = atof(sci_receive);
			wr_float(236,ftemp);
			kd_c = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(d_c_disp,kd_c);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		case 12:
			if(strtoint(sci_receive,&temp)){
				wr_word(100,temp);
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
		case 13:
			if(strtoint(sci_receive,&temp)){
				wr_word(102,temp);
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
		case 14:
			if(strtoint(sci_receive,&temp)){
				wr_word(104,temp);
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
		case 15:
			if(strtoint(sci_receive,&temp)){
				wr_word(106,temp);
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
		case 16:
			if(strtoint(sci_receive,&temp)){
				wr_word(108,temp);
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
		case 17:
			if(strtoint(sci_receive,&temp)){
				wr_word(110,temp);
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
		case 18:
			if(strtoint(sci_receive,&temp)){
				wr_word(112,temp);
				offset_a = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(offset_a_disp,offset_a);
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
		case 19:
			if(strtoint(sci_receive,&temp)){
				wr_word(114,temp);
				offset_b = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(offset_b_disp,offset_b);
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
		case 20:
			if(strtoint(sci_receive,&temp)){
				wr_word(116,temp);
				offset_c = temp;
				para_sele = 0;
				pass_flag = 2;
				one_para_disp(offset_c_disp,offset_c);
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
		case 21:
			ftemp = atof(sci_receive);
			wr_float(200,ftemp);
			scale = ftemp;
			para_sele = 0;
			pass_flag = 2;
			float_disp(scale_disp,scale);
			strcpy(send,c_row);
			UartSent_str(send);
			break;
		default: break;
	}
}

 
void sci_server(void){

	unsigned int temp;
	
	UartRec(&sci_receive[sci_i++],pass_flag);
	sci_receive[sci_i] = '\0';
	
	if('\r' == sci_receive[sci_i-1]){
		sci_i = 0;
		strcpy(send,c_row);
		UartSent_str(send);
		switch(pass_flag){
			case 0:
				if(!strcmp(set_str,sci_receive)){
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,pass);
					UartSent_str(send);
					pass_flag = 1;
				}
				else if(!strcmp(list_str,sci_receive)){
					strcpy(send,state_val);
					UartSent_str(send);
					temp = state;
					if(hextostr(temp,send))
						UartSent_str(send);
					else
						UartSent_str("255");
					strcpy(send,c_row);
					UartSent_str(send);
					value_display();
				}
				else if(!strcmp(quit_str,sci_receive)){
					strcpy(send,disconnect);
					UartSent_str(send);
					pass_flag = 0;
				}
				else{
					strcpy(send,vcp);
					UartSent_str(send);
					strcpy(send,invalid_com);
					UartSent_str(send);
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,vcp);
					UartSent_str(send);
				}
				
				break;
			case 1:
				if(!strcmp(password,sci_receive)){
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
					
					strcpy(send,para_input);
					UartSent_str(send);
					strcpy(send,c_row);
					UartSent_str(send);
					strcpy(send,vcpset);
					UartSent_str(send);
					pass_flag = 2;
				}
				else{
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
			case 2:
				edit_para();
				break;
			case 3:
				if(!strcmp(cancel_str,sci_receive)){
					strcpy(send,vcpset);
					UartSent_str(send);
					para_sele = 0;
					pass_flag = 2;
				}
				else if(strlen(sci_receive) > 1){
					strcpy(send,vcpset);
					UartSent_str(send);
					save_para();
					strcpy(send,vcpset);
					UartSent_str(send);
				}
				else{
					strcpy(send,vcpset);
					UartSent_str(send);
				}
				break;
			default: break;
		}	
	}
	
	if(sci_i > 9){
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

 
void serieal_logo(void){

	if(0x2000&state){
		if(255 == pass_flag){
			delay(3000);
			strcpy(send,description);
			UartSent_str(send);
			strcpy(send,connected);
			UartSent_str(send);
			strcpy(send,vcp);
			UartSent_str(send);
			pass_flag = 0;
		}
	}
	else
		pass_flag = 255;
}



