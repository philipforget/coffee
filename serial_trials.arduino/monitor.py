#!/usr/bin/env python

import serial

def main():
    s = serial.Serial('/dev/tty.usbserial-A4001m75', 9600, timeout=1)
    while True:
        line = s.readline().strip()
        if line:
            print line
        

if __name__ == '__main__':
    main()
