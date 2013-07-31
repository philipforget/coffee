#!/usr/bin/env python
import sys

import serial


def main(port):
    s = serial.Serial(port, 9600, timeout=1)
    while True:
        line = s.readline().strip()
        if line:
            print line
        

if __name__ == '__main__':
    main(sys.argv[1])
