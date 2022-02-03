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

#ifndef __PANEL_H__
#define __PANEL_H__

#include <stddef.h>
#include <stdint.h>
#include "ControlContainer.h"
#include "Control.h"
#include "InputControl.h"

namespace ATL {

    /** The Panel abstract class maintains a reference to the current control.
     */
    class Panel : public InputControl
    {
    public:
        /** Retrieves the current control.
         *  \return Returns NULL if no current control is set.
         */
        inline InputControl* getCurrentControl() const
        {
            return _currentControl;
        }

        /** A predicate callback function to test InputControls.
         * \param currentControl is the control to be tested.
         * \param callerState is a (pointer to a) caller defined state object.
         * \return Returns true if the currentControl matches the predicate.
         */
        typedef bool (*ControlPredicate)(const InputControl* currentControl, void* callerState);

        /** Retrieves the current control that passes the predicate.
         * If the predicate returns false, the current control cast to a Panel and if successful
         * that panel is asked for its current control, drilling into a panel hierarchy until the predicate returns true.
         * \param predicate is a callback function to determine what currentControl to return. If NULL the return value is simply the currentControl.
         * \param callerState is a caller defined state object that is passed to the predicate when called. Can be used as a this pointer.
         * \return Returns the currentControl that passed the predicate or NULL if none was matched or no currentControl was set.
         */
        inline InputControl* getCurrentControl(ControlPredicate predicate, void* callerState = nullptr) const
        {
            if (_currentControl != nullptr && predicate != nullptr && 
                !predicate(_currentControl, callerState))
            {
                Panel* panel = (Panel*)_currentControl->DynamicCast(ControlTypes::Panel);
                if (panel != nullptr)
                    return panel->getCurrentControl(predicate);
                    
                return nullptr;
            }

            return _currentControl;
        }

        /** Assigns ctrl to the current control.
         *  The old current control (if any) will be set to `Normal`.
         *  The new current control (ctrl - if not NULL) will be set to `Focused`.
         *  The state of the Panel will reflect the state of the current control.
         *  \param ctrl is the control make current. Can be NULL.
         */
        inline void setCurrentControl(InputControl* ctrl)
        {
            if (_currentControl != nullptr)
            {
                _currentControl->setState(ControlState::Normal);
                setState(ControlState::Normal);
            }

            _currentControl = ctrl;

            if (_currentControl != nullptr)
            {
                _currentControl->setState(ControlState::Focused);
                setState(ControlState::Focused);
            }
        }

        /** Forwards the call unchanged to the current control (if any).
         *  \param output is used to output text and set the cursor position.
         *  \param mode indicates what is to be displayed.
         */
        void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal) override
        {
            if (_currentControl != nullptr)
            {
                _currentControl->Display(output, mode);
            }
        }

        /** Forwards the call unchanged to the current control (if any).
         *  \param navCmd is the navigation command.
         */
        bool OnNavigationCommand(NavigationCommands navCmd) override
        {
            if (_currentControl != nullptr)
            {
                return _currentControl->OnNavigationCommand(navCmd);
            }

            return false;
        }

        /** Overridden to respond to the `Panel` type.
         *  \param type the requested type.
         *  \return Returns true if the type is part of the class hierarchy.
         */
        bool IsOfType(ControlTypes type) const override
        {
            return type.HasFlag(ControlTypes::Panel) || InputControl::IsOfType(type);
        }

    protected:
        /** For derived classes.
         *  \param pos is the optional control position.
         */
        Panel(uint8_t pos = 0)
            : InputControl(pos), _currentControl(nullptr)
        { }

        /** Overridden to disallow `Selected`
         *  \param newState is the proposed state.
         *  \return Returns true if the state change may occur.
         */
        bool BeforeChangeState(ControlState newState) override
        {
            return newState != ControlState::Selected && 
                   InputControl::BeforeChangeState(newState);
        }

    private:
        InputControl* _currentControl;
    };


} // ATL

#endif //__PANEL_H__