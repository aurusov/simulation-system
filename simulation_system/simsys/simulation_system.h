
#ifndef _SIMULATION_SYSTEM_SIMULATION_SYSTEM_H_
#define _SIMULATION_SYSTEM_SIMULATION_SYSTEM_H_

#include <map>
#include "model.h"
#include "event_i.h"
#include "model_time.h"
#include "planning_service.h"

class SimulationSystem: public IPlanningService, public IModelTimeService, virtual public ref_counter
{
public:
	SimulationSystem();
	virtual ~SimulationSystem();

	void run(const LPModel& model);

private:
	typedef  std::multimap<ModelTime, LPIEvent>  EventList;
	EventList futureList;
	ModelTime modelTime;

	void planning(const ModelTime& time, const LPIEvent& event);
	const ModelTime& timeNow() const;
};

#endif // _SIMULATION_SYSTEM_SIMULATION_SYSTEM_H_
