from enum import Enum

class EventEnter:
    def __init__(event, name):
        event.name = name

    def run(event, simulator, model):
        simulator.scheduler.planning(simulator.time_now + model.get_enter_time_delay.next(), model.event_enter)

        if model.barber.state == Model.Barber.State.BUSY:
            model.queue += 1
            return

        if model.barber.state == Model.Barber.State.FREE:
            model.barber.state = Model.Barber.State.BUSY
            simulator.scheduler.planning(simulator.time_now + model.get_haircut_duration.next(), model.event_finish)
            return

class EventFinish:
    def __init__(event, name):
        event.name = name

    def run(event, simulator, model):
        if model.queue > 0:
            model.queue -= 1
            simulator.scheduler.planning(simulator.time_now + model.get_haircut_duration.next(), model.event_finish)
            return

        if model.queue == 0:
            model.barber.state = Model.Barber.State.FREE


class Model:

    class Barber:
        class State(Enum):
            FREE = 1
            BUSY = 2
        def __init__(barber):
            barber.state = Model.Barber.State.FREE

    def __init__(model):
        model.event_enter = EventEnter('enter')
        model.event_finish = EventFinish('finish')
        model.barber = Model.Barber()
        model.queue = 0
        model.get_enter_time_delay = Model.__get_enter_time_delay__()
        model.get_haircut_duration = Model.__get_haircut_duration__()

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


class Simulator:

    class Scheduler:

        class Item:
            def __init__(item, time, event):
                item.time = time
                item.event = event

            def __repr__(item):
                return str(item)

            def __str__(item):
                return str(item.time) + ', ' + item.event.name

        def __init__(scheduler):
            scheduler.__items__ = []

        def planning(scheduler, time, event):
            scheduler.__items__.append(Simulator.Scheduler.Item(time, event))

    def __init__(simulator):
        simulator.time_now = 0.0
        simulator.scheduler = Simulator.Scheduler()

    def run(simulator, model):
        while simulator.scheduler.__items__:
            simulator.scheduler.__items__.sort(key=lambda item: item.time)
            item = simulator.scheduler.__items__[0]
            simulator.scheduler.__items__.remove(item)
            simulator.time_now = item.time
            item.event.run(simulator, model)
            print 'time = %f, queue = %d, barber = %s, future_events_list = %s' % (simulator.time_now, model.queue, model.barber.state, simulator.scheduler.__items__)


model = Model()
simulator = Simulator()
simulator.scheduler.planning(model.get_enter_time_delay.next(), model.event_enter)
simulator.run(model)
