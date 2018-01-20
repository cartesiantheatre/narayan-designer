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
    #include <iostream>
    #include <vector>

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
    m_TreeModel_Hardware_Platform(Gtk::ListStore::create(m_TreeColumns_Hardware_Platform)),
    m_CheckButton_General_ShowSplash(nullptr),
    m_CheckButton_Editor_UseSystemDefaultMonospaceFont(nullptr),
    m_FontButton_Editor_CustomFont(nullptr),
    m_CheckButton_Editor_UseDarkTheme(nullptr),
    m_TreeView_Editor_ColourScheme(nullptr),
    m_ComboBoxText_Hardware_Platform(nullptr),
    m_Label_Hardware_Platform_Profile(nullptr),
    m_Label_Hardware_Platform_Version(nullptr),
    m_Label_Hardware_Platform_Vendor(nullptr),
    m_ComboBoxText_Hardware_Devices(nullptr),
    m_TextView_Hardware_DeviceInfo(nullptr),
    m_Button_Hardware_Refresh(nullptr),
    m_Button_Help(nullptr),
    m_Button_Close(nullptr)
{
    // Preferences notebook...
    
        // Find the widget...
        m_Builder->get_widget("Notebook_Preferences", m_Notebook_Preferences);
        g_assert(m_Notebook_Preferences);
        
        // Bind page index to settings backend...
        m_Settings->bind("preferences-page-index", m_Notebook_Preferences->property_page());

    // General tab...

        // Set label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_General), _("General"));

        // Find show splash check button and bind to settings backend...
        FindAndBindActiveProperty(
            "CheckButton_General_ShowSplash", 
            m_CheckButton_General_ShowSplash, 
            "general-show-splash");

    // Editor tab...

        // Set tab label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_Editor), _("Editor"));

        // Use system default monospace font check button...
        
            // Find and bind to settings backend...
            FindAndBindActiveProperty(
                "CheckButton_Editor_UseSystemDefaultMonospaceFont", 
                m_CheckButton_Editor_UseSystemDefaultMonospaceFont, 
                "editor-use-system-default-monospace-font");

            // Set label showing default font...

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

        // Custom font button...
            
            // Find it...
            m_Builder->get_widget("FontButton_Editor_CustomFont", m_FontButton_Editor_CustomFont);
            g_assert(m_FontButton_Editor_CustomFont);
            
            // Bind to settings backend...
            m_Settings->bind("editor-custom-font", m_FontButton_Editor_CustomFont->property_font_name());

        // Use dark theme if available check button...
        FindAndBindActiveProperty(
            "CheckButton_Editor_UseDarkTheme",
            m_CheckButton_Editor_UseDarkTheme,
            "editor-use-dark-theme");
        
        // Colour scheme tree view...
        
            // Find the widget...
            m_Builder->get_widget("TreeView_Editor_ColourScheme", m_TreeView_Editor_ColourScheme);
            g_assert(m_TreeView_Editor_ColourScheme);
            
            // Connect cursor changed signal...
            m_TreeView_Editor_ColourScheme->signal_cursor_changed().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnColourSchemeChanged));

    // Hardware tab...
    
        // Set label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_Hardware), _("Hardware"));

        // Hardware platform combobox text...
            
            // Find it...
            m_Builder->get_widget("ComboBoxText_Hardware_Platform", m_ComboBoxText_Hardware_Platform);
            g_assert(m_ComboBoxText_Hardware_Platform);
            
            // Set its storage tree model...
            m_ComboBoxText_Hardware_Platform->set_model(m_TreeModel_Hardware_Platform);
            
            // Add columns, but only show platform name for now...
            m_ComboBoxText_Hardware_Platform->clear();
            m_ComboBoxText_Hardware_Platform->pack_start(m_TreeColumns_Hardware_Platform.m_Column_ID);
            m_ComboBoxText_Hardware_Platform->pack_start(m_TreeColumns_Hardware_Platform.m_Column_Name);

            // Bind to settings backend...
            m_Settings->bind("hardware-platform-id", m_ComboBoxText_Hardware_Platform->property_active());

            // Connect selection change signal...
            m_ComboBoxText_Hardware_Platform->signal_changed().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnHardwarePlatformChanged));

        // Hardware platform labels...
        m_Builder->get_widget("Label_Hardware_Platform_Profile", m_Label_Hardware_Platform_Profile);
        m_Builder->get_widget("Label_Hardware_Platform_Version", m_Label_Hardware_Platform_Version);
        m_Builder->get_widget("Label_Hardware_Platform_Vendor", m_Label_Hardware_Platform_Vendor);

        // Hardware device combobox text...

            // Find it...
            m_Builder->get_widget("ComboBoxText_Hardware_Devices", m_ComboBoxText_Hardware_Devices);
            g_assert(m_ComboBoxText_Hardware_Devices);
            
            // Connect selection change signal...
            m_ComboBoxText_Hardware_Devices->signal_changed().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnHardwareDeviceChanged));
        
        // Device information textview...
        m_Builder->get_widget("TextView_Hardware_DeviceInfo", m_TextView_Hardware_DeviceInfo);
        g_assert(m_TextView_Hardware_DeviceInfo);

        // Refresh hardware button...

            // Find it...
            m_Builder->get_widget("Button_Hardware_Refresh", m_Button_Hardware_Refresh);
            g_assert(m_Button_Hardware_Refresh);

            // Connect clicked signal...
            m_Button_Hardware_Refresh->signal_clicked().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnRefreshHardware));

            // Populate platform and device combo boxes...
            m_Button_Hardware_Refresh->clicked();

    // Help button...
    
        // Find it...
        m_Builder->get_widget("Button_Help", m_Button_Help);
        g_assert(m_Button_Help);
        
        // Connect click signal...
        m_Button_Help->signal_clicked().connect(
            sigc::mem_fun(*this, &PreferencesDialog::OnHelpButton));

    // Close button...
    
        // Find it...
        m_Builder->get_widget("Button_Close", m_Button_Close);
        g_assert(m_Button_Close);

        // Connect clicked signal...
        m_Button_Close->signal_clicked().connect(
            sigc::mem_fun(*this, &PreferencesDialog::OnCloseButton));
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

