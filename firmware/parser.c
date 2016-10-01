#include "stdinc.h"

unsigned char parseSingleHexChar(unsigned char* dec, unsigned char in) {
	
	// check if it is 0-9 or a-f
	if (in < 0x30) {
		return ERROR;
	}
	if (in > 0x66) {
		return ERROR;
	}
	if ((in > 0x39) && (in < 0x61)) {
		return ERROR;
	}
	
	// 0x30 is '0'
	in -= 0x30;	
	if (in > 9) in -= 0x27; 
	*dec = in;

	return SUCCESS;
}


unsigned char getHexnumber2(unsigned char* out, char **line) {

	unsigned char a,b;

	if (parseSingleHexChar(&a,**line) != SUCCESS) return ERROR;
	(*line)++;
	if (parseSingleHexChar(&b,**line) != SUCCESS) return ERROR;
	(*line)++;

	*out = a * 16 + b;

	return SUCCESS;
}

unsigned char getHexnumber3(unsigned int* out, char **line) {

	unsigned char a,b,c;

	if (parseSingleHexChar(&a,**line) != SUCCESS) return ERROR;
	(*line)++;
	if (parseSingleHexChar(&b,**line) != SUCCESS) return ERROR;
	(*line)++;
	if (parseSingleHexChar(&c,**line) != SUCCESS) return ERROR;
	(*line)++;

	*out = a * 256 + b * 16 + c;

	return SUCCESS;
}





