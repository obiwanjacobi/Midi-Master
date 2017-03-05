#include "TimerCounter.h"
#include <avr/interrupt.h>

namespace ATL {
namespace MCU {

volatile uint32_t TimerCounter::_milliCount;
volatile uint32_t TimerCounter::_overflowCount;
uint8_t TimerCounter::_fractureCount;

}} // ATL::MCU

ISR(TIMER0_OVF_vect)
{
    ATL::MCU::TimerCounter::OnTimerOverflowInterrupt();
}
