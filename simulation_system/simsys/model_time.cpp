#include "model_time.h"

ModelTime::ModelTime()
	: time(0)
{}

double ModelTime::getTime() const
{
	return time;
}

bool ModelTime::operator< (const ModelTime& other) const
{
	return time < other.time;
}
