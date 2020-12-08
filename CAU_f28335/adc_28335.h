// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x1   // ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
#define ADC_SHCLK  0xf   // S/H width in ADC module periods                        = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   160    // Sample buffer size

#define ADCINA0		0x0
#define ADCINA1		0x1
#define ADCINA2		0x2
#define ADCINA3		0x3
#define ADCINA4		0x4
#define ADCINA5		0x5
#define ADCINA6		0x6
#define ADCINA7		0x7
#define ADCINB0		0x8
#define ADCINB1		0x9
#define ADCINB2		0xA
#define ADCINB3		0xB
#define ADCINB4		0xC
#define ADCINB5		0xD
#define ADCINB6		0xE
#define ADCINB7		0xF



struct I_TCR{

	unsigned int tcr_iab_1;
	unsigned int tcr_iab_2;
	unsigned int tcr_iab_3;
	unsigned int tcr_iab_4;
	unsigned int tcr_iab_5;
	unsigned int tcr_ibc_1;
	unsigned int tcr_ibc_2;
	unsigned int tcr_ibc_3;
	unsigned int tcr_ibc_4;
	unsigned int tcr_ibc_5;
	unsigned int tcr_ica_1;
	unsigned int tcr_ica_2;
	unsigned int tcr_ica_3;
	unsigned int tcr_ica_4;
	unsigned int tcr_ica_5;
	unsigned int zero;
};






//end of file

