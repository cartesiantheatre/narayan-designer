/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "MainWindow.h"

    // Standard C++ / POSIX system headers...
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
    m_Builder(Builder),
    m_QuitButton(nullptr)
{
    // Get widgets...
    m_Builder->get_widget("quit_button", m_QuitButton);
    
    // Connect signals...
    m_QuitButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnButtonQuit));
}

// Signal handlers...
void MainWindow::OnButtonQuit()
{
    // Hide the window which will cause Gtk::Application::run() to break its
    //  main loop...
    hide();
}

// Deconstructor...
MainWindow::~MainWindow()
{

}

