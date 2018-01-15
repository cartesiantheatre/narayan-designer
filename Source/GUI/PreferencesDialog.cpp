/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "PreferencesDialog.h"

    // OpenCL C++...
    #include <CL/cl2.hpp>

    // Standard C++ / POSIX system headers...
    #include <sstream>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Constructor around Glade's already instantiated dialog...
PreferencesDialog::PreferencesDialog(
    BaseObjectType *CTypeObject, 
    const Glib::RefPtr<Gtk::Builder> &Builder,
    Glib::RefPtr<Gio::Settings> &Settings)
 :  Gtk::Dialog(CTypeObject),
    m_Builder(Builder),
    m_Notebook_Preferences(nullptr),
    m_Settings(Settings),
    m_CheckButton_General_ShowSplash(nullptr),
    m_CheckButton_Editor_UseSystemDefaultMonospaceFont(nullptr),
    m_FontButton_Editor_CustomFont(nullptr),
    m_CheckButton_Editor_UseDarkTheme(nullptr),
    m_TreeView_Editor_ColourScheme(nullptr),
    m_Button_Help(nullptr),
    m_Button_Close(nullptr)
{
    // Find widgets and bind to settings backend if they are associated with a
    //  user configurable setting...

        // Preferences notebook...
        m_Builder->get_widget("Notebook_Preferences", m_Notebook_Preferences);
        g_assert(m_Notebook_Preferences);
        m_Settings->bind("preferences-tab-index", m_Notebook_Preferences->property_page());

        // General tab...
        
            // Show splash check button...
            FindAndBindActiveProperty(
                "CheckButton_General_ShowSplash", 
                m_CheckButton_General_ShowSplash, 
                "general-show-splash");
        
        // Editor tab...
            
            // Use system default monospace font check button...
            FindAndBindActiveProperty(
                "CheckButton_Editor_UseSystemDefaultMonospaceFont", 
                m_CheckButton_Editor_UseSystemDefaultMonospaceFont, 
                "editor-use-system-default-monospace-font");

            // Custom font button...
            m_Builder->get_widget("FontButton_Editor_CustomFont", m_FontButton_Editor_CustomFont);
            g_assert(m_FontButton_Editor_CustomFont);
            m_Settings->bind("editor-custom-font", m_FontButton_Editor_CustomFont->property_font_name());

            // Use dark theme if available check button...
            FindAndBindActiveProperty(
                "CheckButton_Editor_UseDarkTheme",
                m_CheckButton_Editor_UseDarkTheme,
                "editor-use-dark-theme");
            
            // Colour scheme tree view...
            m_Builder->get_widget("TreeView_Editor_ColourScheme", m_TreeView_Editor_ColourScheme);
            g_assert(m_TreeView_Editor_ColourScheme);

        // Help and Close buttons...
        m_Builder->get_widget("Button_Help", m_Button_Help);
        m_Builder->get_widget("Button_Close", m_Button_Close);

    // Connect signals...
        
        // Colour scheme tree view cursor changed...
        m_TreeView_Editor_ColourScheme->signal_cursor_changed().connect(
            sigc::mem_fun(*this, &PreferencesDialog::OnColourSchemeChanged));
        
        // Close button clicked...
        m_Button_Close->signal_clicked().connect(
            sigc::mem_fun(*this, &PreferencesDialog::OnCloseButton));

    // Initialize General tab...
    m_Notebook_Preferences->set_tab_label_text(
       *m_Notebook_Preferences->get_nth_page(Tab_General), _("General"));

    // Initialize Editor tab...
        
        // Set tab label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_Editor), _("Editor"));

        // Set the label showing the system's default monospace font...

            // Get the Gnome settings...
            Glib::RefPtr<Gio::Settings> GnomeSettings =
                Gio::Settings::create("org.gnome.desktop.interface");
        
            // Query for the default monospace font...
            const auto MonospaceFontString =
                GnomeSettings->get_string("monospace-font-name");
            g_assert(!MonospaceFontString.empty());
            
            // Format label...
            stringstream UseSystemMonospaceFontLabelText;
            UseSystemMonospaceFontLabelText
                << _("Use the system's monospace font")
                << " (" << MonospaceFontString << ")";
            
            // Set label...
            m_CheckButton_Editor_UseSystemDefaultMonospaceFont->set_label(
                UseSystemMonospaceFontLabelText.str());

    // Initialize Hardware tab...
    m_Notebook_Preferences->set_tab_label_text(
       *m_Notebook_Preferences->get_nth_page(Tab_Hardware), _("Hardware"));
}

// Find a widget and bind it to a particular setting...
template <typename WidgetType>
void PreferencesDialog::FindAndBindActiveProperty(
    const string &WidgetName,
    WidgetType *& WidgetObject,
    const string &Key) const
{
    // Find the widget...
    m_Builder->get_widget(WidgetName, WidgetObject);
    g_assert(WidgetObject);

    // Get the active property of the widget we will bind settings backend to...
    const auto Property = WidgetObject->property_active();

    // Bind settings...
    m_Settings->bind(Key, Property);
}

// Colour scheme cursor changed in tree view...
void PreferencesDialog::OnColourSchemeChanged()
{
    /* Retrieve the name of the currently selected colour scheme...
    
        // Find the current cursor path and focus column in the treeview...
        TreeModel::Path CurrentCursorPath;
        TreeViewColumn::FocusColumn CurrentFocusColumn;
        m_TreeView_Editor_ColourScheme->get_cursor(CurrentCursorPath, CurrentFocusColumn);
    
        // Verify path iterator is valid...
        if(!CursorPath)
            return;
    
        // Now use the path iterator of the tree view to get the iterator inside
        //  of the tree view's model...
        auto Model = m_TreeView_Editor_ColourScheme->get_modal();
        auto ModelIterator = Model->get_iter(CurrentCursorPath);
    
    // Store the string in the settings backend...
    m_Settings->set_string("editor-colour-scheme", ColourSchemeName);*/
}

// Close button clicked...
void PreferencesDialog::OnCloseButton()
{
    // Hide the dialog...
    hide();
}

// Something or someone is attempting to close the window...
bool PreferencesDialog::on_delete_event([[maybe_unused]] GdkEventAny *Event)
{
    // Hide the dialog...
    hide();

    // Allow further propagation of event...
    return true;
}

