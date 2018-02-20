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
    #include "UnitEditorDialog.h"

    // Gdkmm...
    #include <gdkmm/pixbuf.h>

    // Giomm...
    #include <giomm/appinfo.h>

    // Gtkmm...
    #include <gtkmm/filechooserdialog.h>
    #include <gtkmm/image.h>
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
    m_ToolPalette(nullptr),
    m_Stack(nullptr),
    m_Notebook_Documents(nullptr),
    m_Image_Welcome(nullptr),
    m_Image_Error(nullptr),
    m_Expander_Log(nullptr),
    m_Dialog_UnitEditor(nullptr)
{
    // Set the window icon...
    set_icon(Gdk::Pixbuf::create_from_resource(
        NARAYAN_DESIGNER_RESOURCE_ROOT
        "icons/48x48/apps/com.cartesiantheatre.narayan-designer.png"));

    // Find widgets and dialogs...

        // Tool palette...
        m_Builder->get_widget("MainWindow_ToolPalette", m_ToolPalette);
        g_assert(m_ToolPalette);

        // Stack containing welcome, work space, and error pages...
        m_Builder->get_widget("MainWindow_Stack", m_Stack);
        g_assert(m_Stack);

        // Documents notebook...
        m_Builder->get_widget("MainWindow_Notebook_Documents", m_Notebook_Documents);
        g_assert(m_Notebook_Documents);

        // Log expander...
        m_Builder->get_widget("MainWindow_Expander_Log", m_Expander_Log);
        g_assert(m_Expander_Log);

        // Welcome image...
        m_Builder->get_widget("MainWindow_Image_Welcome", m_Image_Welcome);
        g_assert(m_Image_Welcome);

        // Error image...
        m_Builder->get_widget("MainWindow_Image_Error", m_Image_Error);
        g_assert(m_Image_Error);

        // Preferences dialog...
        m_Builder->get_widget_derived("PreferencesDialog", m_Dialog_Preferences, m_Settings);
        g_assert(m_Dialog_Preferences);

        // Unit editor dialog...
        m_Builder->get_widget_derived("UnitEditorDialog", m_Dialog_UnitEditor);
        g_assert(m_Dialog_UnitEditor);

    // Populate ActionMap using add_action() because our Gtk::ApplicationWindow
    //  derives from Gio::ActionMap...

        // Open a simulation model...
        add_action("open",
            sigc::mem_fun(*this, &MainWindow::OnActionOpen));

        // Report a bug...
        add_action("report-bug",
            sigc::mem_fun(*this, &MainWindow::OnActionReportBug));

        // Show log...
        add_action("show-log",
            sigc::mem_fun(*this, &MainWindow::OnActionShowLog));

        // Unit editor...
        add_action("editor-units",
            sigc::mem_fun(*this, &MainWindow::OnActionUnitEditor));

    // Load and set images...
        
        // Welcome image...
        Glib::RefPtr<Gdk::Pixbuf> Pixbuf_Welcome = 
            Gdk::Pixbuf::create_from_resource(
                NARAYAN_DESIGNER_RESOURCE_ROOT
                "icons/scalable/apps/com.cartesiantheatre.narayan-designer.svg",
                200, -1, true);
        m_Image_Welcome->set(Pixbuf_Welcome);
        
        // Error image...
        Glib::RefPtr<Gdk::Pixbuf> Pixbuf_Error = 
            Gdk::Pixbuf::create_from_resource(
                NARAYAN_DESIGNER_RESOURCE_ROOT
                "icons/scalable/categories/broken-heart.svg",
                200, -1, true);
        m_Image_Error->set(Pixbuf_Error);

    // Initialize documents notebook...
    m_Notebook_Documents->remove_page(0);

    // Initialize the main stack...
    
        // Set the transition type to cross fade of 200 milliseconds...
        m_Stack->set_transition_type(Gtk::STACK_TRANSITION_TYPE_CROSSFADE);
        m_Stack->set_transition_duration(500);

        // Set the main stack to the welcome page...
        m_Stack->set_visible_child("welcome");

    // Bind settings to relevant widgets...
    m_Settings->bind("show-log", m_Expander_Log->property_expanded());
    
    // Did the preferences dialog's hardware detection find any usable devices?
    if(!m_Dialog_Preferences->IsAnyDeviceUsable())
    {
        //  If not, set the main stack to the error page...
        m_Stack->set_visible_child("error");
        
        // And also hide the menu bar...
        set_show_menubar(false);
    }
}

// Open a simulation model...
void MainWindow::OnActionOpen()
{
    // Create the open file dialog...
    Gtk::FileChooserDialog OpenFileDialog(
        _("Select simulation model"),
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    
    // Set its parent...
    OpenFileDialog.set_transient_for(*this);
    
    // Add response buttons to the dialog...
    OpenFileDialog.add_button(_("_Cancel"), Gtk::RESPONSE_CANCEL);
    OpenFileDialog.add_button(_("Open"), Gtk::RESPONSE_OK);

    // Prepare and add filters...
        
        // Narayan simulation model source...
        Glib::RefPtr<Gtk::FileFilter> ModelSourceFilter =
            Gtk::FileFilter::create();
        ModelSourceFilter->set_name(_("Narayan simulation model source"));
        ModelSourceFilter->add_mime_type("application/narayan-model-source");
        OpenFileDialog.add_filter(ModelSourceFilter);
        
        // Everything else...
        Glib::RefPtr<Gtk::FileFilter> AllFilesFilter =
            Gtk::FileFilter::create();
        AllFilesFilter->set_name(_("All files"));
        AllFilesFilter->add_pattern("*");
        OpenFileDialog.add_filter(AllFilesFilter);
    
    // Run the dialog, and skip loading if the user did not request to do so...
    if(OpenFileDialog.run() != Gtk::RESPONSE_OK)
        return;
    
    // Load the file...
    cout << OpenFileDialog.get_filename() << endl;
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

// Actions to open unit editor dialog...
void MainWindow::OnActionUnitEditor()
{
    // Tell window manager to put dialog centred over main window and always
    //  above it...
    m_Dialog_UnitEditor->set_transient_for(*this);
    
    // Show it...
    m_Dialog_UnitEditor->present();
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

