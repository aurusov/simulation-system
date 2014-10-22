from enum import Enum

class EventEnter(object):
    def __init__(self, name):
        self.name = name

    def run(self, model):
        model.scheduler.planning(model.time_now + 0, self)

        if model.barber.state == Model.Barber.State.BUSY:
            model.queue += 1
            return

        if model.barber.state == Model.Barber.State.FREE:
            model.barber.state = Model.Barber.State.BUSY
            return

class Model(object):

    class Barber(object):
        class State(Enum):
            FREE = 1
            BUSY = 2
        def __init__(self):
            self.state = Model.Barber.State.FREE

    class Scheduler(object):

        class Item(object):
            def __init__(self, time, event):
                self.time = time
                self.event = event

            def __repr__(self):
                return str(self)

            def __str__(self):
                return str(self.time) + ', ' + self.event.name

        def __init__(self):
            self.__events__ = []

        def planning(self, time, event):
            self.__events__.append(Model.Scheduler.Item(time, event))

    def __init__(self):
        self.event_enter = EventEnter('enter')
        self.barber = Model.Barber()
        self.queue = 0
        self.scheduler = Model.Scheduler()
        self.time_now = 0.0

model = Model()
model.event_enter.run(model)
print model.scheduler.__events__

def qqq():
    enter_time_delay = [14, 13, 17, 15, 16, 15, 14, 22, 19]
    for delay in enter_time_delay:
        print 'a'
        yield delay
        print 'b'

for i in qqq():
    print i
    print 'c'
