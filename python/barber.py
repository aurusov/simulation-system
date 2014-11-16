from enum import Enum

class EventEnter(object):
    def __init__(self, name):
        self.name = name

    def run(self, simulator, model):
        simulator.scheduler.planning(simulator.time_now + model.get_enter_time_delay.next(), model.event_enter)

        if model.barber.state == Model.Barber.State.BUSY:
            model.queue += 1
            return

        if model.barber.state == Model.Barber.State.FREE:
            model.barber.state = Model.Barber.State.BUSY
            simulator.scheduler.planning(simulator.time_now + model.get_haircut_duration.next(), model.event_finish)
            return

class EventFinish(object):
    def __init__(self, name):
        self.name = name

    def run(self, simulator, model):
        if model.queue > 0:
            model.queue -= 1
            simulator.scheduler.planning(simulator.time_now + model.get_haircut_duration.next(), model.event_finish)
            return

        if model.queue == 0:
            model.barber.state = Model.Barber.State.FREE


class Model(object):

    class Barber(object):
        class State(Enum):
            FREE = 1
            BUSY = 2
        def __init__(self):
            self.state = Model.Barber.State.FREE

    def __init__(self):
        self.event_enter = EventEnter('enter')
        self.event_finish = EventFinish('finish')
        self.barber = Model.Barber()
        self.queue = 0
        self.get_enter_time_delay = Model.__get_enter_time_delay__()
        self.get_haircut_duration = Model.__get_haircut_duration__()

    @staticmethod
    def __get_enter_time_delay__():
        enter_time_delay = [14, 13, 17, 15, 16, 15, 14, 22, 19]
        for delay in enter_time_delay:
            yield delay

    @staticmethod
    def __get_haircut_duration__():
        get_haircut_duration = [18, 12, 14, 15, 14, 15, 13, 14, 17]
        for duration in get_haircut_duration:
            yield duration


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
            self.__items__ = []

        def planning(self, time, event):
            self.__items__.append(Simulator.Scheduler.Item(time, event))

    def __init__(self):
        self.time_now = 0.0
        self.scheduler = Simulator.Scheduler()

    def run(self, model):
        while self.scheduler.__items__:
            self.scheduler.__items__.sort(key=lambda item: item.time)
            item = self.scheduler.__items__[0]
            self.scheduler.__items__.remove(item)
            self.time_now = item.time
            item.event.run(self, model)
            print 'time = %f, queue = %d, barber = %s, futeru_events_list = %s' % (self.time_now, model.queue, model.barber.state, self.scheduler.__items__)


model = Model()
simulator = Simulator()
simulator.scheduler.planning(model.get_enter_time_delay.next(), model.event_enter)
simulator.run(model)
