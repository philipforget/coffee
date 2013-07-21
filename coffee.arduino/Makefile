# OSX Specific
ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java
ARDMK_DIR     = /Users/philipforget/workspace/Arduino-Makefile/
AVR_TOOLS_DIR = /usr/local/
PROJECT_DIR = /Users/philipforget/workspace/coffee/coffee.arduino
USER_LIB_PATH = /Users/philipforget/workspace/coffee/coffee.arduino/lib
# END OSX Specific

BOARD_TAG = diecimila
ARDUINO_PORT = /dev/tty.usbserial-A4001m75
ARDUINO_LIBS = LM75A Wire Wire/utility SoftwareSerial

include /Users/philipforget/workspace/Arduino-Makefile/arduino-mk/Arduino.mk

watch:
	watchmedo shell-command --patterns="*.ino" --command='make' .
