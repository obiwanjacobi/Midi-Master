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

#ifndef __USARTINPUTSTREAM_H__
#define __USARTINPUTSTREAM_H__

#include <stdint.h>

namespace ATL {
namespace MCU {

/** The UsartInputStream can be constructed around the UsartReceive class
 *  to add buffered and interrupt based data reception.
 *  \tparam BaseT is used as base class and is the UsartReceive class and implements
 *  `void Flush()`
 *  `void setEnableIsCompleteInterrupt(bool)`
 *  `void Close()`
 *  `UsartReceiveResult getResult() const` (protected)
 *  `int16_t ReadInternal()` (protected)
 *  \tparam BufferT is class that implements the RingBuffer.
 *	`uint8/16_t getCount() const`
 *  `uint8/16_t getCapacity() const`
 *	`void Clear()`
 *	`int16_t Read()`
 *	`void Write(uint8/16_t)`
 */
template<typename BaseT, typename BufferT>
class UsartInputStream : public BaseT
{
public:
    /** Returns the number of bytes that are available in the stream.
     *  \return Returns 0 (zero) when empty.
     */
    inline uint16_t getCount() const
    {
        return _buffer.getCount();
    }

    inline bool getIsEmpty() const
    {
        return _buffer.getIsEmpty();
    }

    /** Removes all content from the stream.
     *  Keeps reading the input stream until there is nothing left.
     */
    inline void Clear()
    {
        BaseT::Flush();
        _buffer.Clear();
    }

    /** Reads one byte from the stream.
     *  It turns on the receive interrupt when no data is available (first read is always -1).
     *  \return Returns the byte read in the lsb (up to 9 bits). 
     *  If -1 is returned, no data was available or an error occurred.
     */
    inline int16_t Read()
    {
        if (!_buffer.getIsEmpty())
        {
            return _buffer.Read();
        }
        
        BaseT::setEnableIsCompleteInterrupt(true);
        return -1;
    }
    
	inline bool TryRead(int16_t& outData)
	{
		if (!_buffer.getIsEmpty())
		{
			outData = _buffer.Read();
			return true;
		}
		
		outData = 0;
		BaseT::setEnableIsCompleteInterrupt(true);
		return false;
	}
	
    /** Call this method from the `ISR(USARTn_RX_vect)` interrupt handler.
     *  Not meant to be called from regular code.
     */
    inline void OnIsCompleteInterrupt()
    {
        UsartReceiveResult result = BaseT::getResult();
        int16_t data = BaseT::ReadInternal();
        
        if (result == UsartReceiveResult::Success)
            _buffer.Write((typename BufferT::ItemT)data);
    }
    
    /** Retrieves the buffer size used for storing received data.
     *  \return Returns the size of the internal buffer.
     */
    inline uint16_t getBufferSize() const
    {
        return _buffer.getCapacity();
    }
    
    /** Closes the input stream and receiver.
     *  Data still in the buffer is lost.
     */
    inline void Close()
    {
        _buffer.Clear();
        BaseT::Close();
    }

private:
    BufferT _buffer;
};

}}	// ATL::MCU

#endif // __USARTINPUTSTREAM_H__