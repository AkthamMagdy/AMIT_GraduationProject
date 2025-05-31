/*
 * LCD_interface.h
 *
 * Created: 17/01/2025 05:57:37 م
 *  Author: Aktham Magdy
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_SHIFT_LEFT  0
#define LCD_SHIFT_RIGHT 1
                                /*************** APIS PROTO TYPES ***************/

void LCD_voidInit         (void);
void LCD_voidSendCommand  (u8 copy_u8cmnd);
void LCD_voidDisplayChar  (u8 copy_u8Data);


void LCD_voidDisplayString(u8* copy_pu8String);

void LCD_voidClear(void);
void LCD_voidShift(u8 copy_u8ShifttingDirection);
void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position);

void LCD_voidDisplayNumber(u32 copy_u32Number);


#endif /* LCD_INTERFACE_H_ */