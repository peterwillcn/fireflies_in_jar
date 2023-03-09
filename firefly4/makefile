#######################################
#
# Firefly Project
#
#######################################

#######################################
# Config
#######################################

TARGET = firefly

CC = avr-gcc
OBJCOPY = avr-objcopy

# the microcontroller we are using, ATtiny85 in this case
MCU = atmega328
AVRDUDE_FLAGS = -p m328 -P /dev/ttyACM0 -c avrispv2 -e

INCLUDES = -IINCLUDES
INCLUDES += -I src/

CFLAGS = -g -Wall -Os -mmcu=$(MCU) $(INCLUDES)


#######################################
# Files
#######################################

SOURCES := src/main.c src/io.c
OBJECTS := build/main.o build/io.o

OUTDIR = build

#######################################
# Messages
#######################################

MSG_COMPILING = Compiling:
MSG_LIKING = Linking:

#######################################
# Rules
#######################################

all: $(OUTDIR)/$(TARGET).hex

$(OUTDIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OUTDIR)/$(TARGET).hex: $(OUTDIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

build/main.o: src/main.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c src/main.c -o build/main.o $(CFLAGS)

build/io.o: src/io.o
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c src/io.c -o build/io.o $(CFLAGS)

flash: $(OUTDIR)/$(TARGET).hex
	avrdude $(AVRDUDE_FLAGS) -U flash:w:$(OUTDIR)/$(TARGET).hex

clean:
	rm -f $(OUTDIR)/*

.PHONY: all clean
