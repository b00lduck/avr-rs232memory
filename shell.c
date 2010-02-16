#include "stdinc.h"

char buffer2[64];
unsigned char rc;

void doSetCommand(char* buffer) {
	unsigned char b=0,c=0;

	rc = parseSetCommand(buffer,&b,&c);
	switch (rc) {
		case SUCCESS:					
			setByte(b,c);
			sprintf(buffer2,"%03x %02x %02x\n",b,c,calcSetChecksum(b,c));
			USART_TXS(buffer2);
			break;
		case CHECKSUM_ERROR:
			USART_TXS("CHECKSUM\n");
			break;
		default:			
			USART_TXS("ERROR\n");
	}
}

void doGetCommand(char* buffer) {
	unsigned char b=0,c=0;
	rc = parseGetCommand(buffer,&b);
	unsigned char x;
	switch (rc) {
		case SUCCESS:					
			getByte(b,&x);
			sprintf(buffer2,"%03x %02x %02x\n",b,x,calcSetChecksum(b,x));
			USART_TXS(buffer2);
			break;
		case CHECKSUM_ERROR:
			USART_TXS("CHECKSUM\n");
			break;
		default:			
			USART_TXS("ERROR\n");
	}
}

void doMacSetCommand(char* buffer) {
	unsigned char b=0,c=0;
	unsigned char i;
	unsigned char mac[6];

	rc = parseMacSetCommand(buffer,mac);

	switch (rc) {
		case SUCCESS:	
			for(i=0;i<6;i++) {
				setByte(i,mac[i]);
			}						
			sprintf(buffer2,"%02x:%02x:%02x:%02x:%02x:%02x %02x\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],calcMacSetChecksum(mac));
			USART_TXS(buffer2);
			break;
		case CHECKSUM_ERROR:
			USART_TXS("CHECKSUM\n");
			break;
		default:			
			USART_TXS("ERROR\n");
	}
}

void doMacGetCommand(char* buffer) {

	unsigned char mac[6];
	unsigned char i;
	for(i=0;i<6;i++) {
		getByte(i,&mac[i]);
	}

	sprintf(buffer2,"%02x:%02x:%02x:%02x:%02x:%02x %02x\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],calcMacSetChecksum(mac));
	USART_TXS(buffer2);

}

void shell() {	
	
	while(1) {
		
		USART_RXS();
		
		char cmd[MAXCMDLEN];
		memset(cmd,0,MAXCMDLEN);

		parseCommand(buffer,&cmd);

		if(strncmp(cmd,"SET",3) == 0) {
			doSetCommand(buffer);
		} else if (strncmp(cmd,"GET",3) == 0) {
			doGetCommand(buffer);
		} else if (strncmp(cmd,"MACSET",6) == 0) {
			doMacSetCommand(buffer);
		} else if (strncmp(cmd,"MACGET",6) == 0) {
			doMacGetCommand(buffer);
		} else if (strncmp(cmd,"DUMP",4) == 0) {			
			dumpEeprom();		
		} else {
			USART_TXS("ERROR\n");			
		}

	}

}
