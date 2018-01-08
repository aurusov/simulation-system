#!/usr/bin/python

class Model:

    BARBER_FREE = 0
    BARBER_BUSY = 1

    def __init__(model):
        model.barber_state = model.BARBER_FREE
        model.queue_length = 0
        model.arrival_interval = Model.arrivalInterval()
        model.duration_delay = Model.durationDelay()

    def __str__(model):
        if model.barber_state == model.BARBER_FREE:
            state = 'free'
        else:
            state = 'busy'
        return state + ', ' + str(model.queue_length)

    @staticmethod
    def arrivalInterval():
        for arrival_interval in [14, 13, 17, 15, 16, 15, 14, 22, 19]:
            yield arrival_interval

    @staticmethod
    def durationDelay():
        for duration_delay in [18, 12, 14, 15, 14, 15, 13, 14, 17]:
            yield duration_delay

    def arrivalEvent(model, simulator):
        simulator.planning(model.arrivalEvent, simulator.current_time + model.arrival_interval.next())
        if model.barber_state == model.BARBER_FREE:
            model.barber_state = model.BARBER_BUSY
            simulator.planning(model.serviceFinishedEvent, simulator.current_time + model.duration_delay.next())
        else:
            model.queue_length += 1

    def serviceFinishedEvent(model, simulator):
        if model.queue_length > 0:
            model.queue_length -= 1
            simulator.planning(model.serviceFinishedEvent, simulator.current_time + model.duration_delay.next())
        else:
            model.barber_state = model.BARBER_FREE

    def barberShopFinishedEvent(model, simulator):
        if simulator.current_time > 44:
            exit()

class Simulator:

    def __init__(simulator):
        simulator.current_time = 0.0
        simulator.scheduler = Simulator.Scheduler()

    class Scheduler:

        class Item:
            def __init__(item, event, event_time):
                item.event = event
                item.event_time = event_time

            def __repr__(item):
                return str(item)

            def __str__(item):
                return item.event.__name__ + '=' + str(item.event_time)

        def __init__(scheduler):
            scheduler.events = []

        def planning(scheduler, event, event_time):
            scheduler.events.append(Simulator.Scheduler.Item(event, event_time))

    def planning(simulator, event, event_time):
        simulator.scheduler.planning(event, event_time)

    def __str__(simulator):
        return str(simulator.current_time) + ', ' + str(simulator.scheduler.events)

    def run(simulator, model):
        while simulator.scheduler.events:
            item = min(simulator.scheduler.events, key=lambda item: item.event_time)
            simulator.scheduler.events.remove(item)

            simulator.current_time = item.event_time

            item.event(simulator)
            print simulator, model

simulator = Simulator()
model = Model()
print simulator, model
simulator.planning(model.arrivalEvent, model.arrival_interval.next())
simulator.planning(model.barberShopFinishedEvent, 45)

print simulator, model
simulator.run(model)
