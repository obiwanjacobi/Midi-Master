#ifndef TIMER_H_
#define TIMER_H_

namespace ATL {
namespace MCU {
    
// ClkSrc -> Counter -> compare -> PWM/isr

// Timer (8 bits)
// Counter (8 bits)
// CounterConfig/TimerConfig/CompareConfig
// TimerOutputCompare (A/B)
// TimerWaveGen (pwm)
// CounterClockSource
// Counter/Timer/Compare-Registers

BeginEnum(Timer8Ids)
{
    Timer0 = 0,
    Timer2 = 2
}
EndEnum(Timer8Ids)

template<const uint8_t TimerId>
class TimerRegisters
{
public:
    inline static volatile uint8_t& getTCNT()
    {
        return TCNT0;
    }
    
    inline static volatile uint8_t& getOCRA()
    {
        return OCR0A;
    }
    
    inline static volatile uint8_t& getOCRB()
    {
        return OCR0B;
    }
    
    inline static volatile uint8_t& getOCFA()
    {
        return OCF0A;
    }
    
    inline static volatile uint8_t& getOCFB()
    {
        return OCF0B;
    }
    
    inline static volatile uint8_t& getTCCRA()
    {
        return TCCR0A;
    }
    
    inline static volatile uint8_t& getTCCRB()
    {
        return TCCR0B;

    }
    inline static volatile uint8_t& getTIFR()
    {
        return TIFR0;
    }
    
    inline static volatile uint8_t& getTIMSK()
    {
        return TIMSK0;
    }
    
private:
    TimerRegisters(){}
};

/*
        Mode (WGM)		WGM2	TOP	    OCA Pin	                OCB Pin                	TOV
        0	Normal	    0	    0xFF	Toggle, Set*, Clear*	Toggle, Set*, Clear*	0xFF
        1	PWM	        0	    0xFF	Set, Clear	            Set, Clear			    0x00
        2	CTC	        0	    OCRA	Toggle, Set*, Clear*	Toggle, Set*, Clear*	0xFF
        3	FastPWM	    0	    0xFF	Set, Clear	            Set, Clear			    0xFF
        5	PWM	        1	    OCRA	Toggle, Set*, Clear*	Set, Clear			    0x00
        7	FastPWM	    1	    OCRA	Toggle, Set*, Clear*	Set, Clear			    OCRA
        
        * Single shot: sets pin high or low.
        Off mode always available.
        PWM: Set=Inverting/Clear=Non-Inverting
 */


class CounterConfig
{
public:
    // waveform generation modes
    enum Modes
    {
        Off,
        Normal,
        CTC_A,  // only toggle pin-modes for OCA and OCB
        PWM,
        FastPWM
    };
    
    inline void setCounterMode(Modes mode)
    {
        
    }
    
    inline Modes getCounterMode() const
    {
        return Off;
    }
    
    // set prescaler
};

class OutputCompareConfig
{
public:
    // enabling pins and pin-modes are optional (Off)

    enum PinModes
    {
        Off,
        Toggle,
        Clear,  // triggers pin only once
        Set     // triggers pin only once
    };
    
    
    enum PinPWM
    {
        Off,
        ToggleA,    // only A! and must have WGM02 set (and vica-versa)! OCB-value (if active) must be smaller than OCA-value!
        Normal,
        Inverting
    };
};

// it is possible to use OCA0 as a period timebase (WGM02 is set) and trigger OCB0 (valueB < valueA)
// this allows fine-tuning of period/frequency. 

class TimerConfig : public CounterConfig
{
public:
    // clk source: off, pre-scaler, ext(edge)
    // compare A off/modes  // set output pin mode (off, toggle, clear, set)/ set direction
    // compare B off/modes  // set output pin mode (off, toggle, clear, set)/ set direction
    
    OutputCompareConfig OutputCompareA;
    OutputCompareConfig OutputCompareB;
    
    
};


<const uint8_t TimerId>
class TimerOutputCompare
{
public:
    inline bool Open(OutputCompareConfig& config)
    {
        return false;
    }

    inline void setCompareValue(uint8_t value)
    {
        // OCRnx
    }
    
    inline uint8_t getCompareValue() const
    {
        return 0;
    }
    
    inline void setEnableInterrupt(bool enable = true)
    {
        // TIMSK - OCIEnx
    }
    
    inline bool getEnableInterrupt() const
    {
        return false;
    }
    
    inline bool getIsMatch() const
    {
        // TIFRn - OCFnx
        return false;
    }
    
    inline void ClearMatch()
    {
        
    }
};    

template<const uint8_t TimerId>    
class Counter
{
public:
    inline bool Open(CounterConfig& config)
    {
        return false;
    }
    
    inline void setCounterValue(uint8_t value)
    {
        // TCNTn
    }
    
    inline uint8_t getCounterValue() const
    {
        return 0;
    }

    inline void setEnableInterrupt(bool enable = true)
    {
        // TIMSK - TOIEn
    }
    
    inline bool getEnableInterrupt() const
    {
        return false;
    }

    inline bool getIsOVerflow() const
    {
        // TIFRn - TOVn
        return false;
    }
};

// BaseT=Counter
template<typename BaseT, typename OutputCompareAT, typename OutputCompareBT>
class Timer : public BaseT
{
public:
    inline bool Open(TimerConfig& config)
    {
        return false;
    }

    

    OutputCompareAT OutputCompareA;
    OutputCompareBT OutputCompareB;
};



// BaseT = TimerOutputCompare
template<typename BaseT>
class TimerWaveGen : public BaseT
{
public:
    
};


}} // ATL::MCU

#endif /* TIMER_H_ */