/* 
 * This file is part of the Banana Random Number Generator project (https://github.com/5N44P/Banana-Random-Number-Generator).
 * Copyright (c) 2018 Mauro Mombelli.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define F_CPU 16000000UL
#define BAUDRATE 9600        //The baudrate that we want to use
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)    //The formula that does all the required math

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

void TIM1_init() {
	//set normal mode
	TCCR1A = 0;
	//no prescaler
	TCCR1B = (1 << CS10);
}

void USART_init(void){
	UBRR0H = BAUD_PRESCALLER >> 8;
	UBRR0L = BAUD_PRESCALLER;
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

void TIMER1_CAPTURE_init (void){
	//capture flag rising enable
	TCCR1B |= (0 << ICES1);
	// enable capture interrupt
	TIMSK1 = (1<<ICIE1);
	DDRB |= (0<< PINB0);

}

void USART_send(const uint8_t data) {
	while(!(UCSR0A & (1 << UDRE0))) {
		//do nothing
		;
	}
	UDR0 = data;
}

uint8_t USART_receive(void) {
	while(!(UCSR0A & (1 << RXC0))) {
		//do nothing
		;
	}
	return UDR0;
}

bool USART_available(void) {
	return (UCSR0A & (1 << RXC0));
}

//important, 256 as we use the natural overflow to make a circular buffer
volatile uint8_t random[256];
uint8_t start = 0;
volatile uint8_t end = 0;
//volatile uint32_t counter = 0;

ISR(TIMER1_CAPT_vect){
    random[end++] = ICR1L; // low byte interrupt capture
    random[end++] = ICR1H; // high byte interrupt capture
}

int main() {
    uint16_t count = 0;
	TIM1_init();
	USART_init();
	TIMER1_CAPTURE_init();
	sei();
	while(true) {
		if (start != end) {
			USART_send(random[start++]);
		}
	}
}
