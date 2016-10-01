#include "stdinc.h"

uint8_t eeBytes[EEPROM_SIZE] EEMEM;

unsigned char setByte(unsigned int addr, unsigned char data) {
    if (addr >= EEPROM_SIZE) return ERROR;
	eeprom_write_byte(&eeBytes[addr], data);
	return SUCCESS;
}

unsigned char getByte(unsigned int addr, unsigned char* data) {	
	if (addr >= EEPROM_SIZE) return ERROR;
	*data = eeprom_read_byte(&eeBytes[addr]);
	return SUCCESS;
}
