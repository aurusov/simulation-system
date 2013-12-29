
#ifndef _SIMULATION_SYSTEM_PLANNING_SERVICE_H_
#define _SIMULATION_SYSTEM_PLANNING_SERVICE_H_

#include <boost/smart_ptr.hpp>
#include "ref_counter.h"
#include "model_time.h"
#include "event_i.h"

class IPlanningService: virtual public ref_counter
{
public:
	virtual ~IPlanningService() {};

	virtual void planning(const ModelTime& time, const LPIEvent& event) = 0;
};

inline void intrusive_ptr_add_ref(IPlanningService* p)
{
    ++p->ref_count;
}

inline void intrusive_ptr_release(IPlanningService* p)
{
    if (--p->ref_count == 0)
        delete p;
}

typedef  boost::intrusive_ptr<IPlanningService>  LPIPlanningService;

#endif // _SIMULATION_SYSTEM_PLANNING_SERVICE_H_
