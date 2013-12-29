
#ifndef _SIMULATION_SYSTEM_HAIR_CUT_FINISHED_H_
#define _SIMULATION_SYSTEM_HAIR_CUT_FINISHED_H_

#include <vector>
#include <boost/optional.hpp>
#include <simsys/event_i.h>

class HairCutFinishedEvent: public IEvent
{
public:
	HairCutFinishedEvent();
	~HairCutFinishedEvent();

	virtual void onEvent(const EventContext& contex);

	boost::optional<double> getNextDuration();

private:
	typedef std::vector<double> DurationList;
	DurationList                  durationList;
	DurationList::const_iterator  currantDurationIt;
};

#endif // _SIMULATION_SYSTEM_HAIR_CUT_FINISHED_H_
