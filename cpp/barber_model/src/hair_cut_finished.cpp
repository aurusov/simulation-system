#include <boost/assign/std/vector.hpp>
#include <iostream>
#include <simsys/model.h>
#include <simsys/planning_service.h>
#include <simsys/model_time_service.h>

#include "hair_cut_finished.h"

HairCutFinishedEvent::HairCutFinishedEvent()
{
	using namespace boost::assign;
	durationList += 18, 12, 14, 15, 14, 15, 13, 14, 17;
	currantDurationIt = durationList.begin();
}

HairCutFinishedEvent::~HairCutFinishedEvent()
{}

boost::optional<double> HairCutFinishedEvent::getNextDuration()
{
	boost::optional<double> duration;

	if (currantDurationIt != durationList.end())
	{
		duration = *currantDurationIt;
		++currantDurationIt;
	}

	return duration;
}

void HairCutFinishedEvent::onEvent(const EventContext& contex)
{
	int queue_length = boost::any_cast<int>(contex.model->getParamList()["queue_length"]);
	if (queue_length > 0)
	{
		--queue_length;
		contex.model->getParamList()["queue_length"] = queue_length;

		boost::optional<double> duration = getNextDuration();
		if (duration.is_initialized())
		{
			contex.planningService->planning(contex.modelTimeService->timeNow() + duration.get(), LPIEvent(this));
		}
	}
	else if (queue_length == 0)
	{
		contex.model->getParamList()["barber_state"] = false;
	}

	std::cout << contex.modelTimeService->timeNow().getTime() << ": HairCutFinishedEvent::onEvent()" << std::endl;
}
