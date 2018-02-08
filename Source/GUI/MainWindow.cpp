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

    // Gdkmm...
    #include <gdkmm/pixbuf.h>

    // Giomm...
    #include <giomm/appinfo.h>

    // Gtkmm...
    #include <gtkmm/messagedialog.h>

    // Standard C++ / POSIX system headers...
    #include <iostream>
    #include <string>
    #include <stdexcept>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Constructor around already Glade instantiated window...
MainWindow::MainWindow(
    BaseObjectType *CTypeObject,
    const Glib::RefPtr<Gtk::Builder> &Builder,
    Glib::RefPtr<Gio::Settings> &Settings)
 :  Gtk::ApplicationWindow(CTypeObject),
    m_Builder(Builder),
    m_Settings(Settings),
    m_Notebook_Documents(nullptr),
    m_Expander_Log(nullptr)
{
    // Set the window icon...
    set_icon(Gdk::Pixbuf::create_from_resource(
        NARAYAN_DESIGNER_RESOURCE_ROOT
        "icons/48x48/apps/com.cartesiantheatre.narayan-designer.png"));

    // Find widgets...
        
        // Documents notebook...
        m_Builder->get_widget("Notebook_Documents", m_Notebook_Documents);
        g_assert(m_Notebook_Documents);
        
        // Log expander...
        m_Builder->get_widget("Expander_Log", m_Expander_Log);
        g_assert(m_Expander_Log);

    // Populate ActionMap using add_action() because our Gtk::ApplicationWindow
    //  derives from Gio::ActionMap...

        // Show log...
        add_action("show-log",
            sigc::mem_fun(*this, &MainWindow::OnActionShowLog));

        // Report a bug...
        add_action("report-bug",
            sigc::mem_fun(*this, &MainWindow::OnActionReportBug));
    
    // Initialize documents notebook...
    m_Notebook_Documents->remove_page(0);

    // Bind settings to relevant widgets...
    m_Settings->bind("show-log", m_Expander_Log->property_expanded());
}

// Action to report a bug...
void MainWindow::OnActionReportBug()
{
    // Open URL...
    Gio::AppInfo::launch_default_for_uri(PACKAGE_BUGREPORT);
}

// Action to show the log...
void MainWindow::OnActionShowLog()
{
    // Toggle / untoggle...
    m_Expander_Log->set_expanded(!m_Expander_Log->get_expanded());
}

// Something or someone is attempting to close the window...
bool MainWindow::on_delete_event([[maybe_unused]] GdkEventAny *Event)
{
    // Hide the main window, but only if no u nsaved-changes...
    // If no unsaved changes, hide the main window...
    /*if()*/
        hide();

    /*else
    {
        // Create modal warning dialog...
        Gtk::MessageDialog WarningDialog(
            *this,                                  // Parent...
            _("Unsaved Changes"),                   // Caption...
            false,                                  // Use markup...
            Gtk::MessageType::MESSAGE_WARNING,      // Message type...
            Gtk::ButtonsType::BUTTONS_OK_CANCEL,    // Button types...
            true);                                  // Modal...

        // Set its secondary text...
        WarningDialog.set_secondary_text(
              _("Your simulation model contains unsaved changes. Would you "
                "like to save your changes before quitting?"));

        // Show it...
        WarningDialog.run();
    }*/
    
    // Allow further propagation of event...
    return true;
}

// Deconstructor...
MainWindow::~MainWindow()
{

}

