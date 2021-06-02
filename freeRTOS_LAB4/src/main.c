/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"
//------------------------------------
QueueHandle_t Qhandle = 0;
//-----------------------------------
void Task1(void* param) // read input pin to know light color
{
	u8 buffer = 0;
	// define pins as input pullup
	MGPIO_voidSetPinDirection(GPIOA,PIN0,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinDirection(GPIOA,PIN1,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinDirection(GPIOA,PIN2,INPUT_PULLUP_PULLDOWN);

	MGPIO_voidSetPinValue(GPIOA,PIN0,HIGH);
	MGPIO_voidSetPinValue(GPIOA,PIN1,HIGH);
	MGPIO_voidSetPinValue(GPIOA,PIN2,HIGH);

	while(1){
		if(MGPIO_u8GetPinValue(GPIOA,PIN0) == LOW)	buffer = 1;
		else if(MGPIO_u8GetPinValue(GPIOA,PIN1) == LOW)	buffer = 2;
		else if(MGPIO_u8GetPinValue(GPIOA,PIN2) == LOW)	buffer = 3;

		if(xQueueSend(Qhandle, (void*)&buffer, 0) == pdTRUE)
		{
			MUART_voidTransmit((u8*)"Data is sent\n");
		}
		buffer = 0;
		vTaskDelay(900);
	}
}
/*--------------------------------------------*/
void Task2(void* pvParam)
{
	u8 buffer = 0;
	while(1){
		if(xQueueReceive(Qhandle,(void*)&buffer,0) == pdFALSE )
		{
			MUART_voidTransmit("Data isn't received\n");
		}
		MUART_voidTransmit("----------------------------------\n");
		switch (buffer)
		{
		case 1: MUART_voidTransmit("RED\n");    break;
		case 2: MUART_voidTransmit("GREEN\n");  break;
		case 3: MUART_voidTransmit("BLUE\n");   break;
		default: MUART_voidTransmit("UNKNOWN DATA\n"); break;
		}
		vTaskDelay(1000);
	}
}

//---------------------------------------------------
int main()
{
	RCC_voidInitSysClock(); // Enable clk 8M
	RCC_voidEnableClock(RCC_APB2,2); // Enable GPIOA
	RCC_voidEnableClock(RCC_APB2,14);//enable UART1 clk

	// set UART1 pin direction
	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_10MHZ_AF_PP);// TX
	//MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);// RX
	MUART_voidInit();
	/* handles */
	TaskHandle_t handle1,handle2;

	xTaskCreate(Task1,"task1",configMINIMAL_STACK_SIZE,NULL,2,&handle1);
	xTaskCreate(Task2,"task2",configMINIMAL_STACK_SIZE,NULL,1,&handle2);

	Qhandle = xQueueCreate(5,sizeof(u8));

	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
