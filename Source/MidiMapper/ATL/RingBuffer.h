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

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <stdint.h>
#include "LockScope.h"

namespace ATL {

    /** A RingBuffer uses a fixed amount of memory to simulate an 'endless' buffer.
     *  Capacity is always one less than the specified Size.
     *  There is NO under-run detection!
     *  An Array of T[Size] is allocated.
     *  \tparam T is the data type of the buffer items.
     *  \tparam Size is the number of 'T' items in the buffer.
     */
    template <typename T, const uint16_t Size>
    class RingBuffer
    {
    public:
		typedef T ItemT;
		
        /** Constructs the instance.
         */
        RingBuffer()
			: _writeIndex(0), _readIndex(0)
        { }

        /** Clears the buffer.
         *  The actual content is not deleted or reset.
         */
        void Clear()
        {
			LockScope lock;
			
            _writeIndex = 0;
            _readIndex = 0;
        }

        /** Writes the value to the buffer.
         *  The method protects against overrun.
         *  \param value is the value to store in the buffer.
         *  \return Returns true when successful.
         */
        bool Write(T value)
        {
			LockScope lock;
			
            // check for overrun
            if ((_writeIndex + 1) >= Size)
            {
				// TODO: this does not seem right
                if (_readIndex == 0) return false;
            }
            else if ((_writeIndex + 1) == _readIndex) return false;

            _buffer[_writeIndex] = value;
            _writeIndex++;

            if (_writeIndex >= Size)
            {
                _writeIndex = 0;
            }

            return true;
        }

        /** Reads one value from the buffer.
         *  The method does NOT protect against underrun.
         *  \return Returns the value.
         */
        T Read()
        {
			LockScope lock;
			
            T result = _buffer[_readIndex];
            _readIndex++;

            if (_readIndex >= Size)
            {
                _readIndex = 0;
            }

            return result;
        }

        /** Retrieves the number of values in the buffer.
         *  \return Returns the length of the buffer.
         */
        inline uint16_t getCount() const
        {
			LockScope lock;
			
            if (_writeIndex >= _readIndex)
            {
                return _writeIndex - _readIndex;
            }

            return getCapacity() - (_readIndex - _writeIndex);
        }

        inline bool getIsEmpty() const
        {
            return _writeIndex == _readIndex;
        }
        
		inline uint16_t getCapacity() const
		{
			return Size - 1;
		}
		
    private:
        volatile T _buffer[Size];
        volatile uint16_t _writeIndex;
        volatile uint16_t _readIndex;
    };

	
} //ATL

#endif //__RINGBUFFER_H__
