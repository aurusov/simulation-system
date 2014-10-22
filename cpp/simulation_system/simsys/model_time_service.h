
#ifndef _SIMULATION_SYSTEM_MODEL_TIME_SERVICE_H_
#define _SIMULATION_SYSTEM_MODEL_TIME_SERVICE_H_

#include <boost/smart_ptr.hpp>
#include "ref_counter.h"
#include "model_time.h"

class IModelTimeService: virtual public ref_counter
{
public:
	virtual ~IModelTimeService() {};

	virtual const ModelTime& timeNow() const = 0;
};
typedef  boost::intrusive_ptr<IModelTimeService>  LPIModelTimeService;

#endif // _SIMULATION_SYSTEM_MODEL_TIME_SERVICE_H_
