/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Giomm...
    #include <giomm/settings.h>

    // Gtkmm...
    #include <gtkmm/applicationwindow.h>
    #include <gtkmm/builder.h>
    #include <gtkmm/expander.h>
    #include <gtkmm/notebook.h>
    #include <gtkmm/stack.h>
    #include <gtkmm/toolpalette.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Forward declarations...
class PreferencesDialog;
class UnitEditorDialog;

// Main window...
class MainWindow : public Gtk::ApplicationWindow
{
    // Public methods...
    public:
    
        // Constructor around already Glade instantiated window...
        MainWindow(
            BaseObjectType *CTypeObject,
            const Glib::RefPtr<Gtk::Builder> &Builder,
            Glib::RefPtr<Gio::Settings> &Settings);

        // Deconstructor...
        virtual ~MainWindow();

    // Protected methods...
    protected:
        
        // Signals...

            // Overridden defaults...
        
                // Window is being closed...
                bool on_delete_event(GdkEventAny *Event) override;

            // Manually registered...

                // Actions...
    
                    // Open a simulation model...
                    void OnActionOpen();
                    
                    // Toggle the log's visibility...
                    void OnActionShowLog();
                    
                    // Open the unit editor dialog...
                    void OnActionUnitEditor();
                    
                    // Report a bug...
                    void OnActionReportBug();

    // Protected attributes...
    protected:

        // Gtk::Builder...
        Glib::RefPtr<Gtk::Builder>  m_Builder;
        
        // Settings backend...
        Glib::RefPtr<Gio::Settings> m_Settings;
        
        // Widgets...
            
            // Tool palette...
            Gtk::ToolPalette       *m_ToolPalette;
            
            // Stack containing welcome, work space, and error pages...
            Gtk::Stack             *m_Stack;
            
            // Documents notebook...
            Gtk::Notebook          *m_Notebook_Documents;

            // Welcome logo...
            Gtk::Image             *m_Image_Welcome;
            
            // Error image...
            Gtk::Image             *m_Image_Error;

            // Log expander...
            Gtk::Expander          *m_Expander_Log;
        
        // Dialogs...
        PreferencesDialog          *m_Dialog_Preferences;
        UnitEditorDialog           *m_Dialog_UnitEditor;
};

// Multiple include protection...
#endif

