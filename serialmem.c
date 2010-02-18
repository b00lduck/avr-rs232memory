#include "stdinc.h"

#include "usart.h"
#include "shell.h"

int main(void) {

	wdt_enable(WDTO_2S);

//	DDRB = 0b00111111;
	DDRC = 0b00000111; //LEDS
//	DDRD = 0b11110000;

//	PORTB = 0b00000000;
	PORTC = 0b00000010;
//	PORTD = 0b00000000;

	usart_init();

	USART_TXS("MCU ready.\n");

	//delayloop16(30000);

	sei();

	shell();

	while(1) { }

}



