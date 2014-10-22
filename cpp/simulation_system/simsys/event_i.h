
#ifndef _SIMULATION_SYSTEM_EVENT_I_H_
#define _SIMULATION_SYSTEM_EVENT_I_H_

#include <boost/smart_ptr.hpp>
#include "ref_counter.h"
#include "model_time_service.h"

class IPlanningService;
void intrusive_ptr_add_ref(IPlanningService* p);
void intrusive_ptr_release(IPlanningService* p);
typedef  boost::intrusive_ptr<IPlanningService>  LPIPlanningService;

class Model;
void intrusive_ptr_add_ref(Model* p);
void intrusive_ptr_release(Model* p);
typedef  boost::intrusive_ptr<Model>  LPModel;

struct EventContext
{
	EventContext(const LPIModelTimeService& modelTimeService, const LPIPlanningService& planningService, const LPModel model)
		: modelTimeService(modelTimeService)
		, planningService(planningService)
		, model(model)
	{}

	LPIModelTimeService modelTimeService;
	LPIPlanningService  planningService;
	LPModel             model;
};

class IEvent: public ref_counter
{
public:
	virtual ~IEvent() {}

	virtual void onEvent(const EventContext& contex) = 0;
};

typedef  boost::intrusive_ptr<IEvent>  LPIEvent;

#endif // _SIMULATION_SYSTEM_EVENT_I_H_
