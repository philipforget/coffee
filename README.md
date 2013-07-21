# coffee

RESTful Espresso. Coffee consists of three parts:
1. An arduino sketch which communicates with a python server.
2. A python server which communicates with the arduino and provides a REST API.
3. A frontend which consumes the API.

## coffee.arduino

coffee.arduino is the arduino app that powers coffee. It is entrusted with
turning the boiler and pump on and off and keeping the boiler temperature as
near to the target temperature as possible via a pid loop.

You can either use the Arduino IDE to build the project or the Makefile which
requires arduino-mk to be installed on your system. If you choose the latter,
be sure to edit the makefile to target your board.

### OS X Installation notes

The arduino makefile is a bit of a pain to install on OS X. All these steps
assume you have homebrew set up already. The steps are as follows:

```bash
# Install these perl modules for sending serial resets to the board
# You may have to enter the cpan shell and manually set an http mirror
# For example http://serverfault.com/questions/130690/force-cpan-to-download-via-http
sudo perl -MCPAN -e 'install +YAML'
sudo perl -MCPAN -e 'install +Device::SerialPort'

# Add the avr-gcc homebrew tap
brew tap larsimmisch/avr

# Install avr-gcc etc.
brew install avr-libc
```

The coffee.arduino makefile also provides a useful `make watch` entry which
will automatically watch the .ino file for writes and build to the arduino
board.

```bash
# Watches the .ino file and automatically builds when you write to the file
make watch
```

This is a bit of a hack but installing our libraries requires us to symlink
directly into the arduino library folder for now since the makefile doesn't
accept relative paths. For example:

```bash
cd /usr/share/arduino/libraries
sudo ln -s <repo_root>/coffee.arduino/lib/* ./
```

This is because the makefile takes care of creating the imports in the .cpp
file and doesn't seem to respect libraries installed in ~/sketchbook/libraries
just yet. This works just fine for now.

### LM75A
coffee uses the LM75A I2C temperature sensor. It can be found cheaply online,
does not require an external thermocouple or amplifier and works within the
range of temperatures needed to make coffee and steam. It is a bit slow for
conventional PID applications, but since our boiler will have lag time anyway
from the fact that it is a big hunk of brass, this doesn't matter in practice.

Addresses for the LM75A are determined by whether pins 5, 6 and 7 are tied high
or low. The first four bits of the address are hardcoded into the chip as 1001.
The three least significant bits represent the rest of the address. Tying a pin
to Vs+ makes it 1, to ground makes it 0. In my setup it was easiest to tie them
all to Vs+ since they are next to each other, which makes my address binary
1001111, or int 79.

To figure out the integer address of your LM75A, tie your pins either high or
low, and run `echo "ibase=2;1001111" | bc` replacing your address in binary.

A [good datasheet](https://raw.github.com/philipforget/coffee/master/doc/lm75a.pdf)
for the LM75A is provided by Texas Instrument which I have mirrored in this
repo.


## coffee.server

coffee.server is the server component that communicates between the arduino and
exposes a REST API for making coffee and steamed milk.


## coffee.frontend

A refernce frontend for coffee.server, coffee.frontend is meant to be run at
http://coffee and provides a full featured html frontend for the coffee server.
