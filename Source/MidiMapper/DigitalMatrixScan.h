#ifndef DIGITALMATRIXSCAN_H_
#define DIGITALMATRIXSCAN_H_

template<typename DigitalInputPin1, typename DigitalInputPin2, typename DigitalInputPin3, typename DigitalInputPin4>
class DigitalMatrixScan
{
public:
    inline uint8_t Scan()
    {
        return (_inputPin4.Read() << 3) |(_inputPin3.Read() << 2) | (_inputPin2.Read() << 1) | _inputPin1.Read();
    }

private:
    DigitalInputPin1 _inputPin1;
    DigitalInputPin2 _inputPin2;
    DigitalInputPin3 _inputPin3;
    DigitalInputPin4 _inputPin4;
};


#endif /* DIGITALMATRIXSCAN_H_ */