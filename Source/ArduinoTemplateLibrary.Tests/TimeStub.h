#ifndef __TIMESTUB_H__
#define __TIMESTUB_H__

#include "Time.h"

namespace ATL {

	/** Captures the time ticks (specialized).
	*  \return Returns delta-time in milliseconds.
	*/
	template<>
	inline uint32_t Time<TimeResolution::Milliseconds>::Update()
	{
		return 3;
	}

	/** Captures the time ticks (specialized).
	*  \return Returns delta-time in microseconds.
	*/
	template<>
	inline uint32_t Time<TimeResolution::Microseconds>::Update()
	{
		return 42;
	}

}	// ATL

#endif //__TIMESTUB_H__