import serial
import time

TTY = '/dev/tty.usbserial-A4001m75'
BAUD = 57600
TIMEOUT = 1
MAX_RETRIES = 5
RETRY_SLEEP = 5


def set_temperature():pass
def get_temperature():pass
def set_boiler_state():pass
def get_boiler_state():pass
def set_pump_state():pass
def get_pump_state():pass


def loop(arduino):
    line = None
    while line != "Starting up":
        print "Waiting for handshake"
        line = arduino.readline().strip()

    print "Got handshake"
    while True:
        print "> Sending good frame"
        arduino.write('%123456#')
        while True:
            line = arduino.readline().strip()
            if line:
                print "< %s" % line
            else:
                break


def connect(tries=0):
    if tries > MAX_RETRIES:
        print "Unable to connect to Arduino on {0}".format(TTY)
    try:
        arduino = serial.Serial(TTY, BAUD, timeout=TIMEOUT)
        print "Connected to {0}".format(TTY)
        loop(arduino)
    except serial.SerialException:
        print "No Board, trying again in {0}".format(RETRY_SLEEP)
        time.sleep(RETRY_SLEEP)
        return connect(tries + 1)


def main():
    connect()



if __name__ == '__main__':
    main()
