
#ifndef _SIMULATION_SYSTEM_MODEL_H_
#define _SIMULATION_SYSTEM_MODEL_H_

#include <string>
#include <list>
#include <map>
#include <boost/any.hpp>
#include <boost/smart_ptr.hpp>

#include "event_i.h"

class Model: public ref_counter
{
public:
	Model(const std::string& name);
	virtual ~Model();

	const std::string& getName() const;

	typedef std::map<std::string, boost::any> ParamList;
	ParamList& getParamList();

	void pushEvent(const std::string& name, const LPIEvent& event);
	LPIEvent getEvent(const std::string& name) const;

private:
	typedef  std::map<std::string, LPIEvent>  NamedEventList;
	std::string     name;
	NamedEventList  eventList;
	ParamList       paramList;
};

inline void intrusive_ptr_add_ref(Model* p)
{
    ++p->ref_count;
}

inline void intrusive_ptr_release(Model* p)
{
    if (--p->ref_count == 0)
        delete p;
}

typedef  boost::intrusive_ptr<Model>  LPModel;

#endif // _SIMULATION_SYSTEM_MODEL_H_
