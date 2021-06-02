/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 27 2020                              */
/*********************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

/* CHOOSE TIMER CLOCK SOURCE AND DISABLE TMR AND TMR INT */
void STK_voidInit(void);
/* SYNCHRONOUS FUNCTION (DELAY) */
void STK_voidSetBusyWait(u32 copy_u32Ticks);
/* ASYNCHRONOUS FUNCTION TO MAKE ITERRUPT FOR A SINGLE TIME */
void STK_voidSetIntervalSingle(u32 copy_u32Ticks , void (*copy_ptr)(void) );
/* ASYNCHRONOUS FUNCTION TO MAKE ITERRUPT FOR MULTIPLE TIMES (PERIODIC) */
void STK_voidSetIntervalPeriodic(u32 copy_u32Ticks , void (*copy_ptr)(void) );
/* GET THE TIME FROM THR STAT TO A SPECEFIC MOMENT */
u32 STK_u32GetElapsedTime(void);
/* GET THE TIME REMAINING BEFORE ITERRUPT */
u32 STK_u32GetRemainingTime(void);
void STK_voidStopTimer(void);
void STK_voidResetTimer(void);
void STK_voidSetCallBack(void (*ptr) (void));

#endif


