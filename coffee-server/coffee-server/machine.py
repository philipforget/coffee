import os
import re
import subprocess
import uuid

import serial


HELLO           = "HELLO"
GOODBYE         = "GOODBYE"
boiler_off      = "B0"
boiler_on       = "B1"
get_target      = "GT"
get_temperature = "GP"
ping            = "PING"
pong            = "PONG"
pump_off        = "P0"
pump_on         = "P1"
reset           = "R"
set_target      = "ST"

board_finder_re = re.compile(
    r'(?P<board>(ttyusb\d|tty\.usbserial))', flags=re.IGNORECASE)

class BoardNotFound(Exception):
    pass

class NoResponse(Exception):
    pass


class CoffeeMachine():
    """Exposes all of the functionality of the actual espresso hardware.

    """
    def __init__(self, board=None, baud=9600, timeout=1, connection_retries=5):
        self.connected = False
        self.board = board or CoffeeMachine.find_board()
        self.baud = baud
        self.timeout = timeout
        self.connection_retries = connection_retries

        self.initiate_serial()


    @classmethod
    def find_board(cls):
        """Attempt to find a board, pretty naively at that.

        If no board is found, raises BoardNotFound.
        """
        try:
            return "/dev/{0}".format(board_finder_re.search(
                ",".join(os.listdir('/dev'))).group('board'))
        except TypeError:
            raise BoardNotFound("No board found")


    def initiate_serial(self, reset=True):
        """Initiate the serial connection.

        """
        self.serial = serial.Serial(self.board, self.baud, timeout=self.timeout)
        if reset:
            print "Attempting to reset board"
            self.reset()
            print "Giving board time to boot"

        # On potential re-init, assume we will fail
        self.connected = False
        retry = 0
        while retry < self.connection_retries:
            line = self.serial.readline().strip()
            if line == HELLO:
                self.connected = True
                return
            retry += 1

        raise serial.SerialException("Unable to connect to %s" % self.board)


    def reset(self):
        """Reset the board.

        """
        self.send_command(reset)


    def set_target(self, target):
        """Set the target boiler temperature.

        """
        self.send_command(set_target, target)


    def get_target(self):
        """Set the target boiler temperature.

        """
        return self.send_command(get_target, response=True)


    def get_temperature(self):
        """Get the current temperature of the boiler.

        """
        return self.send_command(get_temperature, 12, response=True)


    def pump_on(self):
        """Turn the pump on.

        """
        return self.send_command(pump_on)


    def pump_off(self):
        """Turn the pump off.

        """
        return self.send_command(pump_off)

    def boiler_on(self):
        """Turn the boiler on.

        """
        return self.send_command(boiler_on)


    def boiler_off(self):
        """Turn the boiler off.

        """
        return self.send_command(boiler_off)


    def send_command(self, command, *args, **kwargs):
        """Send a command to the arduino.

        Setting 'get_response' kwarg to True will block temporarily.
        """
        get_response = kwargs.get('get_response', False)
        command_str = command

        if args:
            command_str = "{0} {1}".format(
                command_str, " ".join(map(lambda x: str(x), args)))

        # Cap the command off with a newline
        command_str = "%s\n" % command_str

        self.serial.write(command_str)
        if kwargs.get('response', False):
            retry = 0
            while retry < self.connection_retries:
                line = self.serial.readline().strip()
                if line:
                    return line
                retry += 1

            raise NoResponse("No response for %s" % command_str)
