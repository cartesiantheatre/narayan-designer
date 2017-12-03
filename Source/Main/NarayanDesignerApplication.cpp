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

    // Giomm...
    #include <giomm/application.h>
    #include <giomm/menumodel.h>

    // Standard C++ / POSIX system headers...
    #include <cassert>
    #include <iostream>
    #include <memory>
    #include <stdexcept>
    #include <string>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Protected constructor...
NarayanDesignerApplication::NarayanDesignerApplication()
    : Gtk::Application("com.cartesiantheatre.narayan-designer", Gio::ApplicationFlags::APPLICATION_HANDLES_OPEN),
      m_ApplicationMenu(nullptr),
      m_Builder(Gtk::Builder::create()),
      m_MainWindow(nullptr)
{
    // Try to load Glade resources that were compiled into us. This can throw an
    //  exception for Glib FileError, MarkupError, or BuilderError...
    m_Builder->add_from_resource("/com/cartesiantheatre/narayan-designer/MainWindow.ui");
    m_Builder->add_from_resource("/com/cartesiantheatre/narayan-designer/Menus.ui");

    // Get the main window...
    m_Builder->get_widget_derived("MainWindow", m_MainWindow);
    assert(m_MainWindow);

    // Get the application menu...
    m_ApplicationMenu = Glib::RefPtr<Gio::MenuModel>::cast_dynamic(
        m_Builder->get_object("ApplicationMenu"));
    assert(m_ApplicationMenu);
}

// Public static class instantiation method...
Glib::RefPtr<NarayanDesignerApplication> NarayanDesignerApplication::create()
{
    // Construct object using protected default constructor...
    return Glib::RefPtr<NarayanDesignerApplication>(new NarayanDesignerApplication());
}

// Override the signal_startup() signal which is emitted on the primary instance
//  immediately after registration...
void NarayanDesignerApplication::on_startup()
{
    // Call the base class's implementation...
    Gtk::Application::on_startup();

    // Add actions...
    add_action("action_preferences", sigc::mem_fun(*this, &NarayanDesignerApplication::OnActionPreferences));
    add_action("action_quit", sigc::mem_fun(*this, &NarayanDesignerApplication::OnActionQuit));

    // Set keyboard accelerators for the application menu...
    set_accel_for_action("action_quit", "<Ctrl>Q");

    // Set the application menu...
    set_app_menu(m_ApplicationMenu);
}

// Override the signal_activate() signal which is emitted when the application
//  is activated...
void NarayanDesignerApplication::on_activate()
{
    // Keep the application running for as long as the main window is open and
    //  connect a signal handler to signal_hide() which removes it when
    //  hidden, but doesn't delete it...
    add_window(*m_MainWindow);
    
    // Delete the main window when it is hidden...
    m_MainWindow->signal_hide().connect(sigc::bind(sigc::mem_fun(*this,
       &NarayanDesignerApplication::OnHideWindow), m_MainWindow));

    // Bring the main window to the forefront...
    m_MainWindow->present();
}
       
// Main window is now hidden...
void NarayanDesignerApplication::OnHideWindow([[maybe_unused]] Gtk::Window *Window)
{
    // Delete it...
    delete m_MainWindow;
    m_MainWindow = nullptr;
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
    // Hide all windows to ensure their destructors are called. Otherwise
    //  simply calling Gio::Application::quit() will cause
    //  Gio::Application::run() to return, but without calling destructors
    //  because any open windows will still have non-zero reference counts...
    auto Windows = get_windows();
    for(auto CurrentWindow : Windows)
        CurrentWindow->hide();

    // This technically isn't necessary since run() should return anyways when
    //  all windows are hidden, unless something called Gio::Application::hold()
    //  without a corresponding call to Gio::Application::release()...
    quit();
}

