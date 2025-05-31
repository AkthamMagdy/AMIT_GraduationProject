/*
 * PWM0_Program.c
 *
 * Created: 3/9/2025 10:37:38 PM
 *  Author: Aktham Magdy
 */ 
// UTILES_LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"
// MCAL
#include "PWM0_Interface.h"
#include "PWM0_Register.h"

void PWM0_voidInit(void)
{
	SET_BIT(TCCR0_REG, WGM00);
	SET_BIT(TCCR0_REG, WGM01);
	
	CLR_BIT(TCCR0_REG, COM00);
	SET_BIT(TCCR0_REG, COM01);
}
void PWM0_voidGeneratePWM(u8 copy_u8DutyCycle)
{
	if (copy_u8DutyCycle <= 100)
	{
		OCR0_REG = ((copy_u8DutyCycle * 256) / 100) - 1;
		
		
		SET_BIT(TCCR0_REG, CS00);
		SET_BIT(TCCR0_REG, CS01);
		CLR_BIT(TCCR0_REG, CS02);
	} 
	else
	{
		// RETURN ERROR STATE
	}
	

}
void PWM0_voidStop()
{
	CLR_BIT(TCCR0_REG, CS00);
	CLR_BIT(TCCR0_REG, CS01);
	CLR_BIT(TCCR0_REG, CS02);
}
