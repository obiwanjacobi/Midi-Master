#ifndef INDEXCOLLECTION_H_
#define INDEXCOLLECTION_H_

#include "ATL/Array.h"
#include "ATL/Collection.h"

#include <string.h>

using namespace ATL;



template<const uint8_t MaxSize>
class ValueSequence
{
public:
    typedef enum
    {
        None = 0x00,
        Value = 0x40,
        RangeStart = 0x80,
        RangeEnd = 0xC0,

        EncodingMask = 0x3F

    } Encoding;

    inline void Clear()
    {
        _data.Clear();
    }

    inline uint8_t getCapacity() const
    {
        return _data.getCapacity();
    }

    inline uint8_t getCount() const
    {
        return _data.getCount();
    }

    inline bool IsValidIndex(int16_t index) const
    {
        return _data.IsValidIndex(index);
    }

    inline void Add(uint8_t value)
    {
        _data.Add(Value | (value & EncodingMask));
    }

    inline void AddRange(uint8_t start, uint8_t end)
    {
        _data.Add(RangeStart | (start & EncodingMask));
        _data.Add(RangeEnd | (end & EncodingMask));
    }

    inline uint8_t GetValueAt(int16_t index) const
    {
        return _data.GetAt(index) & EncodingMask;
    }

    inline Encoding GetEncodingAt(int16_t index) const
    {
        return (Encoding)(_data.GetAt(index) & ~EncodingMask);
    }


    // T => Array or derived (Collection).
    template<typename T>
    inline void Assign(T array)
    {
        uint8_t last = 0;
        bool inRange = false;

        for(uint8_t i = 0; i < array.getCount(); i++)
        {
            uint8_t value = array.GetAt(i);

            if (inRange)
            {

            }
            else if (value == last + 1)
            {
                
            }
        }
    }

private:
    ATL::Collection<ATL::Array<uint8_t, MaxSize> > _data;

};

template<typename ValueSequenceT>
class SequenceIterator
{
public:
    /** Constructs a new Iterator for the sequence.
    */
    SequenceIterator(const ValueSequenceT& collection)
        : _sequence(collection)
    {
        Reset();
    }

    /** Moves to the next item in the sequence.
    *  \return Returns true when successful.
    */
    inline bool MoveNext()
    {
        // not iterating a range
        if (_nextRangeValue == 0)
        {
            if (_sequence.IsValidIndex(_index) &&
                _sequence.GetEncodingAt(_index) == ValueSequenceT::RangeStart)
            {
                _nextRangeValue = _sequence.GetValueAt(_index) + 1;
            }

            _index++;
            return _sequence.IsValidIndex(_index);
        }
        else
        {
            if (_sequence.GetEncodingAt(_index) != ValueSequenceT::RangeEnd)
                return false;   // must be

            if (_nextRangeValue >= _sequence.GetValueAt(_index))
            {
                _nextRangeValue = 0;
                _index++;
                return _sequence.IsValidIndex(_index);
            }

            _nextRangeValue++;
            return true;
        }
        return false;
    }

    /** Resets the current position to just before the beginning.
    *  MoveNext must be called before there is a valid current item.
    */
    inline void Reset()
    {
        _index = -1;
        _nextRangeValue = 0;
    }

    /** Retrieves the item at the current position.
    *  \return Returns the item or a Default value if the current position is not valid.
    */
    inline uint8_t getCurrent() const
    {
        if (_nextRangeValue != 0) 
            return _nextRangeValue;

        return _sequence.GetValueAt(_index);
    }

private:
    const ValueSequenceT& _sequence;
    int16_t _index;
    uint8_t _nextRangeValue;
};


template <typename ValueArrayT, typename ValueSequenceT>
class ValueSequenceIterator
{
public:
    ValueSequenceIterator(ValueArrayT& values, const ValueSequenceT sequence)
        : _values (values), _sequence(sequence)
    { }

    /** Moves to the next value in the sequence.
    *  \return Returns true when successful.
    */
    inline bool MoveNext()
    {
        return _sequence.MoveNext();
    }

    /** Resets the current position to just before the beginning.
    *  MoveNext must be called before there is a valid current value.
    */
    inline void Reset()
    {
        _sequence.Reset();
    }

    /** Retrieves the value at the current position.
    *  \return Returns the item or a Default value if the current position is not valid.
    */
    inline typename ValueArrayT::ItemT& getCurrent()
    {
        return _values.GetAt(_sequence.getCurrent());
    }

private:
    const SequenceIterator<ValueSequenceT> _sequence;
    ValueArrayT& _values;
};

#endif /* INDEXCOLLECTION_H_ */