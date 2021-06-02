/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 27 2020                              */
/*********************************************************/


#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

typedef struct{
	volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
}SysTck;
#define STK ((volatile SysTck *)0xE000E010)
/*  */
#define Enable_TMR     0
#define TMR_INT        1
#define TMR_CLK        2
#define TMR_FLAG       16 
/**/
#define SINGLE_INT              1
#define PERIODIC_INT            2




#endif



