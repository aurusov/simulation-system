
#ifndef _SIMULATION_SYSTEM_REF_COUNTER_H_
#define _SIMULATION_SYSTEM_REF_COUNTER_H_

struct ref_counter
{
	ref_counter(): ref_count(0)
	{}
	virtual ~ref_counter() {}

	unsigned int ref_count;
};

inline void intrusive_ptr_add_ref(ref_counter* p)
{
    ++p->ref_count;
}

inline void intrusive_ptr_release(ref_counter* p)
{
    if (--p->ref_count == 0)
        delete p;
}

#endif // _SIMULATION_SYSTEM_REF_COUNTER_H_
