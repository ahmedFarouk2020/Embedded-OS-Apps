/* RTOS */
#include"FreeRTOS.h"
#include "task.h"
/* STD LIB */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* DRIVERS */
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "UART_interface.h"
//------------------------------------
// Shared Data-----------------------
u8 x = 0;
u8 y = 0;
//-----------------------------------
void Task1(void* param) // Active LOW
{
	while(1){
		//taskENTER_CRITICAL();
		x++;
		y++;
		//taskEXIT_CRITICAL();
	}
}
/*--------------------------------------------*/
void Task2(void* pvParam)
{
	while(1){
		if(x != y){
			MUART_voidTransmit((u8*)"Shared problem!");
		}
		vTaskDelay(47);
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

	xTaskCreate(Task1,"task1",configMINIMAL_STACK_SIZE,NULL,1,&handle1);
	xTaskCreate(Task2,"task2",configMINIMAL_STACK_SIZE,NULL,2,&handle2);

	vTaskStartScheduler();
	while(1)
	{
		// Tasks.c 3036
	}
	return 0;
}
