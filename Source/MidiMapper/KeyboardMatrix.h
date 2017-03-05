#ifndef KEYBOARDMATRIX_H_
#define KEYBOARDMATRIX_H_

#include "DigitalMatrixScan.h"

#include "ATL/AVR/DigitalOutputPin.h"
#include "ATL/AVR/DigitalInputPin.h"



typedef DigitalMatrixScan<DigitalInputPin<PortA, Pin0>, 
                          DigitalInputPin<PortA, Pin1>, 
                          DigitalInputPin<PortA, Pin2>, 
                          DigitalInputPin<PortA, Pin3> 
                        > 
        MatrixScanLine;

class KeyboardMatrix : public MatrixScanLine
{
    
public:
    KeyboardMatrix()
        : _keyCode(0)
    {
        // keyboard is on PortA so disable ADC (also on PortA)
        ADCSRA = 0;
    }
    
    inline uint8_t getKeyCode() const
    {
        return _keyCode;
    }
    
    inline uint8_t Scan()
    {
        uint8_t result;
        
        _scanLine1.Write(true);
        Delay<TimeResolution::Microseconds>::Wait(1);
        result = MatrixScanLine::Scan();
        _scanLine1.Write(false);
        
        _scanLine2.Write(true);
        Delay<TimeResolution::Microseconds>::Wait(1);
        result |= MatrixScanLine::Scan() << 4;
        _scanLine2.Write(false);
        
        return result;
    }
    
protected:
    inline bool Read()
    {
        _keyCode = Scan();
        return _keyCode != 0;
    }
    
private:
    uint8_t _keyCode;
    DigitalOutputPin<PortA, Pin4> _scanLine1;
    DigitalOutputPin<PortA, Pin5> _scanLine2;
};



#endif /* KEYBOARDMATRIX_H_ */