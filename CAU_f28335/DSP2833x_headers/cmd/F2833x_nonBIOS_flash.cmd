/*############################################################################

 FILE:   DSP2833x_nonBIOS_flash.cmd

 DESCRIPTION:  Linker allocation for all sections. 
############################################################################
 Author: Tim Love
 Release Date: 	March 2008
############################################################################*/


MEMORY
{
PAGE 0:    /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */

	ZONE0       : origin = 0x004000, length = 0x001000     /* XINTF zone 0 */
	RAM_L0L1L2L3: origin = 0x008000, length = 0x004000	   /* on-chip RAM */
   	OTP         : origin = 0x380400, length = 0x000400     /* on-chip OTP */
    ZONE6       : origin = 0x100000, length = 0x100000     /* XINTF zone 6 */ 
    ZONE7A      : origin = 0x200000, length = 0x00FC00     /* XINTF zone 7 - program space */
   	FLASHH      : origin = 0x300000, length = 0x008000     /* on-chip FLASH */
    FLASHG      : origin = 0x308000, length = 0x008000     /* on-chip FLASH */
    FLASHF      : origin = 0x310000, length = 0x008000     /* on-chip FLASH */
    FLASHE      : origin = 0x318000, length = 0x008000     /* on-chip FLASH */
    FLASHD      : origin = 0x320000, length = 0x008000     /* on-chip FLASH */
    FLASHC      : origin = 0x328000, length = 0x008000     /* on-chip FLASH */
    FLASHA      : origin = 0x338000, length = 0x007F80     /* on-chip FLASH */
    CSM_RSVD    : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */

    BEGIN_FLASH : origin = 0x33FFF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
    CSM_PWL     : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
    ADC_CAL     : origin = 0x380080, length = 0x000009	   /* Part of TI OTP */
    IQTABLES    : origin = 0x3FE000, length = 0x000b50     /* IQ Math Tables in Boot ROM */
    IQTABLES2   : origin = 0x3FEB50, length = 0x00008c     /* IQ Math Tables in Boot ROM */  
    FPUTABLES   : origin = 0x3FEBDC, length = 0x0006A0     /* FPU Tables in Boot ROM */
    ROM         : origin = 0x3FF27C, length = 0x000D44     /* Boot ROM */

   	RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   	VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */


PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */

   	RAMM0       : origin = 0x000000, length = 0x000400     /* on-chip RAM block M0 */
   	BOOT_RSVD   : origin = 0x000400, length = 0x000080     /* Part of M1, BOOT rom will use this for stack */
   	RAMM1       : origin = 0x000480, length = 0x000380     /* on-chip RAM block M1 */

	RAML45      : origin = 0x00C000, length = 0x002000
	RAML6       : origin = 0x00E000, length = 0x001000     /* on-chip RAM block L6 */
	RAML7       : origin = 0x00F000, length = 0x000D00     /* on-chip RAM block L7 */
	ADCRES      : origin = 0x00FD00, length = 0x000100
	RAMXCHG1    : origin = 0x00FE00, length = 0x000100
	RAMXCHG2    : origin = 0x00FF00, length = 0x000100

	DPRAM_UP    : origin = 0x100100, length = 0x000064
	DPRAM_DN    : origin = 0x100800, length = 0x000064
	SEM0_ADDR   : origin = 0x101000, length = 0x000001
	SEM1_ADDR   : origin = 0x101001, length = 0x000001
	AD7656      : origin = 0x102000, length = 0x000001
	CPLD_ADDR   : origin = 0x200000, length = 0x000004

    ZONE7B      : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */
}

