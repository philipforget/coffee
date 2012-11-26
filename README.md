# coffee

Coffee is a server for my espresso machine. It has three parts, an arduino app,
a server app, and an html frontend for the server. The server exposes a REST
API for making espresso and steamed milk, what does your server do?

Since most of the helper scripts are also written in python, it makes sense to
be inside the projects virtualenvs when working with the other parts of the
project. Assuming you have virtualenvwrapper installed on your system:

```bash
mkvirtualenv --distribute coffee && pip install -r requirements.txt
```

This will create the virtualenv and install the requirements.


## coffee.arduino

coffee.arduino is the arduino app that powers coffee. It is entrusted with
turning the boiler and pump on and off and keeping the boiler temperature as
near to the target temperature as possible via a pid loop.

You can either use the Arduino IDE to build the project or the Makefile which
requires arduino-mk to be installed on your system. If you choose the latter,
be sure to edit the makefile to target your board.

The Makefile also provides an extra command that isn't in arduino-mk:
```bash
# Watches the .ino file and automatically builds when you write to the file
make watch
```

This is a bit of a hack but installing our libraries requires us to symlink
directly into the arduino library folder for now since the makefile doesn't
accept relative paths. For example:
```
cd /usr/share/arduino/libraries
sudo ln -s <repo_root>/coffee.arduino/lib/* ./
```
This is because the makefile takes care of creating the imports in the .cpp
file and doesn't seem to respect libraries installed in ~/sketchbook/libraries
just yet. This works just fine for now.


## coffee.server

coffee.server is the server component that communicates between the arduino and
exposes a REST API for making coffee and steamed milk.


## coffee.frontend

A refernce frontend for coffee.server, coffee.frontend is meant to be run at
http://coffee and provides a full featured html frontend for the coffee server.
