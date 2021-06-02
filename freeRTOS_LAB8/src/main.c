/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"

#define BIT0 (1<<0)
#define BIT1 (1<<1)
// shared data------------------------------------
EventGroupHandle_t eventGroup_handle;
//-----------------------------------
void button1(void* pvParam)
{
	u8 state = 0xff;
	while(1)
	{
		u8 data = MGPIO_u8GetPinValue(GPIOA,PIN1);
		if(state && !data) // pressed
		{
			xEventGroupSetBits(eventGroup_handle,BIT0);
		}
		state = data;
		vTaskDelay(15);
	}
}
/*--------------------------------------------*/
void button2(void* pvParam)
{
	u8 state = 0xff;
	while(1)
	{
		u8 data = MGPIO_u8GetPinValue(GPIOA,PIN2);
		if(state && !data)
		{
			xEventGroupSetBits(eventGroup_handle,BIT1);
		}
		state= data;
		vTaskDelay(15);
	}
}
/*----------------------------------------------*/
void task1(void* pvParam)
{
	u8 state = 0xff;
	while(1)
	{
		 xEventGroupWaitBits(eventGroup_handle,BIT0|BIT1 ,pdTRUE,pdTRUE,(TickType_t)portMAX_DELAY );
		 MGPIO_voidSetPinValue(GPIOA,PIN0,GET_BIT(state,0));
		 state ^= 0xff;
	}
}


int main()
{
	RCC_voidInitSysClock(); // Enable clk 8M
	RCC_voidEnableClock(RCC_APB2,2); // Enable GPIOA
	// define switch1 (pin1) as input pullup
	MGPIO_voidSetPinDirection(GPIOA,PIN1,OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinValue(GPIOA,PIN1,HIGH);
	// define switch2 (pin2) as input pullup
	MGPIO_voidSetPinDirection(GPIOA,PIN2,OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinValue(GPIOA,PIN2,HIGH);
	// define led(pin0) as output pin
	MGPIO_voidSetPinDirection(GPIOA,PIN0,OUTPUT_2MHZ_PP);

	eventGroup_handle = xEventGroupCreate();

	/* Define Tasks */
	TaskHandle_t task1_handle,button1_handle,button2_handle;
	xTaskCreate(task1,"Task1",configMINIMAL_STACK_SIZE,NULL,3,&task1_handle);
	xTaskCreate(button1,"button1",configMINIMAL_STACK_SIZE,NULL,2,&button1_handle);
	xTaskCreate(button2,"button2",configMINIMAL_STACK_SIZE,NULL,1,&button2_handle);

	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
