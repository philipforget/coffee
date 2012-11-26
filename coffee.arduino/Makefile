BOARD_TAG = atmega328
ARDUINO_PORT = /dev/ttyUSB*
ARDUINO_LIBS = LM75A

include /usr/share/arduino/Arduino.mk

watch:
	watchmedo shell-command --patterns="*.ino" --command='make' .
