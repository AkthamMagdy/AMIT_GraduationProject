/*
 * PWM0_Register.h
 *
 * Created: 3/9/2025 10:38:00 PM
 *  Author: Aktham Magdy
 */ 


#ifndef PWM0_REGISTER_H_
#define PWM0_REGISTER_H_

#define TCCR0_REG     (*(volatile u8*)0x53)
#define FOC0                   7
#define WGM00                  6
#define COM01                  5
#define COM00                  4
#define WGM01                  3
#define CS02                   2
#define CS01                   1
#define CS00                   0






#define TCNT0_REG        (*(volatile u8*)0x52)


#define OCR0_REG         (*(volatile u8*)0x5C)



#define TIMSK_REG         (*(volatile u8*)0x59)
#define TOIE0               0
#define OCIE0               1






#define TIFR_REG         (*(volatile u8*)0x58)
#define TOV0               0
#define OCF0               1



#endif /* PWM0_REGISTER_H_ */