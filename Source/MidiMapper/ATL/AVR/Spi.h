/*
Arduino Template Library https://github.com/obiwanjacobi/atl
Written by Marc Jacobi
Copyright 2012-2015 All Rights Reserved

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SPI_H_
#define SPI_H_

#include "../Bit.h"

namespace ATL {
namespace MCU {

//template<>
class SpiRegisters
{
public:
    inline static volatile uint8_t& refSPCR()
    {
        return SPCR;
    }

    inline static volatile uint8_t& refSPSR()
    {
        return SPSR;
    }

    inline static volatile uint8_t& refSPDR()
    {
        return SPDR;
    }

private:
    SpiRegisters()
    { }
};


class SpiConfig
{
public:
    SpiConfig()
        : _clockPolarity(IdleLow), _samplePoint(LeadingEdge), _bitOrder(MostSignificantBitFirst), _speed(ClockFromMaster)
    { }

    typedef enum
    {
        IdleLow,
        IdleHigh
    } ClockPolarity;

    inline void setClockPolarity(ClockPolarity clockPolarity)
    {
        _clockPolarity = clockPolarity;
    }
    inline ClockPolarity  getClockPolarity() const
    {
        return _clockPolarity;
    }

    typedef enum
    {
        LeadingEdge,
        TrailingEdge,
    } SamplePoint;

   inline  void setSamplePoint(SamplePoint samplePoint)
    {
        _samplePoint = samplePoint;
    }
    inline SamplePoint getSamplePoint() const
    {
        return _samplePoint;
    }

    typedef enum
    {
        MostSignificantBitFirst,
        LeastSignificantBitFirst,
    } BitOrder;

    inline void setBitOrder(BitOrder bitOrder)
    {
        _bitOrder = bitOrder;
    }
    inline BitOrder getBitOrder() const
    {
        return _bitOrder;
    }

    typedef enum
    {
        ClockFromMaster,    // for slaves
        ClockDividedBy2,
        ClockDividedBy4,
        ClockDividedBy8,
        ClockDividedBy16,
        ClockDividedBy32,
        ClockDividedBy64,
        ClockDividedBy128,
    } Speed;

    inline void setSpeed(Speed speed)
    {
        _speed = speed;
    }
    inline Speed getSpeed() const
    {
        return _speed;
    }

    //
    // translation to register values
    //

    inline uint8_t getSPCR() const
    {
        uint8_t spcr = 0;

        if (_bitOrder == LeastSignificantBitFirst)
            Bit<DORD>::Set(spcr);

        if (_clockPolarity == IdleHigh)
            Bit<CPOL>::Set(spcr);

        if (_samplePoint == TrailingEdge)
            Bit<CPHA>::Set(spcr);

        switch (_speed)
        {
        case ClockDividedBy8:
        case ClockDividedBy16:
            Bit<SPR0>::Set(spcr);
            break;
        case ClockDividedBy32:
        case ClockDividedBy64:
            Bit<SPR1>::Set(spcr);
            break;
        case ClockDividedBy128:
            Bit<SPR0>::Set(spcr);
            Bit<SPR1>::Set(spcr);
            break;
        default:
            // SPR0/SPR1 are zero
            break;
        }

        return spcr;
    }

    inline uint8_t getSPSR() const
    {
        uint8_t spsr = 0;

        if (_speed % 2 != 0 &&
            _speed != ClockDividedBy128)
        {
            Bit<SPI2X>::Set(spsr);
        }

        return spsr;
    }

private:
    ClockPolarity _clockPolarity;
    SamplePoint _samplePoint;
    BitOrder _bitOrder;
    Speed _speed;
};


// TODO: make the pin-classes device specific.
class SpiMasterPins
{
public:
    typedef DigitalOutputPin<PortB, Pin4> SlaveSelect;
    typedef DigitalOutputPin<PortB, Pin5> MasterOutputSlaveInput;
    typedef DigitalInputPin<PortB, Pin6> MasterInputSlaveOutput;
    typedef DigitalOutputPin<PortB, Pin7> Clock;

    inline static void Initialize()
    {
        SlaveSelect::Initialize();
        MasterOutputSlaveInput::Initialize();
        MasterInputSlaveOutput::Initialize();
        Clock::Initialize();
    }
};

class SpiSlavePins
{
public:
    typedef DigitalInputPin<PortB, Pin4> SlaveSelect;
    typedef DigitalInputPin<PortB, Pin5> MasterOutputSlaveInput;
    typedef DigitalOutputPin<PortB, Pin6> MasterInputSlaveOutput;
    typedef DigitalInputPin<PortB, Pin7> Clock;

    inline static void Initialize()
    {
        SlaveSelect::Initialize();
        MasterOutputSlaveInput::Initialize();
        MasterInputSlaveOutput::Initialize();
        Clock::Initialize();
    }
};


class SpiTransmit
{
public:
    inline bool IsComplete() const
    {
        return Bit<SPIF>::IsTrue(SpiRegisters::refSPSR());
    }

    inline void WaitIsComplete() const
    {
        while (!IsComplete());
    }

    inline void Write(uint8_t data)
    {
        SpiRegisters::refSPDR() = data;
    }

    inline bool TryWrite(uint8_t data)
    {
        if (!IsComplete()) return false;

        Write(data);
        return true;
    }

    inline bool IsWriteCollision() const
    {
        return Bit<WCOL>::IsTrue(SpiRegisters::refSPSR());
    }
};


class SpiReceive
{
public:
    inline bool IsComplete() const
    {
        return Bit<SPIF>::IsTrue(SpiRegisters::refSPSR());
    }

    inline void WaitIsComplete() const
    {
        while (!IsComplete());
    }

    inline uint8_t Read()
    {
        return SpiRegisters::refSPDR();
    }
};


template<class TransmitT = SpiTransmit, class ReceiveT = SpiReceive>
class Spi
{
public:
    inline bool OpenMaster(const SpiConfig& config)
    {
        return Open(config, true);
    }

    // ignores config.Speed
    inline bool OpenSlave(const SpiConfig& config)
    {
        return Open(config, false);
    }

    inline void Close()
    {
        EnableTransferCompleteInterrupt(false);
        Enable(false);
    }

    inline void Enable(bool enable)
    {
        Bit<SPE>::Set(SpiRegisters::refSPCR(), enable);
    }
    inline bool Enable() const
    {
        return Bit<SPE>::IsTrue(SpiRegisters::refSPCR());
    }

    inline void IsMaster(bool enable)
    {
        Bit<MSTR>::Set(SpiRegisters::refSPCR(), enable);
    }
    inline bool IsMaster() const
    {
        return Bit<MSTR>::IsTrue(SpiRegisters::refSPCR());
    }

    inline void EnableTransferCompleteInterrupt(bool enable)
    {
        Bit<SPIE>::Set(SpiRegisters::refSPCR(), enable);
    }
    inline bool EnableTransferCompleteInterrupt() const
    {
        return Bit<SPIE>::IsTrue(SpiRegisters::refSPCR());
    }

    TransmitT Transmit;

    ReceiveT Receive;

private:
    inline bool Open(const SpiConfig& config, bool isMaster)
    {
        uint8_t spcr = config.getSPCR();
        if (isMaster) Bit<MSTR>::Set(spcr);   // is master
        Bit<SPE>::Set(spcr);    // enable
        SpiRegisters::refSPCR() = spcr;

        SpiRegisters::refSPSR() = config.getSPSR();
        return true;
    }
};


}}  // ATL::MCU


#endif /* SPI_H_ */