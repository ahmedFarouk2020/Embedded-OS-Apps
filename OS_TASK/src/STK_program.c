/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 27 2020                              */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_private.h"
#include "STK_interface.h"

/* GLOBAL VAR. FOR CALLBACK FN. */
void (*STK_CALLBACK) (void);
/**/
static u8 STK_u8Identifier;
/* ISR FOR SYSTICK */
void SysTick_Handler(void)
{
	STK_CALLBACK();
	if(STK_u8Identifier == SINGLE_INT)
	{
		CLR_BIT(STK -> CTRL , TMR_INT);
		CLR_BIT(STK -> CTRL , Enable_TMR);
		STK -> LOAD = 0;
		STK -> VAL  = 0;
	}
	else if(STK_u8Identifier == PERIODIC_INT)
	{
/*THIS WAY TO CLR THE FLAG IS NOT SUFFICIENT THE BEST IS TO READ IT */
		STK -> VAL  = 0;
	}
}

void STK_voidInit(void)
{
	/* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
	STK -> CTRL = 0;
}

void STK_voidSetBusyWait(u32 copy_u32Ticks)
{
	STK -> LOAD = copy_u32Ticks;
	SET_BIT(STK -> CTRL , Enable_TMR);
	while((GET_BIT( STK->CTRL , TMR_FLAG)) == 0 );
	CLR_BIT(STK -> CTRL , Enable_TMR);
	STK -> LOAD = 0;
	STK -> VAL  = 0;

}
/*THE FUCTION THAT IS SENT AS AN ARGUMENT WILL DETERMINE WHETHER 
 *THE FUNC IS SINGLE OR PERIODIC
 */ 
void STK_voidSetIntervalSingle(u32 copy_u32Ticks , void (*copy_ptr)(void) )
{
	STK -> LOAD = copy_u32Ticks;
	STK_CALLBACK = copy_ptr;
	STK_u8Identifier = SINGLE_INT;
	SET_BIT(STK -> CTRL , Enable_TMR);
	SET_BIT(STK -> CTRL , TMR_INT);
}
//                        LIKE      100000000          &FUNC
void STK_voidSetIntervalPeriodic(u32 copy_u32Ticks , void (*copy_ptr)(void) )
{
	STK -> LOAD = copy_u32Ticks;
	STK_CALLBACK = copy_ptr;
    STK_u8Identifier = PERIODIC_INT;
	SET_BIT(STK -> CTRL , Enable_TMR);
	SET_BIT(STK -> CTRL , TMR_INT);
}

u32 STK_u32GetElapsedTime(void)
{
	return (STK ->LOAD - STK ->VAL);
}

u32 STK_u32GetRemainingTime(void)
{
    return 	(STK ->VAL);
}

void STK_voidStopTimer(void)
{
	CLR_BIT(STK -> CTRL , Enable_TMR);
	STK -> LOAD = 0;
	STK -> VAL  = 0;
}

void STK_voidSetCallBack(void (*ptr) (void))
{
	STK_CALLBACK = ptr ;
}

void STK_voidResetTimer(void)
{
	STK -> VAL  = 0;
}
