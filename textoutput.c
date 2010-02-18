#include "stdinc.h"
#include "usart.h"
#include "eeprom.h"

void dumpEeprom() {

	unsigned int i;

	for(i=0;i<EEPROM_SIZE;i++) {

		char buffer[32];
		char buffer2[64];

		unsigned char x;
		getByte(i,&x);
		sprintf(buffer,"%02x",x);

		if ((i % 16) == 0) {
			sprintf(buffer2,"%03x",i);						
			USART_TXS("0x");	
			USART_TXS(buffer2);		
			USART_TXS("  ");		
		}

		USART_TXS(buffer);		

		if ((i+1) % 16) {
			USART_TXS(" ");
		} else {
			USART_TXS("\n");	
		}
	
	}

}
