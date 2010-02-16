#include "stdinc.h"

char buffer[LINEBUFFER_LENGTH];

void usart_init() {

	UBRR0H = 0; 

	UBRR0L = 71; // 9600
//	UBRR0L = 35; // 19200
//	UBRR0L = 23; // 28800
//	UBRR0L = 17; // 38400
//	UBRR0L = 11; // 56600


	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void USART_TX(char data ) {
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

void USART_TXS(char* s) {
	while(*s) {
		USART_TX(*s);
		s++;		
	}
}

char USART_RX(void) {
    while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART_RXS(void) {
	uint8_t t = 0;
	uint8_t* b = buffer;
	unsigned char len = LINEBUFFER_LENGTH;
	do {
 		t = USART_RX();
		if (len) {
			*b++ = t;
			len--;
		}
	} while(t != 13);
	*b = 0; // ende
}
