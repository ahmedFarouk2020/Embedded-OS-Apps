/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"
//------------------------------------
SemaphoreHandle_t sem;
//-----------------------------------
void client(void* param) // read input pin to know light color
{
	while(1){
		if(MGPIO_u8GetPinValue(GPIOA,PIN0) == LOW){
			if( xSemaphoreGive(sem) != pdTRUE )
			{
			}
		}
	}
}
/*--------------------------------------------*/
void server(void* pvParam)
{
	u8 i = 0;
	sem = xSemaphoreCreateBinary();
	xSemaphoreTake(sem,(TickType_t) 0);
	while(1){
		xSemaphoreTake(sem,(TickType_t) portMAX_DELAY);// block waiting semaphore
		MUART_voidTransmit("User number ");
		MUART_voidTransmitInt(++i);
		MUART_voidTransmit(" is served ");
		MUART_voidTransmit("\r\n");
	}
}

//---------------------------------------------------

int main()
{
	RCC_voidInitSysClock(); // Enable clk 8M
	RCC_voidEnableClock(RCC_APB2,2); // Enable GPIOA
	RCC_voidEnableClock(RCC_APB2,14);//enable UART1 clk
	// define pins as input pullup
	MGPIO_voidSetPinDirection(GPIOA,PIN0,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinValue(GPIOA,PIN0,HIGH);

	// set UART1 pin direction
	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_10MHZ_AF_PP);// TX
	//MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);// RX
	MUART_voidInit();
	/* handles */
	TaskHandle_t handle1,handle2;

	xTaskCreate(client,"client",configMINIMAL_STACK_SIZE,NULL,1,&handle1);
	xTaskCreate(server,"server",configMINIMAL_STACK_SIZE,NULL,2,&handle2);

	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
