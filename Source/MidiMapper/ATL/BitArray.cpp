/*
Arduino Template Library http://atl.codeplex.com
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