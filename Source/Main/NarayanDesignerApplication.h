/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _NARAYAN_DESIGNER_APPLICATION_H_
#define _NARAYAN_DESIGNER_APPLICATION_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Giomm...
    #include <giomm/applicationcommandline.h>
    #include <giomm/settings.h>

    // Gtkmm...
    #include <gtkmm/application.h>
    #include <gtkmm/builder.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Useful definitions...

    // Application unique identifier...
    #define NARAYAN_DESIGNER_APPLICATION_ID "com.cartesiantheatre.narayan-designer"
    
    // Root path to all embedded resources accessible via GResource API...
    #define NARAYAN_DESIGNER_RESOURCE_ROOT  "/com/cartesiantheatre/narayan-designer/"

// Forward declarations...
class MainWindow;
class PreferencesDialog;

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

        // Signals...

            // Overridden defaults...

                // Override the signal_startup() signal which is emitted on the
                //  primary instance immediately after registration. Perform various
                //  initialisation tasks not directly related to showing a new
                //  window...
                void on_startup() override;

                // Override the signal_activate() signal which is emitted when the
                //  application is activated. Called after startup signal. Typically
                //  used to show the default first window of the application.
                //  Corresponds to the application being launched by the desktop
                //  environment...
                void on_activate() override;

            // Manually registered...

                // Command line signal...
                int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine> &CommandLine);

                // Window is being hidden...
                void on_hide(Gtk::Window *Window);
                
                // Actions...
                void OnActionPreferences();
                void OnActionQuit();

        // Show version information...
        void ShowVersion() noexcept;

    // Protected attributes...
    protected:

        // Application menu...
        Glib::RefPtr<Gio::MenuModel>    m_ApplicationMenu;

        // Builder...
        Glib::RefPtr<Gtk::Builder>      m_Builder;

        // Main window...
        MainWindow                     *m_MainWindow;
        
        // Preferences dialog...
        PreferencesDialog              *m_PreferencesDialog;
        
        // Settings backend...
        Glib::RefPtr<Gio::Settings>     m_Settings;
};

// Multiple include protection...
#endif