// Hardware device combobox text selection changed...
void PreferencesDialog::OnHardwareDeviceChanged()
{

}

// Hardware platform combobox text selection changed...
void PreferencesDialog::OnHardwarePlatformChanged()
{
    // Clear previous hardware platform labels...
    m_Label_Hardware_Platform_Profile->set_label("");
    m_Label_Hardware_Platform_Version->set_label("");
    m_Label_Hardware_Platform_Vendor->set_label("");

    // Get the selected text...
    Gtk::TreeModel::iterator Index = m_ComboBoxText_Hardware_Platform->get_active();

        // Nothing selected...
        if(!Index)
        {
            // De-select any device of the platform that may have been selected...
            m_ComboBoxText_Hardware_Devices->set_active(-1);
        }

    // Get the row...
    Gtk::TreeModel::Row CurrentRow = *Index;

    // Get the hardware platform's information...
    const string PlatformProfile    = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Profile];
    const string PlatformVersion    = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Version];
    const string PlatformName       = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Name];
    const string PlatformVendor     = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Vendor];

    // Set the hardware platform labels...
    m_Label_Hardware_Platform_Profile->set_label(PlatformProfile);
    m_Label_Hardware_Platform_Version->set_label(PlatformVersion);
    m_Label_Hardware_Platform_Vendor->set_label(PlatformVendor);
}

// Help button clicked...
void PreferencesDialog::OnHelpButton()
{

}

// Populate platform and device combo boxes...
void PreferencesDialog::OnRefreshHardware()
{
    // Query settings backend for user's selected hardware platform ID...
    const int SelectedPlatformID = m_Settings->get_int("hardware-platform-id");

    // Get the list of hardware platforms...
    vector<cl::Platform> Platforms;
    cl::Platform::get(&Platforms);

    // Populate model with the list of platforms...
    
        // Remove the old ones...
        m_TreeModel_Hardware_Platform->clear();

        // Add each one OpenCL provided us...
        for(size_t Index = 0; Index < Platforms.size(); ++Index)
        {
            // Get a platform...
            const cl::Platform  &CurrentPlatform = Platforms.at(Index);

            // Allocate a new row...
            Gtk::TreeModel::Row NewRow = *(m_TreeModel_Hardware_Platform->append());

            // Query current platform for profile, version, name, and vendor...
            auto PlatformProfile    = CurrentPlatform.getInfo<CL_PLATFORM_PROFILE>();
            auto PlatformVersion    = CurrentPlatform.getInfo<CL_PLATFORM_VERSION>();
            auto PlatformName       = CurrentPlatform.getInfo<CL_PLATFORM_NAME>();
            auto PlatformVendor     = CurrentPlatform.getInfo<CL_PLATFORM_VENDOR>();
            
            // Populate the new row...
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_ID]         = Index;
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Profile]    = PlatformProfile;
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Version]    = PlatformVersion;
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Name]       = PlatformName;
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Vendor]     = PlatformVendor;
        }

        // Select the one that was stored in the settings backend...
        m_ComboBoxText_Hardware_Platform->set_active(SelectedPlatformID);

    /*m_ComboBoxText_Hardware_Devices
    
    m_TextView_Hardware_DeviceInfo*/
}

