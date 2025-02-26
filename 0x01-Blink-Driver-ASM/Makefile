TARGET    = program
MCU       = atmega328p
F_CPU     = 16000000UL
PORT      = /dev/tty.usbserial-83420
BAUD      = 57600

AS        = avr-as
LD        = avr-ld
OBJCOPY   = avr-objcopy
AVRDUDE   = avrdude

ASFLAGS   = -mmcu=$(MCU) -Wa --defsym=F_CPU\=$(F_CPU)
LDFLAGS   = -m avr5

all: $(TARGET).hex

$(TARGET).o: $(TARGET).s
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET).elf: $(TARGET).o
	$(LD) $(LDFLAGS) -o $@ $<

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).o $(TARGET).elf $(TARGET).hex
