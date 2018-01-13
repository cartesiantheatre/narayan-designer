/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanDesignerApplication.h"
    #include "MainWindow.h"
    #include "PreferencesDialog.h"
    #include "Resources.h"

    // Giomm...
    #include <giomm/application.h>
    #include <giomm/menumodel.h>
    
    // Glibmm...
    #include <glibmm/miscutils.h>
    #include <glibmm/optioncontext.h>
    #include <glibmm/optionentry.h>
    #include <glibmm/optiongroup.h>

    // Standard C++ / POSIX system headers...
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
      m_MainWindow(nullptr),
      m_PreferencesDialog(nullptr),
      m_Settings(nullptr)
{
    // Set the application name...
    Glib::set_application_name(_("Narayan Designer"));

    // Connect command line handler signal with after=false because we want it
    //  to be called before the default signal handler...
    signal_command_line().connect(
        sigc::mem_fun(*this, &NarayanDesignerApplication::on_command_line), false);

    // Initialize GSettings backend...

        // This environment variable can be set to the name of a directory that
        //  is considered in addition to the glib-2.0/schemas subdirectories of
        //  the XDG system data dirs when looking for the compiled schema for
        //  GSettings. Since we may be running our binary from a location other
        //  than where it was configured, not setting this would lead to
        //  GLib-GIO throwing an exception because it wouldn't be able to find
        //  gschemas.compiled. Note that the third parameter here is set to
        //  false to ensure this call is ignored if the environment variable was
        //  already set, such as by the user on the command line or during a
        //  Makefile.am unit test...
        Glib::setenv("GSETTINGS_SCHEMA_DIR", "Data/", false);

        // Allocate backend...
        m_Settings = Gio::Settings::create(NARAYAN_DESIGNER_APPLICATION_ID);

        // Documentation isn't totally clear on how all errors are handled so
        //  verify it at least allocated...
        g_assert(m_Settings);

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
        
        // Load the preferences dialog...
        m_Builder->add_from_resource(NARAYAN_DESIGNER_RESOURCE_ROOT "PreferencesDialog.ui");
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
    m_Builder->get_widget_derived("MainWindow", m_MainWindow, m_Settings);
    g_assert(m_MainWindow);
    
    // Get the preferences dialog...
    m_Builder->get_widget_derived("PreferencesDialog", m_PreferencesDialog, m_Settings);
    g_assert(m_PreferencesDialog);

    // Get the application menu...
    m_ApplicationMenu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(m_Builder->get_object("menubar"));
//    m_ApplicationMenu = get_menubar();
    g_assert(m_ApplicationMenu);
    
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

    // Set the menu bar and verify it was set...
    set_menubar(m_ApplicationMenu);
    g_assert(get_menubar());
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
    // Tell window manager to put dialog centred over main window and always
    //  above it...
    m_PreferencesDialog->set_transient_for(*m_MainWindow);
    
    // Show it...
    m_PreferencesDialog->present();
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
int NarayanDesignerApplication::on_command_line(
    const Glib::RefPtr<Gio::ApplicationCommandLine> &CommandLine)
{
    // Option variable command line parser will initialize...
    bool DisplayVersion = false;

    // Create option parser...
    Glib::OptionContext Parser;

    // Main options group...
        
        // Create group...
        Glib::OptionGroup MainGroup("main", _("main group"));

        // Version...
        Glib::OptionEntry VersionEntry;
        VersionEntry.set_long_name("version");
        VersionEntry.set_description(_("show version information"));
        MainGroup.add_entry(VersionEntry, DisplayVersion);

    // Add groups to parser...
    
        // Main group. Note that set_main_group() also has the effect of calling
        //  add_group()...
        Parser.set_main_group(MainGroup);
    
        // Gtk+ and GDK option groups...
        Glib::OptionGroup GtkGroup(gtk_get_option_group(true));
        Parser.add_group(GtkGroup);

    // Retrieve command line vector...
    int     ArgumentCount   = 0;
    char  **Arguments       = CommandLine->get_arguments(ArgumentCount);

    // Parse the given command line options...
    Parser.parse(ArgumentCount, Arguments);

    // Show version requested...
    if(DisplayVersion)
    {
        // Display it...
        ShowVersion();
        
        // Don't activate the application...
        return EXIT_SUCCESS;
    }

    // Now activate the application...
    activate();

    // Everything was just peachy...
    return EXIT_SUCCESS;
}

// Main window is now hidden...
void NarayanDesignerApplication::on_hide([[maybe_unused]] Gtk::Window *Window)
{
    // Delete it...
    delete m_MainWindow;
    m_MainWindow = nullptr;
}

// Show version information...
void NarayanDesignerApplication::ShowVersion() noexcept
{
    // Application name and vendor copyright notice...
    cout << PACKAGE_NAME " " PACKAGE_VERSION << endl
         << _(COPYRIGHT_NOTICE) << endl << endl;

    // Show build date...
    cout << _("Built on: ") << PACKAGE_BUILD_DATE << endl << endl;

    // Relevant dependencies...
    cout << _("Compiled against:") << endl

         <<  "  Gtkmm "
            << GTKMM_MAJOR_VERSION << "."
            << GTKMM_MINOR_VERSION << "."
            << GTKMM_MICRO_VERSION << endl << endl;

    // Show full argument vector passed to configure before building...
    cout << _("Configured with: ") << CONFIGURATION_FLAGS << endl;
}

