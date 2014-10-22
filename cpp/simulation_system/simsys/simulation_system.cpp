#include <iostream>
#include "simulation_system.h"

SimulationSystem::SimulationSystem()
{}

SimulationSystem::~SimulationSystem()
{}

void SimulationSystem::planning(const ModelTime& time, const LPIEvent& event)
{
	futureList.insert(EventList::value_type(time, event));
}

const ModelTime& SimulationSystem::timeNow() const
{
	return modelTime;
}

void SimulationSystem::run(const LPModel& model)
{
	std::cout << "start model: " << model->getName() << std::endl;

	EventContext contex(LPIModelTimeService(this), LPIPlanningService(this), model);
	while (true)
	{
		if (futureList.empty())
			break;

		EventList::iterator it = futureList.begin();
		ModelTime time = it->first;
		modelTime = time;
		LPIEvent event = it->second;
		futureList.erase(it);
		event->onEvent(contex);
	}

	std::cout << "stop model: " << model->getName() << std::endl;
	int i = 1;
}
