###############################################################################
# Makefile for the project motor_pwm
###############################################################################

## General Flags
PROJECT = motor_pwm
MCU = atmega88
TARGET = serialmem.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2  -DF_CPU=11059200UL -O3 -fsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=serialmem.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = tools.o shell.o usart.o serialmem.o cmdparser.o eeprom.o parser.o textoutput.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) serialmem.hex serialmem.eep serialmem.lss size

## Compile
tools.o: ../tools.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

shell.o: ../shell.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart.o: ../usart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serialmem.o: ../serialmem.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

cmdparser.o: ../cmdparser.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

eeprom.o: ../eeprom.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

parser.o: ../parser.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

textoutput.o: ../textoutput.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) serialmem.elf dep/* serialmem.hex serialmem.eep serialmem.lss serialmem.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

