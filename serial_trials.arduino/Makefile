# OSX Specific
#ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java
#ARDMK_DIR     = /Users/philipforget/workspace/Arduino-Makefile/
#AVR_TOOLS_DIR = /usr/local/
#PROJECT_DIR = /Users/philipforget/workspace/coffee/coffee.arduino
#USER_LIB_PATH = /Users/philipforget/workspace/coffee/coffee.arduino/lib

#include /Users/philipforget/workspace/Arduino-Makefile/arduino-mk/Arduino.mk


# Ubuntu Specific
include /usr/share/arduino/Arduino.mk
PARSE_BOARD  = $(ARDUINO_DIR)/ard-parse-boards --boards_txt=$(BOARDS_TXT)
ARDUINO_DIR  = /usr/share/arduino
BOARD_TAG    = atmega328
ARDUINO_PORT = /dev/ttyUSB0


# Global
#ARDUINO_LIBS = LM75A Wire Wire/utility SoftwareSerial


monitor:
	python ./monitor.py "/dev/$$(ls /dev | grep -ie 'tty.\?usb')"

watch:
	watchmedo shell-command --patterns="*.ino" --command='make' .
