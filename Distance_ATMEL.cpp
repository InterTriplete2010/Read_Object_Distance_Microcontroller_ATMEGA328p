#ifndef F_CPU
#define F_CPU 16000000UL	//16 MHz; this is the system clock of ATMEGA328p
#endif

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#ifndef BAUD
#define BAUD 9600
#endif

//#define UBRR0 
#ifndef MYUBRR
#define MYUBRR ((F_CPU/(BAUD*16UL))-1) //The value 16 has been used because we are operating in single speed;
#endif

volatile unsigned long time_elapsed_ms;

//Define the USART
void uart_init(unsigned int ubrr) {
	
	//Set the baud rate. This is a 12 bit register 
	UBRR0H = (unsigned char) (ubrr >> 8);	//It contains the 4 most significant bits
	UBRR0L = (unsigned char)ubrr;	//It contains the 8 least significant bits

	//Now enable the transmitter by setting TXEN0 to 1. The interrupt and the Receiver won't be enabled
	UCSR0B |= (0 << TXCIE0) | (0 << RXEN0) | (1 << TXEN0);
	
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);	//Set the number of data bits that the transmitter will use
	

}

//Function for the transmission of the data
void USART_Transmit (uint8_t data)
{
	
	//Check if the transmit buffer is empty and ready to receive new data. This happens when the UCSR01 and the UDRE0 are empty (UDRE0 is set to 1 in the UCSR0A register).
	while(!(UCSR0A & (1<<UDRE0)));
	
	//Put the data into the buffer and send it out;
	UDR0 = data;
	
}

//Setup the timer0
void setup_timer() {

	// Configure Timer0 with desired prescaler

	TCCR0A = 0x00;	//Normal port operation

	TCCR0B = 0x03;	//Set the prescaler to 64
	
	TIMSK0 = 0x01;	//Enable interrupts when overflow occurs

}

//Interrupt for the counter (Timer0 overflow)
ISR(TIMER0_OVF_vect)
{

	time_elapsed_ms++; // Increment the time counter

}

//Enable the trigger for 10us
void Enable_Sound()
{
	
	//Set the trigger high for 10 us
	PORTD |= (1 << PORTD3);
	_delay_us(10);
	PORTD &= ~(1 << PORTD3);	
	
}

int main(void)
{
	
		DDRB &= ~(1 << DDB0);	//Use port PB0 as the input for the Ultrasonic sensor
		PORTB |= (1 << PORTB0);	//Enable the pull-up resistor
		DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6);	//PD3 is used for the trigger. PD5 and PD6 are used for the LEDs
		
		setup_timer();
		uart_init(MYUBRR);	//Initialize the USART
		
			sei();
			
		unsigned long elapsed_time; //Elapsed time;
		double time_traveled;	//Time traveled from the sensor to the obejct and back
		
	while (1)
	{	
	
	
		Enable_Sound();
			
//Wait for the port to go HIGH
while (!(PINB & (1 << PINB0)));

time_elapsed_ms = 0;	//Set the variable for the overflow
TCNT0 = 0;	//Set the timer to zero

		while ((PINB & (1 << PINB0)));	//Execute until the sound is sent back to the sensor
		
		elapsed_time = TCNT0;	
		time_traveled = (343*((double)elapsed_time + (double)(time_elapsed_ms*(pow(2,8)-1)))/((double)F_CPU/6400));
	
			USART_Transmit((uint8_t)time_traveled/2);	//Take half of the clock, because the sound needs to bounce back to the sensor
			
			if (time_traveled/2 > 10)
			{
				
				PORTD &= ~(1 << PORTD6);
					
					PORTD |= (1 << PORTD5);
					_delay_ms(50);
					PORTD &= ~(1 << PORTD5);
					_delay_ms(50);			
				
			}
			
			else
			{
				
				PORTD &= ~(1 << PORTD5);
					
					PORTD |= (1 << PORTD6);
					_delay_ms(50);
					PORTD &= ~(1 << PORTD6);
					_delay_ms(50);
								
			}	
	
	}

}
