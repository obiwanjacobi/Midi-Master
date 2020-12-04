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

#ifndef __TEXTCONTROL_H__
#define __TEXTCONTROL_H__

#include <stdint.h>
#include "EditControl.h"

namespace ATL {

    /** The TextControl is a text edit control that allows a FixedString to be edited.
     *	\tparam StringT is a FixedString type that holds the string and implements 
     *  `typename ItemT`
     *  `ItemT GetAt(uint8_T)` (Array)
     *  `void SetAt(uint8_t, ItemT)` (FixedArray)
     *  `uint8_t getCapacity()` (Array).
     *	\tparam CharacterIteratorT is an Iterator that manages the characters that can be selected 
     *  when editing the TextControl and implements:
     *  `bool MoveNext()` (Iterator)
     *  `bool MoveBack()` (Iterator)
     *  `bool MoveTo(char)` (Iterator)
     *  `char getCurrent() const` (Iterator).
	 */
    template<class StringT, class CharacterIteratorT>
    class TextControl : public EditControl<StringT, CharacterIteratorT, TextControl<StringT, CharacterIteratorT> >
    {
        typedef EditControl<StringT, CharacterIteratorT, TextControl<StringT, CharacterIteratorT> > BaseT;
        friend BaseT;

    public:
        /** Constructs an initialized instance.
         *  \param str points to the string buffer of the FixedString that is being edited.
         *  \param iterator points to the Iterator that provides the characters during editing.
         *  \param pos is an optional position relative to its siblings.
         */
        TextControl(StringT* str, CharacterIteratorT* iterator, uint8_t pos = 0)
            : BaseT(str, iterator, this, pos)
        { }
    };

} // ATL

#endif //__TEXTCONTROL_H__