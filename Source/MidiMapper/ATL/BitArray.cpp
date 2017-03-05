#include "BitArray.h"

namespace ATL {
    
    // BitArray template specializations
    // \todo These specializations should be made on datatype length - not on specific types.

    template<>
    void BitArray<uint8_t>::Reverse()
    {
        _bits = (_bits & 0xF0) >> 4 | (_bits & 0x0F) << 4;
        _bits = (_bits & 0xCC) >> 2 | (_bits & 0x33) << 2;
        _bits = (_bits & 0xAA) >> 1 | (_bits & 0x55) << 1;
    }

    template<>
    void BitArray<uint16_t>::Reverse()
    {
        _bits = (_bits & 0xFF00) >> 8 | (_bits & 0x00FF) << 8;
        _bits = (_bits & 0xF0F0) >> 4 | (_bits & 0x0F0F) << 4;
        _bits = (_bits & 0xCCCC) >> 2 | (_bits & 0x3333) << 2;
        _bits = (_bits & 0xAAAA) >> 1 | (_bits & 0x5555) << 1;
    }

} // ATL   