#include "stdinc.h"


unsigned char parseCommand(char* line, char* cmd) {
	char* oldline = line;
	unsigned char len = strlen(line);

	while((len) && (*line != 32)) { // read first datafield
		if ((*line != 10) && (*line != 13)) {
			*(cmd++) = *line;
		}
		line++;
		len--;
	}

	line = oldline;

	return SUCCESS;
}

unsigned char calcGetChecksum(unsigned int addr) {
	return addr % 256;
}

unsigned char calcSetChecksum(unsigned int addr, unsigned char data) {
	return (addr + data) % 256;
}

unsigned char calcMacSetChecksum(unsigned char bytes[]) {
	
	int i,x;
	for(i=0;i<6;i++) {	
		x += bytes[i];		
	}
	
	return x % 256;
}

unsigned char parseSetCommand(char* line, unsigned int* addr, unsigned char* data) {

	unsigned char chksum;

	// skip command
	line += 3;

	// skip space
	if (*line != 32) {
		return ERROR;
	} else {
		line++;
	}
	
	if (getHexnumber3(addr,&line) != SUCCESS) {
		return ERROR;
	}

	// skip space
	if (*line != 32) {
		return ERROR;
	} else {
		line++;
	}

	if (getHexnumber2(data,&line) != SUCCESS) {
		return ERROR;
	}

	// skip space
	if (*line != 32) {
		return ERROR;
	} else {
		line++;
	}

	if (getHexnumber2(&chksum,&line) != SUCCESS) {
		return ERROR;
	}

	// end
	if ((*line != 10) && (*line != 13)) {
		return ERROR;
	}


	if (calcSetChecksum(*addr,*data) != chksum ) {
		return CHECKSUM_ERROR;
	}

	return SUCCESS;
}

unsigned char parseGetCommand(char* line, unsigned int* addr) {

	unsigned char chksum;

	// skip command
	line += 3;

	// skip space
	if (*line != 32) {
		return ERROR;
	} else {
		line++;
	}
	
	if (getHexnumber3(addr,&line) != SUCCESS) {
		return ERROR;
	}

	// skip space
	if (*line != 32) {
		return ERROR;
	} else {
		line++;
	}

	if (getHexnumber2(&chksum,&line) != SUCCESS) {
		return ERROR;
	}

	// end
	if ((*line != 10) && (*line != 13)) {
		return ERROR;
	}


	if (calcGetChecksum(*addr) != chksum ) {
		return CHECKSUM_ERROR;
	}

	return SUCCESS;
}


unsigned char parseMacSetCommand(char* line, unsigned char bytes[]) {

	unsigned char chksum;

	// skip command
	line += 6;

	// skip space
	if (*line != 32) return ERROR;
	line++;

	int i;

	for(i=0;i<6;i++) {
		
		// get hex
		if (getHexnumber2(&bytes[i],&line) != SUCCESS) {
			return ERROR;
		}

		if (i<5) {
			// skip ':'
			if (*line != ':') {
				return ERROR;
			}
			line++;
		}

	}

	// skip space
	if (*line != 32) {
		return ERROR;
	}
	line++;

	if (getHexnumber2(&chksum,&line) != SUCCESS) {
		return ERROR;
	}

	// end
	if ((*line != 10) && (*line != 13)) {
		return ERROR;
	}


	if (calcMacSetChecksum(bytes) != chksum ) {
		return CHECKSUM_ERROR;
	}

	return SUCCESS;
}
