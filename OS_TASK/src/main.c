#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_Interface.h"
#include "STK_Interface.h"
#include "OS_interface.h"

void LED0(void);
void LED1(void);
void LED2(void);

int main(void)
{
	/*initialization  */
	/* RCC init */
	RCC_voidInitSysClock();/* initiate clock as HSE */
	RCC_voidEnableClock(RCC_APB2 , 2);/* enable GPIOA */
	MGPIO_voidSetPinDirection(GPIOA , PIN8 , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN9 , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN10 , OUTPUT_2MHZ_PP);
	/* GPIOA init (SET Directions) */
	OS_voidCreateTask(0 , 1000 , LED0 , 0 );
	OS_voidCreateTask(1 , 2000 , LED1 , 1 );
	OS_voidCreateTask(2 , 1000 , LED2 , 2 );
	OS_voidStart();
    
	while(1)
	{
		
	}
}

void LED0(void)
{
	/*u8 Local_u8Tog = 0;
	TOG_BIT(Local_u8Tog,0);*/
	MGPIO_voidSetPinValue(GPIOA,PIN8,HIGH);
}

void LED1(void)
{
	/*u8 Local_u8Tog = 0;
	TOG_BIT(Local_u8Tog,0);*/
	MGPIO_voidSetPinValue(GPIOA,PIN9,HIGH);
}

void LED2(void)
{
	/*u8 Local_u8Tog = 0;
	TOG_BIT(Local_u8Tog,0);*/
	MGPIO_voidSetPinValue(GPIOA,PIN10,HIGH);
}
