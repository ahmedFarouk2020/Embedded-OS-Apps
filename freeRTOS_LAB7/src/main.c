/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
#include "timers.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"

//------------------------------------
TimerHandle_t timer_function;
//-----------------------------------
void callback_timer(TimerHandle_t timer_function)
{
	static u8 state = 1;
	MGPIO_voidSetPinValue(GPIOA,PIN0,GET_BIT(state,0));
	// toggle pin
	state ^=1;
}
/*--------------------------------------------*/
void task1(void* pvParam)
{
	char receive = '0';
	static u16 period = 1000;
	while(1)
	{
		receive = MUART_u8Receive();

		MUART_voidTransmit((u8*)"\r\nAS%as^&$^%#&^*\r\n");
		if(receive == 'r')
		{
			xTimerReset(timer_function,500);
		}
		else if(receive == 's')
		{
			xTimerStop(timer_function,500);
		}
		else if(receive == 'i')
		{
			period = period/2;
			xTimerChangePeriod(timer_function,period,500);
		}
		else if(receive == 'd')
		{
			period = period*2;
			xTimerChangePeriod(timer_function,period,500);
		}
		else {}
	}
}

//---------------------------------------------------
// BUG: Data is received incorrectly! SOLVED
//1. make os clk the same as micro controller clk
//2. change the baudrate to 115200
//------------------------------------------------

int main()
{
	RCC_voidInitSysClock(); // Enable clk 8M
	RCC_voidEnableClock(RCC_APB2,2); // Enable GPIOA
	RCC_voidEnableClock(RCC_APB2,14);//enable UART1 clk
	// define pins as input pullup
	MGPIO_voidSetPinDirection(GPIOA,PIN0,OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinValue(GPIOA,PIN0,HIGH);
	// set UART1 pin direction
	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_10MHZ_AF_PP);// TX
	MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);// RX
	MUART_voidInit();
	/* Define Task1 */
	TaskHandle_t task1_handle;
	xTaskCreate(task1,"Task1",configMINIMAL_STACK_SIZE,NULL,1,&task1_handle);
	/* Define timer */
	timer_function = xTimerCreate("Timer",500,pdTRUE,NULL,callback_timer),
	xTimerStart(timer_function,0);
	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
