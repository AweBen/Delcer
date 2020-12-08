/*
// TI File $Revision: /main/9 $
// Checkin $Date: August 28, 2007   11:23:31 $
//###########################################################################
//
// FILE:    28335_RAM_lnk.cmd
//
// TITLE:   Linker Command File For 28335 examples that run out of RAM
//
//          This ONLY includes all SARAM blocks on the 28335 device.
//          This does not include flash or OTP. 
//
//          Keep in mind that L0 and L1 are protected by the code
//          security module.
//
//          What this means is in most cases you will want to move to 
//          another memory map file which has more memory defined.  
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################
*/

/* ======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file, 
// add the header linker command file directly to the project. 
// The header linker command file is required to link the
// peripheral structures to the proper locations within 
// the memory map.
//
// The header linker files are found in <base>\DSP2833x_Headers\cmd
//   
// For BIOS applications add:      DSP2833x_Headers_BIOS.cmd
// For nonBIOS applications add:   DSP2833x_Headers_nonBIOS.cmd    
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the 
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper 
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l DSP2833x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l DSP2833x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\DSP2833x_headers\cmd to the
   library search path under project->build options, linker tab, 
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the F28335  
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes: 
         Memory blocks on F28335 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.  
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program 
         and/or data. 
         
         L0/L1/L2 and L3 memory blocks are mirrored - that is
         they can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file. 
         
         Contiguous SARAM memory blocks can be combined 
         if required to create a larger memory block. 
*/


MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode      */
   /* BOOT_RSVD is used by the boot ROM for stack.               */
   /* This section is only reserved to keep the BOOT ROM from    */
   /* corrupting this area during the debug process              */
   
   BEGIN      : origin = 0x000000, length = 0x000002    /* Boot to M0 will go here                      */
   BOOT_RSVD  : origin = 0x000002, length = 0x00004E    /* Part of M0, BOOT rom will use this for stack */               
   RAMM0      : origin = 0x000050, length = 0x0003B0
   RAML01     : origin = 0x008000, length = 0x002000    
   RAML23     : origin = 0x00A000, length = 0x002000    /*creat large block RAM.*/
   ZONE6A     : origin = 0x100000, length = 0x00FC00    /* XINTF zone 6 - program space */ 
   CSM_RSVD   : origin = 0x33FF80, length = 0x000076    /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   CSM_PWL    : origin = 0x33FFF8, length = 0x000008    /* Part of FLASHA.  CSM password locations in FLASHA            */
   ADC_CAL    : origin = 0x380080, length = 0x000009
   RESET      : origin = 0x3FFFC0, length = 0x000002
   IQTABLES   : origin = 0x3FE000, length = 0x000b50
   IQTABLES2  : origin = 0x3FEB50, length = 0x00008c
   FPUTABLES  : origin = 0x3FEBDC, length = 0x0006A0
   BOOTROM    : origin = 0x3FF27C, length = 0x000D44               

         
PAGE 1 : 
   RAMM1      : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML45     : origin = 0x00C000, length = 0x002000    
   RAML6      : origin = 0x00E000, length = 0x001000
   RAML7      : origin = 0x00F000, length = 0x000D00 
   ADCRES     : origin = 0x00FD00, length = 0x000100
   RAMXCHG1   : origin = 0x00FE00, length = 0x000100     /*for Dpram data down,256 words.*/
   RAMXCHG2   : origin = 0x00FF00, length = 0x000100     /*for Dpram data up,256 words.*/

   DPRAM_UP   : origin = 0x100100, length = 0x000064     /* XINTF zone 6 - dpram up data space */
   DPRAM_DN   : origin = 0x100800, length = 0x000064     /* XINTF zone 6 - dpram down data space */
   SEM0_ADDR  : origin = 0x101000, length = 0x000001
   SEM1_ADDR  : origin = 0x101001, length = 0x000001
   AD7656     : origin = 0x102000, length = 0x000001
   ZONE6B     : origin = 0x10FC00, length = 0x000400     /* XINTF zone 6 - data space */

   CPLD_ADDR  : origin = 0x200000, length = 0x000004
}
 
 
SECTIONS
{
   /* Setup for "boot to SARAM" mode: 
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAML01,    PAGE = 0  
   .text            : > RAML23,    PAGE = 0	/*program code section.*/
   .cinit           : > RAML01,    PAGE = 0
   .pinit           : > RAML01,    PAGE = 0
   .switch          : > RAML01,    PAGE = 0
   
   .stack           : > RAMM1,     PAGE = 1
   .ebss            : > RAML45,    PAGE = 1
   .econst          : > RAML7,     PAGE = 1
   .esysmem         : > RAMM1,     PAGE = 1

   IQmath           : > RAML01,    PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD 
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD 
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD 

   /*DMA Accessible SARAM space*/
   CODE_TABLE       : > RAML6,      PAGE = 1 /*data table stored.*/
   ADC28335         : > ADCRES,     PAGE = 1 /*0xFD00 ~ 0xFDFF*/
   DMARAMUP         : > RAMXCHG1,   PAGE = 1 /*0xFE00 ~ 0xFEFF*/
   DMARAMDN         : > RAMXCHG2,   PAGE = 1 /*0XFF00 ~ 0xFFFF*/
   
   /*Zone 6 space*/
   ZONE6DATA        : > ZONE6B,     PAGE = 1 /*0x10,0000 ~ 0X1F,FFFF*/
   DPRAM_UP_DATA	: > DPRAM_UP,	PAGE = 1 /*0x10,0100 ~ 0x10,0163*/
   DPRAM_DN_DATA	: > DPRAM_DN,	PAGE = 1 /*0x10,0800 ~ 0x10,0863*/
   SEM0				: > SEM0_ADDR,  PAGE = 1 /*0x10,1000*/
   SEM1             : > SEM1_ADDR,  PAGE = 1 /*0x10,1001*/
   AD7656_CS        : > AD7656,		PAGE = 1 /*0x10,2000*/

   /*Zone 7 space*/
   CPLD_VAR         : > CPLD_ADDR,  PAGE = 1 /*0x20,0000 ~ 0x20,0003*/


   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used                    */
   csm_rsvd         : > CSM_RSVD   PAGE = 0, TYPE = DSECT /* not used for SARAM examples */
   csmpasswds       : > CSM_PWL    PAGE = 0, TYPE = DSECT /* not used for SARAM examples */
   
   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD
     
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
