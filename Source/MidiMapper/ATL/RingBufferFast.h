#ifndef __RINGBUFFERFAST_H__
#define __RINGBUFFERFAST_H__

#include <stdint.h>

namespace ATL {

    /** A smaller (max 255 items) and faster RingBuffer. 
     *	Because of its reduced size no atomic access to its buffer is required. (sizeof(T) == 8!)
     *  Capacity is always one less than the specified Size.
     *  There is NO under-run detection! Call `getCount()` or `getIsEmpty()` before calling `Read()`.
     *  An Array of T[Size+1] is allocated.
     *  \tparam T is the data type of the buffer items.
     *  \tparam Size is the number of 'T' items in the buffer.
     */
    template <typename T, const uint8_t Size>
    class RingBufferFast
    {
        #define ActualSize (Size + 1)

    public:
        typedef T ItemT;
        
        /** Constructs the instance.
         */
        inline RingBufferFast()
            : _writeIndex(0), _readIndex(0)
        { }

        /** Clears the buffer.
         *  The actual content is not deleted or reset.
         */
        inline void Clear()
        {
            _writeIndex = 0;
            _readIndex = 0;
        }

        /** Writes the value to the buffer.
         *  The method protects against overrun.
         *  \param value is the value to store in the buffer.
         *  \return Returns true when successful.
         */
        inline bool Write(T value)
        {
            uint8_t newIndex = _writeIndex + 1;
            if (newIndex >= ActualSize)
            {
                // wrap around
                newIndex = 0;
            }

            // collision detection (buffer full condition)
            if (newIndex == _readIndex) return false;

            _buffer[_writeIndex] = value;
            _writeIndex = newIndex;
            return true;
        }

        /** Retrieves an indication if a call to `Write()` will succeed.
         *  \return Returns true if `Write()` can be called.
         */
        inline bool getCanWrite() const
        {
            return getCapacity() - getCount() > 0;
        }

        /** Reads one value from the buffer.
         *  The method does NOT protect against under-run. Call `getCount()`.
         *  \return Returns the value.
         */
        inline T Read()
        {
            T result = _buffer[_readIndex];
            _readIndex++;

            if (_readIndex >= ActualSize)
            {
                _readIndex = 0;
            }

            return result;
        }

        /** Retrieves the number of values in the buffer.
         *  \return Returns the length of the buffer.
         */
        inline uint8_t getCount() const
        {
            if (_writeIndex >= _readIndex)
            {
                return _writeIndex - _readIndex;
            }

            return ActualSize - (_readIndex - _writeIndex);
        }
        
        inline bool getIsEmpty() const
        {
            return _writeIndex == _readIndex;
        }

        inline uint8_t getCapacity() const
        {
            return Size;
        }
        
    private:
        volatile T _buffer[ActualSize];
        volatile uint8_t _writeIndex;
        volatile uint8_t _readIndex;
    };

} //ATL

#endif /* __RINGBUFFERFAST_H__ */