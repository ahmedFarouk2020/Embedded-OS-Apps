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

#define Water_condition (H_count >= 2) && (O_count >= 1)
//------------------------------------
SemaphoreHandle_t mutx;
static  char  O_count, H_count  ;
//-----------------------------------
void O_task(void* param) // read input pin to know light color
{
	mutx = xSemaphoreCreateMutex();
	u8 flag = 1;// state before
	u8 	stateNow = 0;
	while(1)
	{
		//Read pin0
		stateNow = MGPIO_u8GetPinValue(GPIOA,PIN0);
		xSemaphoreTake(mutx,(TickType_t)portMAX_DELAY);
		if((stateNow == LOW) && (flag)) //active low , if button is pressed , and last time was high
		{
			O_count++;
			MUART_voidTransmit("O is pressed!");
			MUART_voidTransmitInt(O_count);
			MUART_voidTransmit("\r\n");
		}
		while(Water_condition)
		{
			H_count -= 2;
			O_count --;
			MUART_voidTransmit("Water YAAAAAY!! Remaining H = ");
			MUART_voidTransmitInt(H_count);
			MUART_voidTransmit(" O  =  ");
			MUART_voidTransmitInt(O_count);

			MUART_voidTransmit("\r\n");
		}
		flag = stateNow;
		xSemaphoreGive(mutx);
		vTaskDelay(1);
	}
}
/*--------------------------------------------*/
void H_task(void* pvParam)
{
	u8 flag = 1;// state before
	u8 	stateNow = 0;
	while(1)
	{
		xSemaphoreTake(mutx,(TickType_t)portMAX_DELAY);
		//Read pin0
		stateNow = MGPIO_u8GetPinValue(GPIOA,PIN1);
		if((stateNow == LOW) && (flag)) //active low , if button is pressed , and last time was high
		{
			H_count++;
			MUART_voidTransmit("H is pressed!");
			MUART_voidTransmitInt(H_count);
			MUART_voidTransmit("\r\n");
		}
		while(Water_condition)
		{
			H_count -= 2;
			O_count --;
			MUART_voidTransmit("Water YAAAAAY!! Remaining H = ");
			MUART_voidTransmitInt(H_count);
			MUART_voidTransmit(" O  =  ");
			MUART_voidTransmitInt(O_count);

			MUART_voidTransmit("\r\n");
		}
		flag = stateNow;
		xSemaphoreGive(mutx);
		vTaskDelay(1);
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
	MGPIO_voidSetPinDirection(GPIOA,PIN1,INPUT_PULLUP_PULLDOWN);
	MGPIO_voidSetPinValue(GPIOA,PIN1,HIGH);

	// set UART1 pin direction
	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_10MHZ_AF_PP);// TX
	//MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);// RX
	MUART_voidInit();
	/* handles */
	TaskHandle_t handleO,handleH;

	xTaskCreate(O_task,"Otask",configMINIMAL_STACK_SIZE,NULL,3,&handleO);
	xTaskCreate(H_task,"Htask",configMINIMAL_STACK_SIZE,NULL,2,&handleH);

	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
