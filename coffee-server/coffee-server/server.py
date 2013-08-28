import serial
import time

import tornado.ioloop
import tornado.web

from machine import CoffeeMachine

settings = {
    "debug": True
}

machine = CoffeeMachine()

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Coffee")

class BoilerHandler(tornado.web.RequestHandler):
    def get(self, state):
        try:
            state = bool(int(state))
        except ValueError:
            state = False

        if state:
            machine.boiler_on()
        else:
            machine.boiler_off()

        self.write("Boiler %s" % ("on" if state else "off"))

application = tornado.web.Application([
    (r"/", MainHandler),
    (r"/boiler/(\d)", BoilerHandler),
], **settings)


if __name__ == "__main__":
    application.listen(6886, '0.0.0.0')
    tornado.ioloop.IOLoop.instance().start()
