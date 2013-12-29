
#ifndef _SIMULATION_SYSTEM_CLIENT_INCOMING_H_
#define _SIMULATION_SYSTEM_CLIENT_INCOMING_H_

#include <vector>
#include <boost/optional.hpp>
#include <simsys/event_i.h>

class ClientIncomingEvent: public IEvent
{
public:
	ClientIncomingEvent();
	~ClientIncomingEvent();

	virtual void onEvent(const EventContext& contex);

	boost::optional<double> getNextInterval();

private:
	typedef std::vector<double> IntervalList;
	IntervalList                  intervalList;
	IntervalList::const_iterator  currentItervalIt;
};

typedef  boost::shared_ptr<ClientIncomingEvent> LPClientIncomingEvent;

#endif // _SIMULATION_SYSTEM_CLIENT_INCOMING_H_
