#define F_CPU 16000000UL
#define BAUDRATE 9600        //The baudrate that we want to use
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)    //The formula that does all the required math

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

void TIM1_init() {
	//set normal mode, no prescaler
	TCCR1A = 0;
	TCCR1B = 1;
}

void USART_init(void){
	UBRR0H = BAUD_PRESCALLER >> 8;
	UBRR0L = BAUD_PRESCALLER;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
}

void INT0_init (void) {
	//ENABLE INT0 ON RISING EDGE
	EICRA = ( (1 << ISC01) | (1 << ISC00) );
	//ENABLE INT0
	EIMSK = (1 << INT0);
}

void USART_send(const uint8_t data) {
	while(!(UCSR0A & (1 << UDRE0))) {
		; //do nothing
	}
	UDR0 = data;
}

uint8_t USART_receive(void) {
	while(!(UCSR0A & (1 << RXC0))) {
		; //do nothing
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

ISR(INT0_vect) {
	//we dont care about override, we are looking for random after all
	uint16_t tmp = TCNT1;
	random[end++] = tmp;
	tmp = tmp >> 8;
	random[end++] = tmp;
}

int main() {
	TIM1_init();
	USART_init();
	INT0_init();
	sei();
	USART_send('S');
	USART_send('t');
	USART_send('a');
	USART_send('r');
	USART_send('t');
	USART_send('\n');
	while(true) {
		if (start < end) {
			USART_send(random[start++]);
		}
	}
}
