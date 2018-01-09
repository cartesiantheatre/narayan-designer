/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _PREFERENCES_DIALOG_H_
#define _PREFERENCES_DIALOG_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanDesignerApplication.h"

    // Gtkmm...
    #include <gtkmm/builder.h>
    #include <gtkmm/button.h>
    #include <gtkmm/checkbutton.h>
    #include <gtkmm/dialog.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Preferences dialog...
class PreferencesDialog : public Gtk::Dialog
{
    // Public methods...
    public:
    
        // Constructor around Glade's already instantiated dialog...
        PreferencesDialog(
            BaseObjectType *CTypeObject,
            const Glib::RefPtr<Gtk::Builder> &Builder,
            Glib::RefPtr<Gio::Settings> &Settings);

    // Protected methods...
    protected:

        // Signals...

            // Overridden defaults...
        
                // Window is being closed...
                bool on_delete_event(GdkEventAny *Event) override;
            
            // Manually registered...
                
                // Close button clicked...
                void OnCloseButton();

    // Protected attributes...
    protected:

        // Builder...
        Glib::RefPtr<Gtk::Builder>          m_Builder;

        // Settings
        
            // Backend...
            Glib::RefPtr<Gio::Settings>     m_Settings;

            // Bound widgets...

                // Show splash check button...
                Gtk::CheckButton           *m_CheckButton_ShowSplash;

                // Close button...
                Gtk::Button                *m_Button_Close;
};

// Multiple include protection...
#endif

