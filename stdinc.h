#pragma once
#include <avr/io.h>
#include <stdlib.h> 
#include <string.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <avr/eeprom.h>

#define LINEBUFFER_LENGTH 64
#define MAXCMDLEN 16

#define SUCCESS 0
#define ERROR	1
#define CHECKSUM_ERROR	2

#define EEPROM_SIZE 512

#include "tools.h"
#include "usart.h"

#include "cmdparser.h"
#include "parser.h"


#include "eeprom.h"
#include "shell.h"
#include "serialmem.h"






