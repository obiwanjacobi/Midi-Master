#ifndef TIME_AVR_H_
#define TIME_AVR_H_

#include "../Time.h"
#include "TimerCounter.h"

namespace ATL {
    
/** Captures the time ticks (specialized).
 *  \return Returns delta-time in milliseconds.
 */
template<>
inline uint32_t Time<TimeResolution::Milliseconds>::Update()
{
    uint32_t previous = _ticks;

    _ticks = TimerCounter::getMilliseconds();

    return _ticks - previous;
}

/** Captures the time ticks (specialized).
 *  \return Returns delta-time in microseconds.
 */
template<>
inline uint32_t Time<TimeResolution::Microseconds>::Update()
{
    uint32_t previous = _ticks;

    _ticks = TimerCounter::getMicroseconds();

    return _ticks - previous;
}

} // ATL    



#endif /* TIME_AVR_H_ */