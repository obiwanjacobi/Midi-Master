# MIDI Master UI

Control Class Hierarchy:

- Control
    - LabelControl
    - InputControl (+NavigationController)
        - UpDownControl
            - EditControl
                - TextControl
                - `NameTextControl`
            - `PatchSelectControl`
            - `MapEntrySelectControl`
        - Panel
            - PanelControlContainer (+ControlContainer)
                - HorizontalPanel
                    - Line
                        - `RealtimeLine1/2`
                        - `EditOutputMapLine1/2`
                - VerticalPanel
                    - Page
                        - `RealtimePage`
                        - `EditOutputMapPage`
                - PageController
                    - `PageManager`
        - `MidiOutNavigationControl`
    - `MidiInNoteControl`
