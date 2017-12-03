/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _NARAYAN_DESIGNER_APPLICATION_H_
#define _NARAYAN_DESIGNER_APPLICATION_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Gtkmm...
    #include <gtkmm/application.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Forward declarations...
class MainWindow;

// Narayan Designer main application class...
class NarayanDesignerApplication : public Gtk::Application
{
    // Public methods...
    public:
    
        // Public static class instantiation method...
        static Glib::RefPtr<NarayanDesignerApplication> create();

    // Protected methods...
    protected:
        
        // Protected constructor...
        NarayanDesignerApplication();

        // Override default signal handlers...
        void on_startup() override;
        void on_activate() override;

    // Protected attributes...
    protected:

        // Gtk::Builder...
        Glib::RefPtr<Gtk::Builder>  m_Builder;

        // Main window...
        MainWindow                  m_MainWindow;

    // Private methods...
    private:
    
        // Signal handler callbacks...
        
            // Window is being hidden...
            void OnHideWindow(Gtk::Window *Window);
            
            // Actions...
            void OnActionPreferences();
            void OnActionQuit();
};

// Multiple include protection...
#endif

