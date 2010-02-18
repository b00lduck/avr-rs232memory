#pragma once

unsigned char parseCommand(char* line, char* cmd);
unsigned char parseSetCommand(char* line, unsigned int* addr, unsigned char* val);
unsigned char parseGetCommand(char* line, unsigned int* addr);
unsigned char parseMac(char* line, unsigned char* byte1, unsigned char* byte2, unsigned char* byte3,
                        unsigned char* byte4, unsigned char* byte5, unsigned char* byte6);
unsigned char parseMacSetCommand(char* line, unsigned char bytes[]);
unsigned char calcGetChecksum(unsigned int addr);
unsigned char calcSetChecksum(unsigned int addr, unsigned char data);
unsigned char calcMacSetChecksum(unsigned char bytes[]);
