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
    #include <gtkmm/fontbutton.h>
    #include <gtkmm/notebook.h>
    #include <gtkmm/treeview.h>

    // Standard C++ / POSIX system headers...
    #include <string>

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

        // Find a widget and bind it to a particular setting...
        template <typename WidgetType>
        void FindAndBindActiveProperty(
            const std::string &WidgetName,
            WidgetType *& WidgetObject,
            const std::string &Key) const;

        // Signals...

            // Overridden defaults...
        
                // Window is being closed...
                bool on_delete_event(GdkEventAny *Event) override;
            
            // Manually registered...
                
                // Close button clicked...
                void OnCloseButton();

                // Colour scheme cursor changed in tree view...
                void OnColourSchemeChanged();

    // Protected attributes and enumerated types...
    protected:

        // Notebook tab ordinals...
        enum
        {
            Tab_General,
            Tab_Editor,
            Tab_Hardware
        };

        // Builder...
        Glib::RefPtr<Gtk::Builder>          m_Builder;

        // Settings

            // Preferences notebook...
            Gtk::Notebook                  *m_Notebook_Preferences;
        
            // Backend...
            Glib::RefPtr<Gio::Settings>     m_Settings;

            // Bound widgets...

                // General tab...

                    // Show splash check button...
                    Gtk::CheckButton           *m_CheckButton_General_ShowSplash;
                
                // Editor tab...
                    
                    // Use system monospace font...
                    Gtk::CheckButton           *m_CheckButton_Editor_UseSystemDefaultMonospaceFont;
                    
                    // Custom font to use...
                    Gtk::FontButton            *m_FontButton_Editor_CustomFont;
                    
                    // Use dark theme variant, if available...
                    Gtk::CheckButton           *m_CheckButton_Editor_UseDarkTheme;
                    
                    // Colour scheme...
                    Gtk::TreeView              *m_TreeView_Editor_ColourScheme;
                
                // Hardware tab...

                // Help button...
                Gtk::Button                    *m_Button_Help;

                // Close button...
                Gtk::Button                    *m_Button_Close;
};

// Multiple include protection...
#endif

