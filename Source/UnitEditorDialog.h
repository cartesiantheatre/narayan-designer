/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _UNIT_EDITOR_DIALOG_H_
#define _UNIT_EDITOR_DIALOG_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Gtkmm...
    #include <gtkmm/builder.h>
    #include <gtkmm/button.h>
    #include <gtkmm/dialog.h>

// Unit editor dialog...
class UnitEditorDialog : public Gtk::Dialog
{
    // Public methods...
    public:
    
        // Constructor around Glade's already instantiated dialog...
        UnitEditorDialog(
            BaseObjectType *CTypeObject,
            const Glib::RefPtr<Gtk::Builder> &Builder);

    // Protected methods...
    protected:

        // Signals...

            // Manually registered...

                // Close button clicked...
                void OnClose();

    // Protected attributes, classes, and enumerated types...
    protected:

        // Builder...
        Glib::RefPtr<Gtk::Builder>                  m_Builder;

        // Widgets...
        Gtk::Button                                *m_Button_Close;
};

// Multiple include protection...
#endif

