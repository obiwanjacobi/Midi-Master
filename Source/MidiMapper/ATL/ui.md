# ATL UI

Control Types:

- Control. A basic control without user interaction.
- Input. The control receives input from user interaction and can be focussed and/or selected.
- Panel. A container for multiple controls. Usually performs layout and keeps track of current selected control.
- Page. A complete UI page with multiple lines.

Control States:

- Disabled. control does not receive input but is displayed as read-only.  
- Hidden. The control does not receive input and is not displayed.
- Focussed. The control has the focus and is displayed high-lighted with a cursor. Only one control has focus at a time.
- Selected. The control is displayed with an edit cursor. Only one control can be selected at a time.

Control Class Hierarchy:

- `Control`
    - `LabelControl`
    - `InputControl` (+`NavigationController`)
        - `UpDownControl`
            - `EditControl`
                - `TextControl`
        - `Panel`
            - `PanelControlContainer` (+`ControlContainer`)
                - `HorizontalPanel`
                    - `Line`
                - `VerticalPanel`
                    - `Page`
                - `PageController`

A typical LCD Page layout (2 lines):

- `Page: VerticalPanel: PanelControlContainer: Panel: InputControl: Control`
	- `Line: HorizonatalPanel: PanelControlContainer: Panel: InputControl: Control`
		- `LabelControl`
		- `TextControl: EditControl: UpDownControl: InputControl: Control`
	- `Line: HorizonatalPanel: PanelControlContainer: Panel: InputControl: Control`
		- `LabelControl`
		- `TextControl: EditControl: UpDownControl: InputControl: Control`

## `Control` (class)

A base class for all controls.

- Position. Position of the control inside its container.
- State. Disabled/Focussed/Selected. Manages state changes.
- DynamicCast/IsType. Lightweight type information.
- Display. Called to draw the control.

## `ControlContainer` (template)

Fixed-size collection of 'Control' instance pointers.

Allows adding and iteration (next/previous) of control pointers.

## `DisplayWriter` (class)

An abstraction to decouple drawing controls and UI in general onto any display.

- Display. Draw text.
- GoTo. Move current drawing position.
- EnableCursor. Display cursor (two types)

## `EditControl` extends `UpDownControl` (class)

Implements text editing in a control using a character provider (iterator).

## `HorizontalPanel` extends `PanelControlContainer` (template)

A control container that lays out the control horizontally.

## `InputControl` extends `Control` and `NavigationController` (class)

A base class for all controls that use the `NavigationCommands` to allow editing their content.

## `LabelControl` extends `Control` (class)

A read-only display text for labelling other controls.

## `Line` extends `HorizontalPanel` (template)

A fixed-size control container for laying out a single display line.

## `NavigationControler` (class)

Interface for acting on navigation commands as they are routed through the control tree.

## `Page` extends `VerticalPanel` (template)

A fixed-sized `Line` containter for laying out an entire display page.

## `PageController` extends `PanelControlContainer` (template)

A fixed-size container of pages that manages page transitions.

## `Panel` extends `InputControl` (class)

Keeps track of the current active `InputControl`.

## `PanelControlContainer` extends `Panel` and `ControlContainer` (template)

A fixed-size container base class for managing multiple `InputControl`s.

## `TextControl` extends `EditControl` (template)

Manages editing a fixes-size string.

## `UpDownControl` extends `InputControl` (template)

Manages changing a value with the Up/Down navigation Commands.

## `VerticalPanel` extends `PanelControlContainer` (template)

A fixed-size control panel that are layed out vertically.
