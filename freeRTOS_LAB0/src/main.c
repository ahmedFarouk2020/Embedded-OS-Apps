/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"

void delay(void)
{
	u16 i = 1000;
	while(i>0)
	{i--;}
}
/*--------------------------------------------*/
void LedBlinking(void* pvParam)
{
	while(1){
		MGPIO_voidSetPinValue(GPIOA,0,HIGH);
		delay();
		MGPIO_voidSetPinValue(GPIOA,0,LOW);
		delay();
	}
}
/*--------------------------------------------------*/
int main()
{
	RCC_voidInitSysClock(); // Enable clk 8M
	RCC_voidEnableClock(RCC_APB2,2); // Enable GPIOA
	MGPIO_voidSetPinDirection(GPIOA,0,OUTPUT_2MHZ_PP); // output
	TaskHandle_t BlinkH;
	xTaskCreate(LedBlinking,"Blinking",configMINIMAL_STACK_SIZE,NULL,2,&BlinkH);
	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