/**************************************************************/
/* Link all user defined sections                             */
/**************************************************************/
SECTIONS
{

/*** Code Security Password Locations ***/
   	csmpasswds      : > CSM_PWL     	PAGE = 0
   	csm_rsvd        : > CSM_RSVD    	PAGE = 0

/*** User Defined Sections ***/
   	codestart       : > BEGIN_FLASH,	PAGE = 0        /* Used by file CodeStartBranch.asm */
   	wddisable		: > FLASHA,			PAGE = 0	
  	copysections	: > FLASHA,			PAGE = 0

	 /* Allocate IQ math areas: */
   IQmath           : > FLASHC     		PAGE = 0        /* Math Code */
   IQmathTables     : > IQTABLES,  		PAGE = 0, TYPE = NOLOAD 
   IQmathTables2    : > IQTABLES2, 		PAGE = 0, TYPE = NOLOAD 
   FPUmathTables    : > FPUTABLES, 		PAGE = 0, TYPE = NOLOAD 
         
   /* Allocate DMA-accessible RAM sections: */
	CODE_TABLE      : > RAML6,          PAGE = 1
	ADC28335        : > ADCRES,         PAGE = 1
	DMARAMUP        : > RAMXCHG1,       PAGE = 1
	DMARAMDN        : > RAMXCHG2,       PAGE = 1

	DPRAM_UP_DATA   : > DPRAM_UP,       PAGE = 1
	DPRAM_DN_DATA   : > DPRAM_DN,       PAGE = 1
	SEM0            : > SEM0_ADDR,      PAGE = 1
	SEM1            : > SEM1_ADDR,      PAGE = 1
	AD7656_CS       : > AD7656,         PAGE = 1

	CPLD_VAR        : > CPLD_ADDR,      PAGE = 1

   /* Allocate 0x400 of XINTF Zone 7 to storing data */
   ZONE7DATA        : > ZONE7B,    		PAGE = 1

/* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     	: load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD 

/* .reset is a standard section used by the compiler.  It contains the */ 
/* the address of the start of _c_int00 for C Code.   /*
/* When using the boot ROM this section and the CPU vector */
/* table is not needed.  Thus the default type is set here to  */
/* DSECT  */ 
	.reset         	: > RESET,      	PAGE = 0, TYPE = DSECT
	vectors         : > VECTORS     	PAGE = 0, TYPE = DSECT

/*** Uninitialized Sections ***/
   	.stack          : > RAMM0       	PAGE = 1
   	.ebss           : > RAML45       	PAGE = 1
   	.esysmem        : > RAMM1       	PAGE = 1


/*** Initialized Sections ***/                                          
  	.cinit			:	LOAD = FLASHA,		PAGE = 0        /* can be ROM */ 
                		RUN = RAM_L0L1L2L3, PAGE = 0   		/* must be CSM secured RAM */
                		LOAD_START(_cinit_loadstart),
                		RUN_START(_cinit_runstart),
                		SIZE(_cinit_size)

	.const			:   LOAD = FLASHA,  	PAGE = 0        /* can be ROM */ 
                		RUN = RAM_L0L1L2L3,	PAGE = 0        /* must be CSM secured RAM */
                		LOAD_START(_const_loadstart),
                		RUN_START(_const_runstart),
                		SIZE(_const_size)

	.econst			:   LOAD = FLASHA,  	PAGE = 0        /* can be ROM */ 
                		RUN = RAM_L0L1L2L3, PAGE = 0        /* must be CSM secured RAM */
                		LOAD_START(_econst_loadstart),
               			RUN_START(_econst_runstart),
                		SIZE(_econst_size)

	.pinit			:   LOAD = FLASHA,  	PAGE = 0        /* can be ROM */ 
                		RUN = RAM_L0L1L2L3, PAGE = 0        /* must be CSM secured RAM */
                		LOAD_START(_pinit_loadstart),
                		RUN_START(_pinit_runstart),
                		SIZE(_pinit_size)

	.switch			:   LOAD = FLASHA,  	PAGE = 0        /* can be ROM */ 
                		RUN = RAM_L0L1L2L3, PAGE = 0        /* must be CSM secured RAM */
                		LOAD_START(_switch_loadstart),
                		RUN_START(_switch_runstart),
                		SIZE(_switch_size)

	.text			:   LOAD = FLASHA, 		PAGE = 0        /* can be ROM */ 
                		RUN = RAM_L0L1L2L3, PAGE = 0        /* must be CSM secured RAM */
                		LOAD_START(_text_loadstart),
                		RUN_START(_text_runstart),
                		SIZE(_text_size)
}

/******************* end of file ************************/
