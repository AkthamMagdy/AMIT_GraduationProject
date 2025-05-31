/*
 * PWM0_test.c
 *
 * Created: 3/9/2025 10:37:14 PM
 * Author : Aktham Magdy
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
// UTILES_LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"
// HAL
#include "LCD_Interface.h"

// MCAL
#include "DIO_Interface.h"
#include "PWM0_Interface.h"

// Pwm drawer which supports 25%, 50%, 75% accurate duty cycles (recommended)

int main(void)
{
	u8 local_u8Duty = 25;
	f32 local_f32Frequency = 250;

	f32 local_f32Ton = ((local_u8Duty / 100.0)/(local_f32Frequency * 1000)) * 1000000;
	f32 local_f32PeriodicTime = (1 / (local_f32Frequency * 1000)) * 1000000;

	LCD_voidInit();

	LCD_voidDisplayString((u8*)"Frequency:");
	LCD_voidDisplayNumber(local_f32Frequency);
	LCD_voidDisplayString((u8*)"KHz");
	LCD_voidGoToSpecificPosition(1,0);
	LCD_voidDisplayString((u8*)"Duty Cycle: ");
	LCD_voidDisplayNumber(local_u8Duty);
	LCD_voidDisplayChar('%');

	_delay_ms(2000);
	LCD_voidClear();

	LCD_voidDisplayString((u8*)"ton: ");
	LCD_voidDisplayNumber(local_f32Ton);
	LCD_voidDisplayString((u8*)"us");
	LCD_voidGoToSpecificPosition(1, 0);
	LCD_voidDisplayString((u8*)"toff: ");
	LCD_voidDisplayNumber(local_f32PeriodicTime - local_f32Ton);
	LCD_voidDisplayString((u8*)"us");

	_delay_ms(2000);
	LCD_voidClear();

	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);
	PWM0_voidInit();
	PWM0_voidGeneratePWM(local_u8Duty);
	
	
		   
					  
		u8 lcd_width = 0;
	
	while (1)
	{		
		
			static u8 counter = 0;
		
		   for(u8 i = 0; i < local_f32Ton; i++)
		   {
			   LCD_voidDisplayChar('-');
			   counter++;
		   }
		   
		   LCD_voidDisplayChar('|');
		   LCD_voidGoToSpecificPosition(1, counter++);
		   LCD_voidDisplayChar('|');
		   for(u8 j = 0; j < (local_f32PeriodicTime - local_f32Ton); j++)
		   {
			   LCD_voidDisplayChar('-');
			   counter++;
		   }
		   LCD_voidDisplayChar('|');
		   LCD_voidGoToSpecificPosition(0, counter++);
		   LCD_voidDisplayChar('|');
		   
		   

		   _delay_ms(1000);
		   lcd_width+=5;
		   if(lcd_width == 45)
		   {
			   LCD_voidClear();
			   lcd_width = 0;
			   counter = 0;
			   
		   }
		   LCD_voidShift(LCD_SHIFT_LEFT);
		   
		   
		   
		   
	}
	
}

