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
    
    // Gtkmm...
    #include <gtkmm/expander.h>
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
    BaseObjectType *CTypeObject, const Glib::RefPtr<Gtk::Builder> &Builder)
 :  Gtk::ApplicationWindow(CTypeObject),
    m_Builder(Builder)
{
    /* Get widgets...
    m_Builder->get_widget("QuitButton", m_QuitButton);

    // Connect signals...
    m_QuitButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnButtonQuit));*/
    
    // Set the window icon...
    set_icon(Gdk::Pixbuf::create_from_resource(
        NARAYAN_DESIGNER_RESOURCE_ROOT
        "Icons/48x48/com.cartesiantheatre.narayan-designer.png"));

    // Populate ActionMap using add_action() because our Gtk::ApplicationWindow
    //  derives from Gio::ActionMap...

        // Show log...
        add_action("show-log",
            sigc::mem_fun(*this, &MainWindow::OnActionShowLog));
}

// Action to show the log...
void MainWindow::OnActionShowLog()
{
    // Get the application log expander widget...
    auto LogExpander = Glib::RefPtr<Gtk::Expander>::cast_dynamic(m_Builder->get_object("LogExpander"));
    g_assert(LogExpander);
    
    // Toggle / untoggle...
    LogExpander->set_expanded(!LogExpander->get_expanded());
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

