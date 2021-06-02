/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "LED_interface.h"



void LED_voidSetLedOn(u8 copy_u8Port , u8 copy_u8Pin)
{
	MGPIO_voidSetPinDirection(copy_u8Port ,copy_u8Pin , OUTPUT_2MHZ_PP );
	MGPIO_voidSetPinValue( copy_u8Port , copy_u8Pin , HIGH );
}

void LED_voidSetLedOff(u8 copy_u8Port , u8 copy_u8Pin)
{
	if( MGPIO_u8GetPinValue(copy_u8Port , copy_u8Pin ) == HIGH )
	     MGPIO_voidSetPinValue(copy_u8Port , copy_u8Pin , LOW );
}
