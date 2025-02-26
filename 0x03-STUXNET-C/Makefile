TARGET = program
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/tty.usbserial-310
BAUD = 57600

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os

all:
	avr-gcc $(CFLAGS) -o $(TARGET).elf $(TARGET).c
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).elf $(TARGET).hex
