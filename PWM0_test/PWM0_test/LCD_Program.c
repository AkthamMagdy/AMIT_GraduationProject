/*
 * LCD_program.c
 *
 * Created: 17/01/2025 05:57:21 م
 *  Author: Aktham Magdy
 */ 


#define  F_CPU			16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_Interface.h"

/* HAL */
#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "LCD_Private.h"


void LCD_voidInit(void)
{
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT,  LCD_E_PIN,  DIO_PIN_OUTPUT);
	
	_delay_ms(35);
	
#if LCD_MODE == LCD_8_BIT_MODE

	DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
	
	LCD_voidSendCommand(0b00111000);
	_delay_us(45);
	
#elif LCD_MODE == LCD_4_BIT_MODE	
    
    DIO_voidSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);
	

	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	PRV_voidWriteHalfPort(0b0010);

	PRV_voidEnableTriggerWrite();

	LCD_voidSendCommand(0b00101000);
	_delay_us(45);
	
#endif


	LCD_voidSendCommand(0b00001111);
	_delay_us(45);
	

	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	

	LCD_voidSendCommand(0b00000110);
}


void LCD_voidSendCommand(u8 copy_u8cmnd)
{

	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	
#if LCD_MODE == LCD_8_BIT_MODE

	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8cmnd);

	PRV_voidEnableTriggerWrite();
	
#elif LCD_MODE == LCD_4_BIT_MODE
    

	PRV_voidWriteHalfPort(copy_u8cmnd >> 4);

	PRV_voidEnableTriggerWrite();
	

	PRV_voidWriteHalfPort(copy_u8cmnd);

	PRV_voidEnableTriggerWrite();
	
#endif
}


void LCD_voidDisplayChar(u8 copy_u8Data)
{

	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	
#if LCD_MODE == LCD_8_BIT_MODE

    DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Data);

    PRV_voidEnableTriggerWrite();

#elif LCD_MODE == LCD_4_BIT_MODE


    PRV_voidWriteHalfPort(copy_u8Data >> 4);

    PRV_voidEnableTriggerWrite();
    

    PRV_voidWriteHalfPort(copy_u8Data);

    PRV_voidEnableTriggerWrite();

#endif
}

void LCD_voidDisplayString(u8* copy_pu8String)
{
	if(copy_pu8String != NULL){
		u8 local_u8Iter = 0;
		while(copy_pu8String[local_u8Iter] != '\0') {
			LCD_voidDisplayChar(copy_pu8String[local_u8Iter]);
			local_u8Iter++;
		}
	}
	else
	{
		// RETURN ERROR STATE
	}
}

void LCD_voidDisplayNumber(u32 copy_u32Number)
{
	if (copy_u32Number == 0)
	{
		LCD_voidDisplayChar('0');
	} 
	else
	{
		u32 local_u32ReversedNumber = 1;    
		    while(copy_u32Number != 0)
		    {
			    local_u32ReversedNumber = (local_u32ReversedNumber * 10) + (copy_u32Number % 10);
			    copy_u32Number /= 10; 
		    }
			
			do 
			{
				LCD_voidDisplayChar((local_u32ReversedNumber % 10) + '0');
				local_u32ReversedNumber /= 10;
			} while (local_u32ReversedNumber != 1);
	}
}

void LCD_voidClear(void)
{
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
}

static void	PRV_voidEnableTriggerWrite(void)
{

	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


static void	PRV_voidWriteHalfPort(u8 copy_u8Value)
{
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Value, 0));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Value, 1));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Value, 2));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Value, 3));
}
void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position)
{
	if(copy_u8LineNumber == 0)
	{
		LCD_voidSendCommand(0b00101011);
		LCD_voidSendCommand(0x80 | 0x00);
		for(u8 i = 0; i < copy_u8Position; i++)
		{
			LCD_voidSendCommand(0b00010111);
		}
	}
	if(copy_u8LineNumber == 1)
	{
		LCD_voidSendCommand(0b00101011);
		LCD_voidSendCommand(0x80 | 0x40);
		for(u8 i = 0; i < copy_u8Position; i++)
		{
			LCD_voidSendCommand(0b00010111);
		}
	}
}
void LCD_voidShift(u8 copy_u8ShifttingDirection)
{
	switch (copy_u8ShifttingDirection)
	{
		case LCD_SHIFT_LEFT:
		LCD_voidSendCommand(0b00011011);
		break;
		case LCD_SHIFT_RIGHT:
		LCD_voidSendCommand(0b00011111);
		break;
	}
}

