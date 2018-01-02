/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanDesignerApplication.h"
    #include "MainWindow.h"
    #include "Resources.h"

    // Giomm...
    #include <giomm/application.h>
    #include <giomm/menumodel.h>
    
    // Glibmm...
    #include <glibmm/miscutils.h>

    // Standard C++ / POSIX system headers...
    #include <cassert>
    #include <iostream>
    #include <memory>
    #include <stdexcept>
    #include <sstream>
    #include <string>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Protected constructor...
NarayanDesignerApplication::NarayanDesignerApplication()
    : Gtk::Application(
        NARAYAN_DESIGNER_APPLICATION_ID, 
          Gio::ApplicationFlags::APPLICATION_HANDLES_OPEN |
          Gio::ApplicationFlags::APPLICATION_HANDLES_COMMAND_LINE |
          Gio::ApplicationFlags::APPLICATION_NON_UNIQUE),
      m_ApplicationMenu(nullptr),
      m_Builder(Gtk::Builder::create()),
      m_MainWindow(nullptr)
{
    // Set the application name...
    Glib::set_application_name(_("Narayan Designer"));

    // Connect command line handler signal...
    signal_command_line().connect(
        sigc::mem_fun(*this, &NarayanDesignerApplication::on_command_line));

    // Try to load Glade resources that were compiled into us. This can throw an
    //  exception for Glib FileError, MarkupError, or BuilderError...
    try
    {
        // Load main window...
        m_Builder->add_from_resource(NARAYAN_DESIGNER_RESOURCE_ROOT "MainWindow.ui");

        /* Load app-menu for desktop environments that support it... */

        // Application menu with id="menubar" is automatically loaded and set as
        //  a menubar in the traditional sense...
        m_Builder->add_from_resource(NARAYAN_DESIGNER_RESOURCE_ROOT "Menus.ui");
    }

        // Failed...
        catch(const Glib::Error &Exception)
        {
            // Format error message...
            stringstream ErrorMessage;
            ErrorMessage
                << _("Error: Gtk::Builder cannot add resource: ")
                << Exception.what();
            
            // Propagate exception up the chain...
            throw std::runtime_error(ErrorMessage.str());
        }

    // Get the main window...
    m_Builder->get_widget_derived("MainWindow", m_MainWindow);
    assert(m_MainWindow);

    // Get the application menu...
    m_ApplicationMenu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(m_Builder->get_object("menubar"));
//    m_ApplicationMenu = get_menubar();
    assert(m_ApplicationMenu);
    
    // Prepare command line parser...
//    add_main_option_entry
}

// Public static class instantiation method...
Glib::RefPtr<NarayanDesignerApplication> NarayanDesignerApplication::create()
{
    // Construct object using protected default constructor...
    return Glib::RefPtr<NarayanDesignerApplication>(
        new NarayanDesignerApplication());
}

// Override the signal_startup() signal which is emitted on the primary instance
//  immediately after registration. Perform various initialisation tasks not
//  directly related to showing a new window...
void NarayanDesignerApplication::on_startup()
{
    // Call the base class's implementation...
    Gtk::Application::on_startup();

    // Populate ActionMap using add_action() because our Gtk::Application
    //  derives from Gio::ActionMap...

        // Preferences...
        add_action("preferences",
            sigc::mem_fun(*this, &NarayanDesignerApplication::OnActionPreferences));
        
        // Quit...
        add_action("quit", 
            sigc::mem_fun(*this, &NarayanDesignerApplication::OnActionQuit));

    // Set keyboard accelerators which may be displayed in the application's
    //  menu, depending on the desktop environment...

        // Quit...
        set_accel_for_action("app.quit", "<Ctrl>q");

    /* Set the application menu...
    if(prefers_app_menu())
        cout << "Prefers app menu!" << endl;
    else
        cout << "Does not prefer app menu!" << endl;*/

//    set_app_menu(m_ApplicationMenu);

    set_menubar(m_ApplicationMenu);
    assert(get_menubar());
}

// Override the signal_activate() signal which is emitted when the application
//  is activated. Called after startup signal. Typically used to show the
//  default first window of the application. Corresponds to the application
//  being launched by the desktop environment...
void NarayanDesignerApplication::on_activate()
{
    // Keep the application running for as long as the main window is open and
    //  connect a signal handler to signal_hide() which removes it when
    //  hidden, but doesn't delete it...
    add_window(*m_MainWindow);
    
    // Delete the main window when it is hidden...
    m_MainWindow->signal_hide().connect(sigc::bind(sigc::mem_fun(*this,
       &NarayanDesignerApplication::on_hide), m_MainWindow));

    // Bring the main window to the forefront...
    m_MainWindow->present();
}

// Actions to open the preferences dialog...
void NarayanDesignerApplication::OnActionPreferences()
{
    // TODO: Implement this...
    cout << __PRETTY_FUNCTION__ << endl;
}

// Action to quit the application...
void NarayanDesignerApplication::OnActionQuit()
{
    // Get the list of all windows...
    auto Windows = get_windows();
    
    // Hide all of the windows to ensure their destructors are called.
    //  Otherwise simply calling Gio::Application::quit() will cause 
    //  Gio::Application::run() to return, but without calling destructors
    //  because any open windows will still have non-zero reference counts...
    for(auto CurrentWindow : Windows)
    {
        // If it is the main window, try to request it close it self first since
        //  it may need to prompt the user to save changes...
        if(CurrentWindow == m_MainWindow)
            CurrentWindow->close();
        
        // All other windows hide them...
        else
            CurrentWindow->hide();
    }

    // This technically isn't necessary since run() should return anyways when
    //  all windows are hidden, unless something called Gio::Application::hold()
    //  without a corresponding call to Gio::Application::release()...
//    quit();
}

// Command line signal...
int NarayanDesignerApplication::on_command_line([[maybe_unused]] const Glib::RefPtr<Gio::ApplicationCommandLine> &CommandLine)
{
    // Stubbed...
    return false;
}

// Main window is now hidden...
void NarayanDesignerApplication::on_hide([[maybe_unused]] Gtk::Window *Window)
{
    // Delete it...
    delete m_MainWindow;
    m_MainWindow = nullptr;
}

