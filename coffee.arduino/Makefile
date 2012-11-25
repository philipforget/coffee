BOARD_TAG = atmega328
ARDUINO_PORT = /dev/ttyUSB*

include /usr/share/arduino/Arduino.mk

watch:
	watchmedo shell-command --patterns="*.ino" --command='make' .
