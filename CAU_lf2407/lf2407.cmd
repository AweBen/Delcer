
 -stack 80h
 -l rts2xx.lib


 MEMORY
{
    PAGE 0 :   VECS   : origin =    0h , length =   040h   /* VECTORS */
	           PROG   : origin =  100h , length =  7F00h   /* PROGRAM */

			   DPRAM_UP	: origin = 0F100h , length = 700h	/* Dpram */
			   DPRAM_DN : origin = 0F800h , length = 800h	/* Dpram */

    PAGE 1 :   MMRS   : origin =    0h , length =   060h   /* MMRS    */
               B2     : origin = 0060h , length =   020h   /* DARAM   */
               B0     : origin = 0200h , length =  0100h   /* DARAM   */
               B1     : origin = 0300h , length =  0100h   /* DARAM   */
               SARAM  : origin = 0800h , length =  0800h   /* SARAM   */
               DATA   : origin = 8000h , length =  8000h   /* XDM     */

}

/*--------------------------------------------------------------------*/
/* SECTIONS ALLOCATION                                                */
/*--------------------------------------------------------------------*/
 SECTIONS
{
    .reset   : { } > VECS      PAGE 0 	/* 复位中断向量表             */
    .vectors : { } > VECS      PAGE 0   /* Interrupt vector table     */
    .text    : { } > PROG      PAGE 0   /* Code                       */
    .cinit   : { } > PROG      PAGE 0   
    .mmrs    : { } > MMRS      PAGE 1   /* Memory mapped registers    */
    .bss     : { } > SARAM     PAGE 1   
    .const   : { } > SARAM	   PAGE 1
    .stack   : { } > B1 	   PAGE 1
    .sysmem  : { } > B0 	   PAGE 1

	dpram_up	: > DPRAM_UP,	PAGE = 0
	dpram_dn	: > DPRAM_DN,	PAGE = 0
}



