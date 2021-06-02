/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"

void LED1(void* param)
{
	while(1){
	MGPIO_voidSetPinValue(GPIOA,0,HIGH);
	vTaskDelay(10);
	MGPIO_voidSetPinValue(GPIOA,0,LOW);
	vTaskDelay(10);
}
}
/*--------------------------------------------*/
void LED2(void* pvParam)
{
	TickType_t current = xTaskGetTickCount();
	u8 state = 0xff;
	while(1){
		MGPIO_voidSetPinValue(GPIOA,1,GET_BIT(state,0));
		state ^= 0xff;
		vTaskDelayUntil(&current,100);
	}
}
/*--------------------------------------------------*/
int main()
{
	RCC_voidInitSysClock(); // Enable clk 8M
	RCC_voidEnableClock(RCC_APB2,2); // Enable GPIOA
	MGPIO_voidSetPinDirection(GPIOA,0,OUTPUT_2MHZ_PP); // output
	MGPIO_voidSetPinDirection(GPIOA,1,OUTPUT_2MHZ_PP); // output
	TaskHandle_t led1;
	TaskHandle_t led2;
	xTaskCreate(LED1,"one",configMINIMAL_STACK_SIZE,NULL,2,&led1);
	xTaskCreate(LED2,"two",configMINIMAL_STACK_SIZE,NULL,1,&led2);
	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
