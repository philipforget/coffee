#BOARD_TAG = atmega328
BOARD_TAG = diecimila
ARDUINO_PORT = /dev/ttyUSB*
ARDUINO_LIBS = LM75A Wire Wire/utility

include /usr/share/arduino/Arduino.mk

watch:
	watchmedo shell-command --patterns="*.ino" --command='make' .
