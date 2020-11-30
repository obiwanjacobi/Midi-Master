#ifndef __DIGITALNOTCONNECTEDPIN_H__
#define __DIGITALNOTCONNECTEDPIN_H__

#include "Port.h"

namespace ATL {
namespace MCU {

/** Can be used at places where a DigitalInputPin or a DigitalOutputPin is required.
 *  The implementation does nothing / has no effect.
 */
template<const Ports PortId, const Pins PinId>
class DigitalNotConnectedPin
{
public:
    DigitalNotConnectedPin()
	{ }
        
    DigitalNotConnectedPin(bool /*initialValue*/)
    { }

    /** Does nothing.
     */
    inline void Write(bool value) const
    { }

    /** Always returns false.
     */
    inline bool Read()
    {
        return false;
    }

    /** Does nothing.
     */
    inline void EnableInternalPullup(bool /*enable = true*/)
    { }
    
    /** Returns the PortId template parameter.
     */
    inline uint8_t getPortNumber() const
    {
        return PortId;
    }

    /** Returns the PinId template parameter.
     */
    inline uint8_t getPinNumber() const
    {
        return PinId;
    }
};

}}	// ATL::MCU

#endif /* __DIGITALNOTCONNECTEDPIN_H__ */