#ifndef DUMMYDIGITALPIN_H_
#define DUMMYDIGITALPIN_H_

template<const Ports PortId, const Pins PinId>
class DummyDigitalPin
{
public:
    DummyDigitalPin(){}
        
    DummyDigitalPin(bool /*initialValue*/)
    {
    }

    /*
        Writes the value to the BoardPinNumder.
     */
    inline void Write(bool value) const
    {
    }

    /*
        Reads the value from the Pin on the Port.
     */
    inline bool Read()
    {
        return false;
    }

    /*
        Enables (true) or disables (false) the internal pull-up resistor the AVR (MCU) has on digital input pins.
     */
    inline void EnableInternalPullup(bool /*enable = true*/)
    {
    }
    
    /*
        Returns the PortId template parameter.
     */
    inline uint8_t getPortNumber() const
    {
        return PortId;
    }

    /*
        Returns the PinId template parameter.
     */
    inline uint8_t getPinNumber() const
    {
        return PinId;
    }

};


#endif /* DUMMYDIGITALPIN_H_ */