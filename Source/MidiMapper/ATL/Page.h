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

#ifndef __PAGE_H__
#define __PAGE_H__

#include <stddef.h>
#include <stdint.h>
#include "NavigationController.h"
#include "ControlContainer.h"
#include "InputControl.h"
#include "DisplayWriter.h"
#include "Panel.h"
#include "VerticalPanel.h"

#include "Debug.h"
#include <assert.h>

namespace ATL {

    /** The Page class manages the Lines that are displayed together as one (page).
     *  Lines run horizontally and are organized in a VerticalPanel.
     *  \tparam MaxLines is the maximum number of lines on the Page.
     */
    template<const uint8_t MaxLines>
    class Page : public VerticalPanel<MaxLines>
    {
        typedef VerticalPanel<MaxLines> BaseT;

    public:
        /** Constructs the instance.
         *  Lines have to be added using the Add method.
         */
        Page()
        { }

        /** Constructs the instance.
         *  Lines can be added using the Add method.
         *  \param line1 is the first line.
         */
        Page(Panel* line1)
        {
            assert(MaxLines >= 1);
            Add(line1);
        }

        /** Constructs the instance.
         *  Lines can be added using the Add method.
         *  \param line1 is the first line.
         *  \param line2 is the second line.
         */
        Page(Panel* line1, Panel* line2)
        {
            assert(MaxLines >= 2);
            Add(line1);
            Add(line2);
        }

        /** Constructs the instance.
         *  Lines can be added using the Add method.
         *  \param line1 is the first line.
         *  \param line2 is the second line.
         *  \param line3 is the third line.
         *  \param line4 is the fourth line.
         */
        Page(Panel* line1, Panel* line2, Panel* line3, Panel* line4)
        {
            assert(MaxLines >= 4);
            Add(line1);
            Add(line2);
            Add(line3);
            Add(line4);
        }

        /** Adds a line to the bottom of the page.
         *  \param line is the line to add. If NULL nothing happens.
         */
        inline void Add(Panel* line)
        {
            if (line == nullptr) return;

            if (line->getPosition() == 0)
            {
                line->setPosition((uint8_t)BaseT::getCount());
            }

            BaseT::Add(line);
        }

        // mode is ignored. Page implements display sequence (normal -> cursor).
        /** Calls `Display` on all its lines.
         *  This method also implements drawing the cursor after a normal call.
         *  \param output is used to output text and position the cursor.
         *  \param mode is not used and is ignored.
         */
        void Display(DisplayWriter* output, ControlDisplayMode /*mode*/) override
        {
            BaseT::Display(output, ControlDisplayMode::Normal);
            DisplayCursor(output);
        }

        /** Routes navigation commands to the active line.
         *  If no Control in the `stateSelected` is present the `Up` and `Down` commands change
         *  the current line.
         *  \param navCmd is the navigation command.
         */
        bool OnNavigationCommand(NavigationCommands navCmd) override
        {
            bool handled = false;

            switch (navCmd.value)
            {
            case NavigationCommands::Up:
                handled = TrySelectPreviousLine();
                break;
            case NavigationCommands::Down:
                handled = TrySelectNextLine();
                break;
            case NavigationCommands::Exit:
                handled = TryUnselectCurrentControl();
                break;
            default:
                break;
            }

            if (handled) { return true; }

            // Skip VerticalPanel because we reimplemented line navigation (up/down) here.
            handled = PanelControlContainer<MaxLines>::OnNavigationCommand(navCmd);
            return handled;
        }

        /** Overridden to implement the typePage type flag.
         *  \param type indicates the requested type.
         *  \return Returns true if the type flag matches the class hierarchy.
         */
        bool IsOfType(ControlTypes type) const override
        {
            return type.HasFlag(ControlTypes::Page) || BaseT::IsOfType(type);
        }

        /** Un-selects the current focused control (if any).
         *  \return Returns true if the current control was unselected.
         */
        bool TryUnselectCurrentControl()
        {
            InputControl* currentCtrl = getCurrentInputControl();

            if (currentCtrl != nullptr &&
                currentCtrl->getIsFocussed())
            {
                BaseT::setCurrentControl(nullptr);
                return true;
            }

            return false;
        }

        /** Selects the next line -or the first if no current line is set- if no Control is currently selected.
         *  \return Returns true if successful.
         */
        bool TrySelectNextLine()
        {
            InputControl* currentCtrl = getCurrentInputControl();

            if (currentCtrl == nullptr ||
                (currentCtrl != nullptr && !currentCtrl->getIsSelected()))
            {
                if (BaseT::SetNextInputControl())
                {
                    TryFocusFirstControl();
                    return true;
                }
            }

            return false;
        }

        /** Selects the previous line -or the last if no current line is set- if no Control is currently selected.
         *  \return Returns true if successful.
         */
        bool TrySelectPreviousLine()
        {
            InputControl* currentCtrl = getCurrentInputControl();

            if (currentCtrl == nullptr ||
                (currentCtrl != nullptr && !currentCtrl->getIsSelected()))
            {
                if (BaseT::SetPreviousInputControl())
                {
                    TryFocusFirstControl();
                    return true;
                }
            }

            return false;
        }

        /** Retrieves the current line.
         *  \return Returns NULL if no current line is available.
         */
        inline Panel* getCurrentLine() const
        {
            return (Panel*)BaseT::getCurrentControl();
        }

        /** Retrieves the Control on the current line that is focused or selected.
         *  \return Returns NULL if no current line or current control is available.
         */
        InputControl* getCurrentInputControl() const
        {
            Panel* currentLine = getCurrentLine();

            if (currentLine != nullptr)
            {
                return currentLine->getCurrentControl();
            }

            return nullptr;
        }

    protected:
        /** Implements displaying the cursor.
         *  Calls `Display()` on the current control on the current line with `ControlDisplayMode::Cursor`
         *  or turns the cursor of if no current control is available.
         *  \param output is used to set the cursor position.
         */
        inline void DisplayCursor(DisplayWriter* output)
        {
            InputControl* ctrl = getCurrentInputControl();

            if (ctrl != nullptr &&
                ctrl->getIsActive())
            {
                Panel* line = getCurrentLine();
                output->EnableCursor(line->getPosition(), ctrl->getPosition(), ctrl->getIsSelected());

                ctrl->Display(output, ControlDisplayMode::Cursor);
            }
            else
            {
                // cursor off
                output->EnableCursor(DisplayWriter::CurrentPos, DisplayWriter::CurrentPos, false);
            }
        }

        /** Focuses the first control of the current line if no current control is set.
         *  \return Returns true if the control state was changed.
         */
        inline bool TryFocusFirstControl()
        {
            Panel* line = getCurrentLine();

            if (line != nullptr &&
                line->getCurrentControl() == nullptr)
            {
                // there is no other way to access the control collection
                return line->OnNavigationCommand(NavigationCommands::Right);
            }

            return false;
        }

    };

} // ATL

#endif //__PAGE_H__