from enum import Enum

class EventEnter(object):
    def __init__(self, name):
        self.name = name

    def run(self, simulator, model):
        simulator.scheduler.planning(simulator.time_now + model.get_enter_time_delay.next(), self)

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

    def __init__(self):
        self.event_enter = EventEnter('enter')
        self.barber = Model.Barber()
        self.queue = 0
        self.get_enter_time_delay = Model.__get_enter_time_delay__()

    @staticmethod
    def __get_enter_time_delay__():
        enter_time_delay = [14, 13, 17, 15, 16, 15, 14, 22, 19]
        for delay in enter_time_delay:
            yield delay


class Simulator(object):
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
            self.__events__.append(Simulator.Scheduler.Item(time, event))

    def __init__(self):
        self.time_now = 0.0
        self.scheduler = Simulator.Scheduler()

model = Model()
simulator = Simulator()
model.event_enter.run(simulator, model)
model.event_enter.run(simulator, model)
print simulator.scheduler.__events__
