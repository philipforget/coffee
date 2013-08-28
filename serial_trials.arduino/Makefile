ifeq ($(shell uname -s),Linux)
	ARDUINO_DIR   = /usr/share/arduino
	AVR_TOOLS_DIR = /usr

	ARDUINO_PORT  = /dev/$(shell ls /dev | grep 'ttyUSB')
	BOARD_TAG     = atmega328
else
	ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java
	AVR_TOOLS_DIR = /usr/local

	ARDUINO_PORT  = /dev/$(ls /dev | grep 'tty\.usbserial')
	BOARD_TAG     = diecimila
endif

ARDMK_DIR     = ~/workspace/Arduino-Makefile
ARDUINO_LIBS  = SoftwareSerial SerialCommand

include ~/workspace/Arduino-Makefile/arduino-mk/Arduino.mk
