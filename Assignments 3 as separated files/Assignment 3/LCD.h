#ifndef LCD_H_
#define LCD_H_
#include "tm4c123gh6pm.h"
#include "registers_operations_macros.h"
#include "std_types.h"
#include "Delay_Functions_GPTimer0.h"
#include "toStringConverter.h"

void LCD_init(void);
void LCD_sendCommand(uint8 command);


/* LCD HW Pins */
#define RS A5
#define RW A6
#define E  A7
#define RS_RW_E_In_The_Same_Port

//#ifndef RS_RW_E_In_The_Same_Port

  /*RS*/
#define ENABLE_RS_PORT_CLOCK ENABLE_PORTA_CLOCK
#define LCD_RS_DATA_R GPIO_PORTA_DATA_R
#define LCD_RS_Direction_R GPIO_PORTA_DIR_R
#define LCD_RS_Digital_Enable_R GPIO_PORTA_DEN_R
#define LCD_RS_Unlock_Register GPIO_PORTA_LOCK_R=0X4C4F434Bul
#define LCD_RS_COMMIT_REGISTER GPIO_PORTA_CR_R

  /*RW*/
#define ENABLE_RW_PORT_CLOCK ENABLE_PORTA_CLOCK
#define LCD_RW_DATA_R GPIO_PORTA_DATA_R
#define LCD_RW_Direction_R GPIO_PORTA_DIR_R
#define LCD_RW_Digital_Enable_R GPIO_PORTA_DEN_R
#define LCD_RW_Unlock_Register GPIO_PORTA_LOCK_R=0X4C4F434Bul
#define LCD_RW_COMMIT_REGISTER GPIO_PORTA_CR_R



/*E*/
#define ENABLE_E_PORT_CLOCK ENABLE_PORTA_CLOCK
#define LCD_E_DATA_R GPIO_PORTA_DATA_R
#define LCD_E_Direction_R GPIO_PORTA_DIR_R
#define LCD_E_Digital_Enable_R GPIO_PORTA_DEN_R
#define LCD_E_Unlock_Register GPIO_PORTA_LOCK_R=0X4C4F434Bul
#define LCD_E_COMMIT_REGISTER GPIO_PORTA_CR_R

/*Data-Command Port*/
#define ENABLE_DATA_Command_PORT_CLOCK ENABLE_PORTB_CLOCK
#define LCD_DATA_Command_DATA_R GPIO_PORTB_DATA_R
#define LCD_DATA_Command_Direction_R GPIO_PORTB_DIR_R
#define LCD_DATA_Command_Digital_Enable_R GPIO_PORTB_DEN_R
#define LCD_DATA_Command_Unlock_Register GPIO_PORTB_LOCK_R=0X4C4F434Bul
#define LCD_DATA_Command_COMMIT_REGISTER GPIO_PORTB_CR_R

/* LCD Commands */
#define CLEAR_DISPLAY 0x01ul
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38ul
#define CURSOR_OFF 0x0Cul
#define CURSOR_ON 0x0Eul
#define SET_CURSOR_LOCATION 0x80ul
#define SET_CURSOR_TO_2ND_LINE 0xC0ul
#define SET_CURSOR_TO_1ST_LINE 0x80ul


void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);

void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);

#endif /* LCD_H_ */
