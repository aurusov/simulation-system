#include <iostream>
#include <boost/assign/std/vector.hpp>
#include <simsys/planning_service.h>
#include <simsys/model_time_service.h>
#include <simsys/model.h>

#include "client_incoming.h"
#include "hair_cut_finished.h"

ClientIncomingEvent::ClientIncomingEvent()
{
	using namespace boost::assign;
	intervalList += 14, 13, 17, 15, 16, 15, 14, 22, 19;
	currentItervalIt = intervalList.begin();
}

ClientIncomingEvent::~ClientIncomingEvent()
{}

boost::optional<double> ClientIncomingEvent::getNextInterval()
{
	boost::optional<double> interval;

	if (currentItervalIt != intervalList.end())
	{
		interval = *currentItervalIt;
		++currentItervalIt;
	}

	return interval;
}

void ClientIncomingEvent::onEvent(const EventContext& contex)
{
	boost::optional<double> interval = getNextInterval();
	if (interval.is_initialized())
	{
		contex.planningService->planning(contex.modelTimeService->timeNow() + interval.get(), LPIEvent(this));
	}

	bool barber_state = boost::any_cast<bool>(contex.model->getParamList()["barber_state"]);
	if (barber_state)
	{
		int queue_length = boost::any_cast<int>(contex.model->getParamList()["queue_length"]);
		++queue_length;
		contex.model->getParamList()["queue_length"] = queue_length;
	}
	else
	{
		contex.model->getParamList()["barber_state"] = true;
		LPIEvent pHairCutBase = contex.model->getEvent("hair_cut");
		HairCutFinishedEvent* pHairCut = static_cast<HairCutFinishedEvent*>(pHairCutBase.get());
		boost::optional<double> duration = pHairCut->getNextDuration();
		contex.planningService->planning(contex.modelTimeService->timeNow() + duration.get(), pHairCutBase);
	}

	std::cout << contex.modelTimeService->timeNow().getTime() << ": ClientIncomingEvent::onEvent() " << std::endl;
}
