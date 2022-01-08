#ifndef EDITCONTROL_H_
#define EDITCONTROL_H_

#include <stdint.h>
#include "UpDownControl.h"

namespace ATL {

    /** The EditControl is a text edit control that allows a FixedString to be edited.
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
     *	\tparam ValueT is the type used to receive the UpDownControl<ValueT> calls and implements:
     *  `const char* getText()`
     *  `void IncrmentValue()`
     *  `void DecrmentValue()`.
     *  These methods are implemented on EditControl itself.
     */
    template<class StringT, class CharacterIteratorT, class ValueT>
    class EditControl : public UpDownControl<ValueT>
    {
        typedef UpDownControl<ValueT> BaseT;
        friend BaseT;

    public:
        /** Constructs an initialized instance.
         *  \param str points to the string buffer of the FixedString that is being edited.
         *  \param iterator points to the Iterator that provides the characters during editing.
         *  \param valueThis is used by the UpDownControl to callback value manipulation on.
         *  \param pos is an optional position relative to its siblings.
         */
        EditControl(StringT* str, CharacterIteratorT* iterator, ValueT* valueThis, uint8_t pos = 0)
            : BaseT(valueThis, pos), _iterator(iterator)
        {
            setString(str);
        }

        /** Retrieves the text the TextControl displays.
         *  Called by the UpDownControl to retrieve the 'value' to display.
         *  \return Returns the pointer to the text. Can be NULL.
         */
        inline const char* getText() const
        {
            return (const char*)_str;
        }

        /** Assigns the String the TextControl displays.
         *  \param text points to a string instance.
         *  The string is NOT copied and the same buffer is used for editing.
         */
        inline void setString(StringT* str)
        {
            _str = str;
            _editIndex = _str == nullptr ? -1 : 0;
            RepositionIterator();
        }

        /** Overridden to display the cursor on the character position that is being edited.
         *  \param output is used to output text and position the cursor.
         *  \mode indicates what to display.
         */
        void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal) override
        {
            //BaseT::Display(output, mode);
            if (mode == ControlDisplayMode::Normal)
            {
                const char* text = getText();
                if (text != nullptr)
                    output->Display(text);

                // erase empty control space
                //for (uint8_t i = strlen(text); i <= CharacterLength(); i++)
                //{
                    //output->Display(" ");
                //}
            }
            else if (mode == ControlDisplayMode::Cursor && BaseT::getIsSelected())
            {
                output->GoTo(DisplayWriter::CurrentPos, BaseT::getPosition() + _editIndex);
            }
        }

        /** Handles the `Left` and `Right` navigation commands to change editing position inside the string.
         *  \param navCmd is the navigation command.
         *  \return Returns true if the command was handled.
         */
        bool OnNavigationCommand(NavigationCommands navCmd) override
        {
            bool handled = false;

            switch (navCmd.value)
            {
            case NavigationCommands::Left:
                handled = TryMoveCursorLeft();
                break;
            case NavigationCommands::Right:
                handled = TryMoveCursorRight();
                break;
            default:
                break;
            }

            if (handled) return true;

            return BaseT::OnNavigationCommand(navCmd);
        }

        /** Attempts to move the editing cursor to the right.
         *  \return Returns true when successful (even when the end of the string was reached).
         */
        inline bool TryMoveCursorRight()
        {
            if (BaseT::getIsSelected())
            {
                if (_editIndex + 1 < CharacterLength())
                {
                    _editIndex++;
                    RepositionIterator();
                }
                return true;
            }

            return false;
        }

        /** Attempts to move the editing cursor to the left.
         *  \return Returns true when successful (even when the start of the string was reached).
         */
        inline bool TryMoveCursorLeft()
        {
            if (BaseT::getIsSelected())
            {
                if (_editIndex > 0)
                {
                    _editIndex--;
                    RepositionIterator();
                }
                return true;
            }

            return false;
        }

    protected:
        /** Called by the UpDownControl to increment the 'value' - char at edit position.
         */
        inline void IncrementValue()
        {
            if (_str != nullptr && _iterator->MoveNext())
            {
                _str->SetAt(_editIndex, _iterator->getCurrent());
            }
        }

        /** Called by the UpDownControl to decrement the 'value' - char at edit position.
         */
        inline void DecrementValue()
        {
            if (_str != nullptr && _iterator->MoveBack())
            {
                _str->SetAt(_editIndex, _iterator->getCurrent());
            }
        }

        /** Helper method that sets the CharacterIteratorT at the character at the current edit position.
         */
        inline void RepositionIterator()
        {
            if (_str != nullptr && _editIndex >= 0)
            {
                _iterator->MoveTo(_str->GetAt(_editIndex));
            }
        }

        /** Overridden to manage the character edit position when going in/out of `Focused` and `Selected`.
         *  Does not alter behavior.
         *  \param newState is the proposed state.
         *  \return Returns true when the state change is allowed.
         */
        bool BeforeChangeState(ControlState newState) override
        {
            if (!BaseT::BeforeChangeState(newState)) return false;

            if (newState == ControlState::Focused)
            {
                _editIndex = 0;
            }

            if (newState == ControlState::Selected)
            {
                _editIndex = 0;
                RepositionIterator();
            }

            return true;
        }

    private:
        StringT* _str;
        CharacterIteratorT* _iterator;
        uint8_t _editIndex;

        inline uint8_t CharacterLength() const
        {
            return _str->getCapacity() - 1;
        }
    };

} // ATL




#endif /* EDITCONTROL_H_ */