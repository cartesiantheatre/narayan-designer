/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "PreferencesDialog.h"

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
    // Find widgets...
    
        // Preferences notebook...
        m_Builder->get_widget("Notebook_Preferences", m_Notebook_Preferences);
        g_assert(m_Notebook_Preferences);

        /* General tab...
        m_Builder->get_widget("CheckButton_General_ShowSplash", m_CheckButton_General_ShowSplash);*/

        // Editor tab...
        m_Builder->get_widget("CheckButton_Editor_UseSystemDefaultMonospaceFont", m_CheckButton_Editor_UseSystemDefaultMonospaceFont);
        m_Builder->get_widget("FontButton_Editor_CustomFont", m_FontButton_Editor_CustomFont);
        m_Builder->get_widget("CheckButton_Editor_UseDarkTheme", m_CheckButton_Editor_UseDarkTheme);
        m_Builder->get_widget("TreeView_Editor_ColourScheme", m_TreeView_Editor_ColourScheme);

        // Help and Close buttons...
        m_Builder->get_widget("Button_Help", m_Button_Help);
        m_Builder->get_widget("Button_Close", m_Button_Close);

    // Connect signals...
    m_Button_Close->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesDialog::OnCloseButton));

    // Bind settings to preference dialog's widgets...
    m_Settings->bind("tab-index", m_Notebook_Preferences->property_page());
    //m_Settings->bind("general-show-splash", m_CheckButton_General_ShowSplash->property_state());

    FindAndBind(
        "CheckButton_General_ShowSplash",
        m_CheckButton_General_ShowSplash,
        "general-show-splash",
        m_CheckButton_General_ShowSplash->property_related_action());

//    m_Settings->bind("editor-", m_CheckButton_General_ShowSplash->property_state());

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
                << "(" << MonospaceFontString << ")";
            
            // Set label...
            m_CheckButton_Editor_UseSystemDefaultMonospaceFont->set_label(
                UseSystemMonospaceFontLabelText.str());

            // Create a font description from the string which contains the name
            //  followed by the size of the face...
            //Pango::FontDescription MonospaceFontDescription(MonospaceFontString);

    // Initialize Hardware tab...
    m_Notebook_Preferences->set_tab_label_text(
       *m_Notebook_Preferences->get_nth_page(Tab_Hardware), _("Hardware"));
}

// Find a widget and bind it to a particular setting...
template <typename WidgetType, typename PropertyType>
void PreferencesDialog::FindAndBind(
    const string &WidgetName,
    const WidgetType *WidgetObject,
    const string &Key,
    const Glib::PropertyProxy<PropertyType> Property) const
{
    // Find the widget...
    m_Builder->get_widget(WidgetName, WidgetObject);

    // Bind settings...
    m_Settings->bind(Key, Property);
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

