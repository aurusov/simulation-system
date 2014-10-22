#include <simsys/model.h>
#include <simsys/simulation_system.h>

#include "client_incoming.h"
#include "hair_cut_finished.h"

void main()
{
	LPModel barber(new Model("barber"));
	barber->getParamList()["barber_state"] = false;
	barber->getParamList()["queue_length"] = 0;

	LPIEvent pClientIncomingEvent(new ClientIncomingEvent());
	LPIEvent pHairCutFinishedEvent(new HairCutFinishedEvent());
	barber->pushEvent("incoming", pClientIncomingEvent);
	barber->pushEvent("hair_cut", pHairCutFinishedEvent);

	boost::intrusive_ptr<SimulationSystem> simulationSystem(new SimulationSystem());
	LPIPlanningService planningService(simulationSystem);
	LPIModelTimeService modelTimeService(simulationSystem);

	ClientIncomingEvent* pIncomingClient = static_cast<ClientIncomingEvent*>(pClientIncomingEvent.get());
	boost::optional<double> incomingFirstClientTime = pIncomingClient->getNextInterval();
	if (incomingFirstClientTime.is_initialized())
	{
		planningService->planning(modelTimeService->timeNow() + incomingFirstClientTime.get(), pClientIncomingEvent);
	}

	simulationSystem->run(barber);
}
