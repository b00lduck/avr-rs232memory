#include "stdinc.h"

#include "usart.h"
#include "shell.h"
#include "tools.h"

void testing() {
	
	DDRD = 0b00000010;
	PORTD = 0b00000001; // pullup

	DDRC = 0b00000111; //LEDS
	PORTC = 0b00000010;

	unsigned long fucker = 0;

	while(1) {

		if (fucker > 30000)	{
			SBI(PORTC,1);
			SBI(PORTD,1);
		}	else {
			CBI(PORTC,1);
			CBI(PORTD,1);
		}

		if (fucker > 60000) fucker = 0;

		fucker++;

		if (PIND & 0b00000001) {
			SBI(PORTC,0);
		} else {
			CBI(PORTC,0);
		}
	
	}

}

int main(void) {

	//testing();

	wdt_enable(WDTO_2S);

//	DDRB = 0b00111111;
	DDRC = 0b00000111; //LEDS
//	DDRD = 0b11110000;

//	PORTB = 0b00000000;
	PORTC = 0b00000010;
//	PORTD = 0b00000000;

	usart_init();

	//USART_TXS("MCU ready.\n");

	//delayloop16(30000);

	sei();

	shell();

	while(1) { }

}



