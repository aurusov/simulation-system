
#include <iostream>
#include "model.h"

Model::Model(const std::string& _name)
	: name(_name)
{}

Model::~Model()
{}

const std::string& Model::getName() const
{
	return name;
}

Model::ParamList& Model::getParamList()
{
	return paramList;
}

void Model::pushEvent(const std::string& name, const LPIEvent& event)
{
	eventList[name] = event;
}

LPIEvent Model::getEvent(const std::string& name) const
{
	return eventList.find(name)->second;
}
