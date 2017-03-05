#ifndef STRINGSTREAM_H_
#define STRINGSTREAM_H_

namespace ATL {

template<typename BaseT>
class StringStream : public BaseT
{
public:
    // stream interface
    inline void Write(char character)
    {
        BaseT::Add(character);
    }
};

} // ATL

#endif /* STRINGSTREAM_H_ */