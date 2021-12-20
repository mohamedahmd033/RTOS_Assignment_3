#ifndef registers_operations_marcos
#define registers_operations_marcos



/* BITWISE OPERATIONS ON REGISTER BITS */
#define SET_BIT(REG,BIT_NUM) (REG |=(1U<< BIT_NUM)) // SET SPECIFIED BIT IN REGISTER
#define CLEAR_BIT(REG,BIT_NUM) (REG &=~(1U<< BIT_NUM)) // CLEAR SPECIFIED BIT IN REGISTER
#define TOGGLE_BIT(REG,BIT_NUM) (REG=REG^(1U<<BIT_NUM)) //TOGGLE SPECIFIED BIT IN REGISTER
#define BIT_IS_SET(REG,BIT_NUM) (REG&(1U<<BIT_NUM)) //CHECK IF A SPECIFIC BIT IS SET IN REGISTER
#define BIT_IS_CLEAR(REG,BIT_NUM) (!(REG&(1U<<BIT_NUM))) //CHECK IF A SPECIFIC BIT IS CLEAR IN REGISTER

/*PORTS CLOCK ACTIVATION AND DEACTIVATION*/

            /*ACTIVATION*/
#define ENABLE_PORTA_CLOCK SYSCTL_RCGCGPIO_R|=(1U<<0)
#define ENABLE_PORTB_CLOCK SYSCTL_RCGCGPIO_R|=(1U<<1)
#define ENABLE_PORTC_CLOCK SYSCTL_RCGCGPIO_R|=(1U<<2)
#define ENABLE_PORTD_CLOCK SYSCTL_RCGCGPIO_R|=(1U<<3)
#define ENABLE_PORTE_CLOCK SYSCTL_RCGCGPIO_R|=(1U<<4)
#define ENABLE_PORTF_CLOCK SYSCTL_RCGCGPIO_R|=(1U<<5)

/*Insert a number to register*/
#define INSERT_IN_REGISTER(REG,NUM) (REG=NUM)

            /*DEACTIVATION*/
#define DISABLE_PORTA_CLOCK SYSCTL_RCGCGPIO_R&=~(1U<<0)
#define DISABLE_PORTB_CLOCK SYSCTL_RCGCGPIO_R&=~(1U<<1)
#define DISABLE_PORTC_CLOCK SYSCTL_RCGCGPIO_R&=~(1U<<2)
#define DISABLE_PORTD_CLOCK SYSCTL_RCGCGPIO_R&=~(1U<<3)
#define DISABLE_PORTE_CLOCK SYSCTL_RCGCGPIO_R&=~(1U<<4)
#define DISABLE_PORTF_CLOCK SYSCTL_RCGCGPIO_R&=~(1U<<5)


/*PINS DEFINATIONS8*/

//PORTA
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

//PORTB
#define B0 0
#define B1 1
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define B6 6
#define B7 7

//PORTC
#define C0 0
#define C1 1
#define C2 2
#define C3 3
#define C4 4
#define C5 5
#define C6 6
#define C7 7

//PORTD
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

//PORTE
#define E0 0
#define E1 1
#define E2 2
#define E3 3
#define E4 4
#define E5 5
#define E6 6
#define E7 7



//PORTF
#define F0 0
#define F1 1
#define F2 2
#define F3 3
#define F4 4
#define F5 5
#define F6 6
#define F7 7


/*FIXED SWITCHS DEFINIATIONS*/


#endif