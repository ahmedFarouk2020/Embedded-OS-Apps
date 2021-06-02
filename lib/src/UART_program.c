/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 19 2020                                */
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



void MUART_voidInit(void)// can be developed
{

	// baud rate=115200  BRR=0x45
	// baud rate=9600    BRR=0x341
	UART1->BRR = 0x45;

	/*
	   1- enable RX
	   2- enable TX
	   3- enable UART1
	*/
	SET_BIT(UART1->CR1,2);
	SET_BIT(UART1->CR1,3);
	SET_BIT(UART1->CR1,13);

	/* reset all flags */
	UART1->SR = 0;
}

void MUART_voidTransmit(u8* copy_u8Arr)
{
	u8 i = 0;
	while(copy_u8Arr[i] != '\0')
	{
		UART1-> DR =copy_u8Arr[i];

		/* Wait till transmission is completed */
		while((GET_BIT(UART1->SR,7) == 0));
		CLR_BIT(UART1->SR,7);
		i++;
	}
}

void MUART_voidTransmitInt(u32 data)
{
	u8 c[10] = {0} ;
	u8 dummy;
	s8 i = 0 ;

	if(data == 0)
	{
		c[0] = 48;
		i = 0 ;
	}
	while(data)
	{
		dummy = (u8)(data%10);
		c[i++] = dummy + 48;
		data = data/10;
	}
	while(i != -1)
	{
		MUART_voidTransmit((u8*)(&c[i--]));
	}
}

char MUART_u8Receive(void)// bad design
{
	// wait until data receive completes
	while( GET_BIT(UART1->SR,5) == 0 );// stops here

	return((char)(UART1->DR & (u16)0x00FF));
}
