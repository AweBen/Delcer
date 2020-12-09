/* ================================================================================== 
File name:        F24x_WD.H                      
                     
Originator:	Digital Control Systems Group 
			Texas Instruments 
Description:   
Driver Interface header for the Watchdog. 
===================================================================================== 
 History: 
------------------------------------------------------------------------------------- 
 9-15-2000	Release	Rev 1.00                                                   
---------------------------------------------------------------------------------- */ 
 
#ifndef __F24x_WD_H__ 
#define __F24x_WD_H__   
  
/*----------------------------------------------------------------------------- 
Define the Watchdog Driver Interface 
-----------------------------------------------------------------------------*/ 
typedef struct {    
        int  (*disable)(); 
        int  (*reset)(); 
        } WATCHDOG ; 
 
/*----------------------------------------------------------------------------- 
Define a WATCHDOG handle 
-----------------------------------------------------------------------------*/ 
typedef WATCHDOG *WATCHDOG_handle; 
                                          
 
 
/*----------------------------------------------------------------------------- 
Default Initializer for the F243 PWMGEN Object  
-----------------------------------------------------------------------------*/ 
#define F24X_WD_DEFAULTS {                                  \ 
                         (int (*)(int))F24x_WD_Disable,     \ 
                         (int (*)(int))F24x_WD_ResetCounter \ 
                         }       
                          
#define WATCHDOG_DEFAULTS  F24X_WD_DEFAULTS 
 
void F24x_WD_ResetCounter(void); 
void F24x_WD_Disable(void); 
 
#endif /* __F24x_WD_H__ */