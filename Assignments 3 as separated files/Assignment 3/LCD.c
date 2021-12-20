#include "LCD.h"

void LCD_init(void)
{

     
              /*RS Pin init*/
         ENABLE_RS_PORT_CLOCK; //Enable clock of the port which contains RS
         LCD_RS_Unlock_Register; //Unlock the port which contains RS
         LCD_RS_COMMIT_REGISTER|=(1<<RS);//Unlock RS pin
         LCD_RS_Direction_R|=(1<<RS); //The direction of RS Pin is output
         LCD_RS_Digital_Enable_R|=(1<<RS); //The RS pin is digital
         
         
         
         /*__________*/
         
            

    
         LCD_RS_COMMIT_REGISTER|=(1<<2);//Unlock RS pin
         LCD_RS_Direction_R|=(1<<2); //The direction of RS Pin is output
         LCD_RS_Digital_Enable_R|=(1<<2); //The RS pin is digital
         
         LCD_RS_COMMIT_REGISTER|=(1<<3);//Unlock RS pin
         LCD_RS_Direction_R|=(1<<3); //The direction of RS Pin is output
         LCD_RS_Digital_Enable_R|=(1<<3); //The RS pin is digital
         
         SET_BIT(LCD_E_DATA_R,2);
         CLEAR_BIT(LCD_E_DATA_R,3);
         
         
         
        
          
              /*RW Pin init*/
         ENABLE_RW_PORT_CLOCK; //Enable clock of the port which contains RW
         LCD_RW_Unlock_Register; //Unlock the port which contains RW
         LCD_RW_COMMIT_REGISTER|=(1<<RW);//Unlock RW pin
         LCD_RW_Direction_R|=(1<<RW); //The direction of RW Pin is output
         LCD_RW_Digital_Enable_R|=(1<<RW); //The RW pin is digital
     

             /*E Pin init*/
         ENABLE_E_PORT_CLOCK; //Enable clock of the port which contains E
         LCD_E_Unlock_Register; //Unlock the port which contains E
         LCD_E_COMMIT_REGISTER|=(1<<E);//Unlock E pin
         LCD_E_Direction_R|=(1<<E); //The direction of E Pin is output
         LCD_E_Digital_Enable_R|=(1<<E); //The E pin is digital
         
         
            /*Data-command port init*/
         ENABLE_DATA_Command_PORT_CLOCK; //Enable clock of the port which  DATA/COMMAND Pins
         LCD_DATA_Command_Unlock_Register; //Unlock the port which contains DATA/COMMAND Pins
         LCD_DATA_Command_COMMIT_REGISTER|=0xFF;//Unlock DATA/COMMAND Pins
         LCD_DATA_Command_Direction_R|=0xFF; //The direction of DATA/COMMAND Pins  is output
         LCD_DATA_Command_Digital_Enable_R|=0xFF; //The DATA/COMMAND Pins is digital
         
         
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	
	LCD_sendCommand(CLEAR_DISPLAY); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_RS_DATA_R,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_RW_DATA_R,RW); /* write data to LCD so RW=0 */
        delay_us(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_E_DATA_R,E); /* Enable LCD E=1 */
	delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_Command_DATA_R = command; /* out the required command to the data bus D0 --> D7 */
	delay_us(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_E_DATA_R,E); /* disable LCD E=0 */
	delay_us(1); /* delay for processing Th = 13ns */
        if (command < 4)
        {
           delay_ms(2); /* command 1 and 2 needs up to 1.64ms */
        }
        else
        {
          delay_us(40); /* all others 40 us */
        }
}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_RS_DATA_R,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_RW_DATA_R,RW); /* write data to LCD so RW=0 */
	delay_us(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_E_DATA_R,E); /* Enable LCD E=1 */
	delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_Command_DATA_R = data; /* out the required data char to the data bus D0 --> D7 */
	delay_us(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_E_DATA_R,E); /* disable LCD E=0 */
	delay_us(1); /* delay for processing Th = 13ns */
        delay_ms(1); /*delay for the characters to not overwrite on each others*/
}

void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
                
	}
	
}

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

//void LCD_intgerToString(int data)
//{
  // char buff[16]; /* String to hold the ascii result */
   //itoa(data,buff,10); /* 10 for decimal */
   //LCD_displayString(buff);
//}


void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_DISPLAY); //clear display 
}
