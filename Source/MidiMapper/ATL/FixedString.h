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

#ifndef __FIXEDSTRING_H__
#define __FIXEDSTRING_H__

#include <avr/pgmspace.h>
#include <stdint.h>
#include "FixedArray.h"

namespace ATL {

    /** FixedString is a specialized FixedArray for character strings.
     *  \tparam MaxChars indicates the maximum number of characters in the string. 
     *  The underlying array has one extra byte for the terminating zero.
     *  \tparam FillChar the character used for filling out the capacity. 
     *  Default is 0 which is no filling.
     */
    template<const uint8_t MaxChars, const char FillChar = 0>
    class FixedString : public FixedArray<char, MaxChars + 1>
    {
        typedef FixedArray<char, MaxChars + 1> BaseT;

    public:
        /** ItemT defines the type of array items.
         */
        typedef char ItemT;

        /** Constructs a blank instance.
         */
        FixedString()
        {
            BaseT::Clear();
        }

        /** Constructs an initialized instance.
         *  \param text points to a zero-terminated string used to initialize (copy) this instance.
         */
        FixedString(const char* text)
        {
            BaseT::Clear();
            CopyFrom(text);
        }

        /** Gets the maximum number of chars the string can store.
         *  \return Returns the MaxChars template parameter.
         */
        inline int16_t getCapacity() const
        {
            return MaxChars;
        }

        /** Gets the current number of chars in the string.
         *  \return Returns the string length.
         */
        inline int16_t getCount() const
        {
            return strlen((const char*)this);
        }

        /** Copy's in the specified text.
         *  Will never copy more than MaxChars characters from text.
         *  \param text is a pointer to a zero-terminated string.
         */
        inline void CopyFrom(const char* text)
        {
            auto len = strlen(text);
            auto buffer = BaseT::getBuffer();
            
            strncpy(buffer, text, MaxChars);
            
            if (len < MaxChars)
                memset(buffer + len, FillChar, MaxChars - len);
        }

        /** Copy's in the specified text from PROGMEM.
         *  Will never copy more than MaxChars characters from text.
         *  \param text is a pointer to a zero-terminated string in PROGMEM.
         */
        inline void CopyFromProgMem(const char* text)
        {
            auto len = strlen(text);
            auto buffer = BaseT::getBuffer();
            
            strncpy_P(buffer, text, MaxChars);
            
            if (len < MaxChars)
                memset(buffer + len, FillChar, MaxChars - len);
        }
        
        /** Copy's in the specified text.
         *  Will never copy more than MaxChars characters from text.
         *  \param text is a pointer to a zero-terminated string.
         */
        inline void operator=(const char* text)
        {
            CopyFrom(text);
        }
    };


} // ATL

#endif //__FIXEDSTRING_H__