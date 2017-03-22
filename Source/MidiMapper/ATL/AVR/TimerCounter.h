#ifndef TIMERCOUNTER_H_
#define TIMERCOUNTER_H_

#include <avr/io.h>
#include "../LockScope.h"
#include "../Time.h"

namespace ATL {
namespace MCU {
    
// This class is a quick implementation taken from Arduino until our own Timer class is ready.
class TimerCounter
{
    // FROM ARDUINO
    // Copyright (c) 2005-2006 David A. Mellis
    
    // the prescaler is set so that timer0 ticks every 64 clock cycles, and the
    // the overflow handler is called every 256 ticks.
    #define Microseconds_Per_Timer0_Overflow Time<TimeResolution::Microseconds>::ForClockCycles(64 * 256)

    // the whole number of milliseconds per timer0 overflow
    #define Millis_Inc (Microseconds_Per_Timer0_Overflow / 1000)

    // the fractional number of milliseconds per timer0 overflow. we shift right
    // by three to fit these numbers into a byte. (for the clock speeds we care
    // about - 8 and 16 MHz - this doesn't lose precision.)
    #define Fract_Inc ((Microseconds_Per_Timer0_Overflow % 1000) >> 3)
    #define Fract_Max (1000 >> 3)
    
public:
    inline static void Start()
    {
        // prescaler to 64
        TCCR0B = (1 << CS00) | (1 << CS01);
        
        // enable overflow interrupt
        TIMSK0 = (1 << TOIE0);
    }
    
    template<TimeResolution::type TimeResolution>
    inline static uint32_t getTime()
    {
        if (TimeResolution == TimeResolution::Milliseconds)
            return getMilliseconds();
        return getMicroseconds();
    }
    
    inline static uint32_t getMilliseconds()
    {
        LockScope lock;
        return _milliCount;
    }
    
    inline static uint32_t getMicroseconds()
    {
        uint32_t micros;
        uint8_t count;
        
        {
            LockScope lock;
            
            micros = _overflowCount;
            count = TCNT0;
            
            // I don't get the (count < 255) - that is always true
            if ((TIFR0 & (1 << TOV0)) && (count < 255))
                micros++;
        }
        
        return ((micros << 8) + count) * (64 / (F_CPU / 1000000L));
    }
    
    // Call from ISR(TIMER0_OVF_vect)
    inline static void OnTimerOverflowInterrupt()
    {
        // copy these to local variables so they can be stored in registers
        // (volatile variables must be read from memory on every access)
        uint32_t millis = _milliCount;
        uint32_t fract = _fractureCount;
        
        millis += Millis_Inc;
        fract += Fract_Inc;
        if (fract >= Fract_Max) {
            fract -= Fract_Max;
            millis += 1;
        }
        
        _milliCount = millis;
        _fractureCount = (uint8_t)fract;
        _overflowCount++;
    }
    
private:
    static volatile uint32_t _milliCount;
    static volatile uint32_t _overflowCount;
    static uint8_t _fractureCount;    // not volatile, only accessed from within ISR
};


}} // ATL::MCU

#endif /* TIMERCOUNTER_H_ */