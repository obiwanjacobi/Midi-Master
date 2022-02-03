#ifndef STRINGEXTENSIONS_H_
#define STRINGEXTENSIONS_H_

#include "DataTypes.h"
//#include <assert.h>


#define MaxToString 15

static StringWriter<MaxToString> _str;

class ToString
{
public:
    template<uint8_t length>
    static const char* Integer(const uint8_t val)
    {
        //static_assert(MaxToString > length, "Specified length too big.");

        _str.Clear();
        _str.Write(val, length);
        return (const char*)_str;
    }
};

#endif /* STRINGEXTENSIONS_H_ */