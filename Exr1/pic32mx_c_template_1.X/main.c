/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */
#include "Tick.h" 
#include "HWP OLIMEX_PIC32-WEB.h"


//#define PROBLEM1
#define PROBLEM2    

void delay(uint32_t period)
{
    int i;
    for(i = 0 ; i < period ; i++);
}

int32_t main(void)
{

#ifndef PIC32_STARTER_KIT
    /*The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
    for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
    to free up the JTAG I/O */
    DDPCONbits.JTAGEN = 0;
#endif

    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.
    
    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:
    
    SYS_CFG_WAIT_STATES (configures flash wait states from system clock)
    SYS_CFG_PB_BUS (configures the PB bus from the system clock)
    SYS_CFG_PCACHE (configures the pCache if used)
    SYS_CFG_ALL (configures the flash wait states, PB bus, and pCache)*/

    /* TODO Add user clock/system configuration code if appropriate.  */
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL); 

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /*Configure Multivector Interrupt Mode.  Using Single Vector Mode
    is expensive from a timing perspective, so most applications
    should probably not use a Single Vector Mode*/
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    LED0_TRIS = 0; // Data direction register LED 1
    LED1_TRIS = 0; // Data direction register LED 2
    LED2_TRIS = 0; // Data direction register LED 3
    LED0_IO = 1; // I/O register LED 1
    LED1_IO = 1; // I/O register LED 2
    LED2_IO = 1; // I/O register LED 3
    BUTTON0_TRIS = 1; // Button 1 data direction register
    BUTTON1_TRIS = 1; // Button 1 data direction register
    BUTTON2_TRIS = 1; // Button 1 data direction register
    TickInit();
    while(1)
    {

#ifdef PROBLEM1
        /* problem 1 
         80MHz clock frequency
         1 / 80MHz = period of a single CPU instruction
         250ms desired period
         250 / ( 1/80MHz ) gives us the desired delay*/
        delay(2000000);
            mPORTDToggleBits(BIT_0);
            mPORTDToggleBits(BIT_1);
            mPORTDToggleBits(BIT_2);
#endif
            
#ifdef PROBLEM2
        while(1)
        {
            if (BUTTON0_IO == 0)
            {
             delay(2);
             if (BUTTON0_IO == 0)
             {
              mPORTDToggleBits(BIT_0);  
             }
            }
            if (BUTTON1_IO == 0)
            {
                delay(2);
              if (BUTTON1_IO == 0)
              {
                mPORTDToggleBits(BIT_1);  
              }
            }

            if (BUTTON2_IO == 0)
            {
                delay(2);
              if (BUTTON2_IO == 0)
              {
                mPORTDToggleBits(BIT_2);  
              }
            }
        }
#endif

        }        
}