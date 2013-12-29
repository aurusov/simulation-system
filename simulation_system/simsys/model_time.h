
#ifndef _SIMULATION_SYSTEM_MODEL_TIME_H_
#define _SIMULATION_SYSTEM_MODEL_TIME_H_

class ModelTime
{
public:
	ModelTime();

	double getTime() const;

	bool operator< (const ModelTime& other) const;

	ModelTime operator+ (double delta) const
	{
		ModelTime modelTime;
		modelTime.time = time + delta;
		return modelTime;
	}

	ModelTime operator+ (const ModelTime& delta) const
	{
		ModelTime modelTime;
		modelTime.time = time + delta.time;
		return modelTime;
	}

private:
	double time;
};

#endif // _SIMULATION_SYSTEM_MODEL_TIME_H_
