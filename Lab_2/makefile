


check1:
	avrdude -c usbtiny -p atmega328p

check2:
	avrdude -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600
all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	avr-gcc -mmcu=atmega328p led.o -o led
	avr-objcopy -O ihex -R .eeprom led led.hex
	avrdude -F -V -c usbtiny -p ATMEGA328P -b 115200 -U flash:w:led.hex

compile:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	avr-gcc -mmcu=atmega328p led.o -o led
	avr-objcopy -O ihex -R .eeprom led led.hex

upload:
	avrdude -F -V -c usbtiny -p ATMEGA328P -b 115200 -U flash:w:led.hex

clear:
	rm -f *.o *.hex
	
