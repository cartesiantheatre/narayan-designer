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
    #include <iostream>
    #include <iomanip>
    #include <vector>
    #include <regex>

    // Gtkmm...
    #include <gtkmm/scrolledwindow.h>
    
    // GtkSourceViewMM...
    #include <gtksourceviewmm/styleschemechooser.h>

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
    m_CheckButton_General_StartupShowSplash(nullptr),
    m_CheckButton_General_StartupShowUsageTips(nullptr),
    m_CheckButton_General_PlaySoundEffects(nullptr),
    m_CheckButton_Editor_UseSystemDefaultMonospaceFont(nullptr),
    m_FontButton_Editor_CustomFont(nullptr),
    m_CheckButton_Editor_UseDarkTheme(nullptr),
    m_StyleSchemeChooserWidget_Editor(nullptr),
    m_ComboBoxText_Hardware_Platform(nullptr),
    m_ListStore_Hardware_Platform(Gtk::ListStore::create(m_TreeColumns_Hardware_Platform)),
    m_Label_Hardware_Platform_Profile(nullptr),
    m_Label_Hardware_Platform_Version(nullptr),
    m_Label_Hardware_Platform_Vendor(nullptr),
    m_ComboBoxText_Hardware_Devices(nullptr),
    m_ListStore_Hardware_Devices(Gtk::ListStore::create(m_TreeColumns_Hardware_Devices)),
    m_TextView_Hardware_DeviceInfo(nullptr),
    m_Hardware_DeviceInfo_DefaultText(_("Select a device to see more information on its capabilities.")),
    m_Button_DeviceInfo_Copy(nullptr),
    m_Button_Hardware_Refresh(nullptr),
    m_Button_Help(nullptr),
    m_Button_Close(nullptr)
{
    // Preferences notebook...
    
        // Find the widget...
        m_Builder->get_widget("PreferencesDialog_Notebook_Preferences", m_Notebook_Preferences);
        g_assert(m_Notebook_Preferences);
        
        // Bind page index to settings backend...
        m_Settings->bind("preferences-page-index", m_Notebook_Preferences->property_page());

    // General tab...

        // Set label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_General), _("General"));

        // Find show splash check button and bind to settings backend...
        FindAndBindActiveProperty(
            "PreferencesDialog_CheckButton_General_StartupShowSplash",
            m_CheckButton_General_StartupShowSplash,
            "general-startup-show-splash");

        // Find show usage tips check button and bind to settings backend...
        FindAndBindActiveProperty(
            "PreferencesDialog_CheckButton_General_StartupShowUsageTips",
            m_CheckButton_General_StartupShowUsageTips,
            "general-startup-show-usage-tips");

        // Find play sound effects check button and bind to settings backend...
        FindAndBindActiveProperty(
            "PreferencesDialog_CheckButton_General_PlaySoundEffects",
            m_CheckButton_General_PlaySoundEffects,
            "general-play-sound-effects");

    // Editor tab...

        // Set tab label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_Editor), _("Editor"));

        // Use system default monospace font check button...
        
            // Find and bind to settings backend...
            FindAndBindActiveProperty(
                "PreferencesDialog_CheckButton_Editor_UseSystemDefaultMonospaceFont", 
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
            m_Builder->get_widget("PreferencesDialog_FontButton_Editor_CustomFont", m_FontButton_Editor_CustomFont);
            g_assert(m_FontButton_Editor_CustomFont);

            // Bind to settings backend...
            m_Settings->bind("editor-custom-font", m_FontButton_Editor_CustomFont->property_font_name());

        // Use dark theme if available check button...
        FindAndBindActiveProperty(
            "PreferencesDialog_CheckButton_Editor_UseDarkTheme",
            m_CheckButton_Editor_UseDarkTheme,
            "editor-use-dark-theme");

        // Style scheme chooser...

            // Find the parent GtkScrolledWindow widget...
            Gtk::ScrolledWindow *ScrolledWindowStyleSchemeChooserWidget_Editor = nullptr;
            m_Builder->get_widget("PreferencesDialog_ScrolledWindowStyleSchemeChooserWidget_Editor", ScrolledWindowStyleSchemeChooserWidget_Editor);
            g_assert(ScrolledWindowStyleSchemeChooserWidget_Editor);

            // Workaround for <https://bugzilla.gnome.org/show_bug.cgi?id=744478>
            //  which requires us to manually create the chooser widget since
            //  at the time of writing Glade would have clobbered it...

                // Create StyleSchemeChooserWidget and let its lifetime be
                //  managed by its parent container...
                m_StyleSchemeChooserWidget_Editor =
                    Gtk::manage(new Gsv::StyleSchemeChooserWidget());

                // Add to parent GtkScrolledWindow container...
                ScrolledWindowStyleSchemeChooserWidget_Editor->add(
                    *m_StyleSchemeChooserWidget_Editor);

                // Make it visible...
                m_StyleSchemeChooserWidget_Editor->set_visible(true);

            /* Another workaround for setting its selected scheme...

                // What did the user previously have selected?
                const std::string CurrentEditorStyleSchemeID =
                    m_Settings->get_string("editor-style-scheme");

                // Lookup that style scheme ID in the scheme manager...
                Glib::RefPtr<Gsv::StyleSchemeManager> DefaultStyleSchemeManager
                    = Gsv::StyleSchemeManager::get_default();
                Glib::RefPtr<Gsv::StyleScheme> CurrentStyleScheme
                    = DefaultStyleSchemeManager->get_scheme(CurrentEditorStyleSchemeID);

                // Find the chooser object...
                GtkSourceStyleSchemeChooser *Chooser =
                    GTK_SOURCE_STYLE_SCHEME_CHOOSER(
                        m_StyleSchemeChooserWidget_Editor->gobj());
                
                // Set the selected scheme...
              ::gtk_source_style_scheme_chooser_set_style_scheme(
                    Chooser,
                    GTK_SOURCE_STYLE_SCHEME(CurrentStyleScheme->gobj()));*/

            // Another workaround for tracking its selected scheme...
            
                // I can't find any way obtain the style-scheme property
                //  directly from the chooser widget, so we wrap the property
                //  manually...
                Glib::PropertyProxy< Glib::RefPtr<Gsv::StyleScheme> >
                    PropertyStyleScheme(
                        m_StyleSchemeChooserWidget_Editor,
                        "style-scheme");

                // But even then, we can't this property directly to a GSettings
                //  backend because it doesn't seem to be able to handle
                //  GtkSourceStyleScheme types as keys with string values in the
                //  settings schema. So we manually connect a callback to
                //  monitor whenever the property changes...
                PropertyStyleScheme.signal_changed().connect(
                    sigc::mem_fun(*this, &PreferencesDialog::OnEditorColourSchemeChanged));

    // Hardware tab...
    
        // Set label...
        m_Notebook_Preferences->set_tab_label_text(
           *m_Notebook_Preferences->get_nth_page(Tab_Hardware), _("Hardware"));

        // Hardware platform combobox text...
            
            // Find it...
            m_Builder->get_widget("PreferencesDialog_ComboBoxText_Hardware_Platform", m_ComboBoxText_Hardware_Platform);
            g_assert(m_ComboBoxText_Hardware_Platform);
            
            // Set its storage tree model...
            m_ComboBoxText_Hardware_Platform->set_model(m_ListStore_Hardware_Platform);
            
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
        m_Builder->get_widget("PreferencesDialog_Label_Hardware_Platform_Profile", m_Label_Hardware_Platform_Profile);
        m_Builder->get_widget("PreferencesDialog_Label_Hardware_Platform_Version", m_Label_Hardware_Platform_Version);
        m_Builder->get_widget("PreferencesDialog_Label_Hardware_Platform_Vendor", m_Label_Hardware_Platform_Vendor);

        // Hardware device combobox text...

            // Find it...
            m_Builder->get_widget("PreferencesDialog_ComboBoxText_Hardware_Devices", m_ComboBoxText_Hardware_Devices);
            g_assert(m_ComboBoxText_Hardware_Devices);

            // Set its storage tree model...
            m_ComboBoxText_Hardware_Devices->set_model(m_ListStore_Hardware_Devices);

            // Add simple columns...
            m_ComboBoxText_Hardware_Devices->clear();
            m_ComboBoxText_Hardware_Devices->pack_start(m_TreeColumns_Hardware_Devices.m_Column_Name);
            
            // Add more sophisticated columns requiring a custom cell renderer...
            m_ComboBoxText_Hardware_Devices->set_cell_data_func(
                m_CellRendererText_Hardware_Devices_Type,
                sigc::mem_fun(*this, &PreferencesDialog::OnCellDataOpenCLDeviceType));
            m_ComboBoxText_Hardware_Devices->pack_start(m_CellRendererText_Hardware_Devices_Type);

            // Connect selection change signal...
            m_ComboBoxText_Hardware_Devices->signal_changed().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnHardwareDeviceChanged));
        
        // Device information textview...
        m_Builder->get_widget("PreferencesDialog_TextView_Hardware_DeviceInfo", m_TextView_Hardware_DeviceInfo);
        g_assert(m_TextView_Hardware_DeviceInfo);

        // Copy device info button...

            // Find it...
            m_Builder->get_widget("PreferencesDialog_Button_DeviceInfo_Copy", m_Button_DeviceInfo_Copy);
            g_assert(m_Button_DeviceInfo_Copy);

            // Connect clicked signal...
            m_Button_DeviceInfo_Copy->signal_clicked().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnCopyDeviceInfo));

        // Refresh hardware button...

            // Find it...
            m_Builder->get_widget("PreferencesDialog_Button_Hardware_Refresh", m_Button_Hardware_Refresh);
            g_assert(m_Button_Hardware_Refresh);

            // Connect clicked signal...
            m_Button_Hardware_Refresh->signal_clicked().connect(
                sigc::mem_fun(*this, &PreferencesDialog::OnRefreshHardware));

            // Populate platform and device combo boxes...
            m_Button_Hardware_Refresh->clicked();

    // Help button...
    
        // Find it...
        m_Builder->get_widget("PreferencesDialog_Button_Help", m_Button_Help);
        g_assert(m_Button_Help);
        
        // Connect click signal...
        m_Button_Help->signal_clicked().connect(
            sigc::mem_fun(*this, &PreferencesDialog::OnHelpButton));

    // Close button...
    
        // Find it...
        m_Builder->get_widget("PreferencesDialog_Button_Close", m_Button_Close);
        g_assert(m_Button_Close);

        // Connect clicked signal...
        m_Button_Close->signal_clicked().connect(
            sigc::mem_fun(*this, &PreferencesDialog::OnCloseButton));
}

// Find a widget and bind it to a particular setting...
template <typename WidgetType>
void PreferencesDialog::FindAndBindActiveProperty(
    const string &WidgetName, WidgetType &&WidgetObject, const string &Key) const
{
    // Find the widget...
    m_Builder->get_widget(WidgetName, std::forward<WidgetType>(WidgetObject));
    g_assert(WidgetObject);

    // Get the active property of the widget we will bind settings backend to...
    const auto Property = WidgetObject->property_active();

    // Bind settings...
    m_Settings->bind(Key, Property);
}

// OpenCL device type needing to be rendered in a combobox cell...
void PreferencesDialog::OnCellDataOpenCLDeviceType(
    const Gtk::TreeModel::const_iterator &Iterator)
{
    // Retrieve the row from the iterator...
    Gtk::TreeModel::Row CurrentRow = *Iterator;
    
    // Obtain the OpenCL device type stored within the row...
    const cl_device_type DeviceType = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_Type];

    // Transform the OpenCL device type into a human readable string and set a
    //  colour too based on expected capability...
    switch(DeviceType)
    {
        // CPU...
        case CL_DEVICE_TYPE_CPU:
            m_CellRendererText_Hardware_Devices_Type.property_text()            = _("(CPU)");
            m_CellRendererText_Hardware_Devices_Type.property_foreground_rgba() = Gdk::RGBA("#00fe00");
            break;

        // GPU...
        case CL_DEVICE_TYPE_GPU: 
            m_CellRendererText_Hardware_Devices_Type.property_text()            = _("(GPU)");
            m_CellRendererText_Hardware_Devices_Type.property_foreground_rgba() = Gdk::RGBA("#00fe00");
            break;
        
        // Dedicated OpenCL hardware accelerator, such as the IBM CELL Blade...
        case CL_DEVICE_TYPE_ACCELERATOR:
            m_CellRendererText_Hardware_Devices_Type.property_text()            = _("(dedicated OpenCL accelerator)");
            m_CellRendererText_Hardware_Devices_Type.property_foreground_rgba() = Gdk::RGBA("#00fe00");
            break;
            
        // Dedicated accelerators that do not support programs written in OpenCL C...
        case CL_DEVICE_TYPE_CUSTOM:
            m_CellRendererText_Hardware_Devices_Type.property_text()            = _("(dedicated accelerator)");
            m_CellRendererText_Hardware_Devices_Type.property_foreground_rgba() = Gdk::RGBA("#fe0000");
            break;
        
        // Unknown...
        default:
            m_CellRendererText_Hardware_Devices_Type.property_text()            = _("(unknown)"); break;
            m_CellRendererText_Hardware_Devices_Type.property_foreground_rgba() = Gdk::RGBA("#0000fe");
            break;
    }
}

// Close button clicked...
void PreferencesDialog::OnCloseButton()
{
    // Hide the dialog...
    hide();
}

// Copy device info button clicked...
void PreferencesDialog::OnCopyDeviceInfo()
{
    // Retrieve the clipboard...
    Glib::RefPtr<Gtk::Clipboard> ClipboardObject = Gtk::Clipboard::get();

    // Get the text buffer for the device info textview...
    Glib::RefPtr<Gtk::TextBuffer> TextBuffer =
        m_TextView_Hardware_DeviceInfo->get_buffer();
    
    // Set the clipboard text to the contents of the device info...
    ClipboardObject->set_text(TextBuffer->get_text());
}

// Colour scheme cursor changed...
void PreferencesDialog::OnEditorColourSchemeChanged()
{
    // GtkStyleSchemeChooserWidget is not a GtkSourceStyleSchemeChooser so I
    //  don't know why this works, but it does...
    GtkSourceStyleSchemeChooser *Chooser =
        GTK_SOURCE_STYLE_SCHEME_CHOOSER(
            m_StyleSchemeChooserWidget_Editor->gobj());
    
    // Get the selected style scheme...
    GtkSourceStyleScheme *SourceStyleScheme =
        ::gtk_source_style_scheme_chooser_get_style_scheme(Chooser);
    
    // Get the ID string of the style scheme...
    const std::string StyleSchemeID = 
        ::gtk_source_style_scheme_get_id(SourceStyleScheme);

    // Store it in the settings backend...
    m_Settings->set_string("editor-style-scheme", StyleSchemeID);
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
    // Get iterator to currently selected item in devices combobox text...
    Gtk::TreeModel::const_iterator TreeModelIterator =
        m_ComboBoxText_Hardware_Devices->get_active();

    // Get the text buffer for the device info textview...
    Glib::RefPtr<Gtk::TextBuffer> TextBuffer =
        m_TextView_Hardware_DeviceInfo->get_buffer();

    // Nothing is selected...
    if(!TreeModelIterator)
    {
        // Clear the device information back to default...
        TextBuffer->property_text() = m_Hardware_DeviceInfo_DefaultText;

        // Nothing to query then...
        return;
    }

    // Get the row associated with the selected device...
    Gtk::TreeModel::Row CurrentRow = *TreeModelIterator;

    // Query OpenCL implementation for device details...
    const string Name                           = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_Name];
    const string Vendor                         = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_Vendor];
    const unsigned int MaxComputeUnits          = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_MaxComputeUnits];
    const unsigned long GlobalMemory            = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_GlobalMemory];
    const unsigned int MaxClockFrequency        = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_MaxClockFrequency];
    const unsigned long MaxAllocatableMemory    = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_MaxAllocatableMemory];
    const unsigned long LocalMemory             = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_LocalMemory];
    const bool Available                        = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_Available];
    const string Extensions                     = CurrentRow[m_TreeColumns_Hardware_Devices.m_Column_Extensions];

    // Format the new device info text from the information queried...
    stringstream NewBufferText;
    NewBufferText.setf(ios::fixed,ios::floatfield);
    NewBufferText.precision(1);
    NewBufferText 
        << _("Name: ") << Name << endl
        << _("Vendor: ") << Vendor << endl
        << _("Max Computing Units: ") << MaxComputeUnits << endl
        << _("Global Memory: ") 
            << GlobalMemory 
            << " ("
            << static_cast<float>(GlobalMemory) / (1024 * 1024 * 1024)
            << " GB)" << endl
        << _("Max Clock Frequency: ") << MaxClockFrequency << " MHz" << endl
        << _("Max Allocatable Memory: ")
            << MaxAllocatableMemory
            << " ("
            << static_cast<float>(MaxAllocatableMemory) / (1024 * 1024 * 1024)
            << " GB)" << endl
        << _("Local Memory: ")
            << LocalMemory
            << " ("
            << static_cast<float>(LocalMemory) / (1024 * 1024)
            << " MB)" << endl
        << _("Available: ") << Available << endl
        << _("Extensions: ") << endl
            << "\t" << regex_replace(Extensions, regex(" "), "\n\t")
        << endl;
    
    // Set the new buffer text...
    TextBuffer->property_text() = NewBufferText.str();
}

// Hardware platform combobox text selection changed...
void PreferencesDialog::OnHardwarePlatformChanged()
{
    // Clear previous hardware platform labels...
    m_Label_Hardware_Platform_Profile->set_label("");
    m_Label_Hardware_Platform_Version->set_label("");
    m_Label_Hardware_Platform_Vendor->set_label("");

    // Get the platform selected...
    const Gtk::TreeModel::iterator TreeModelIterator =
        m_ComboBoxText_Hardware_Platform->get_active();

        // None selected. De-select any device of the platform that may have
        //  been selected...
        if(!TreeModelIterator)
            m_ComboBoxText_Hardware_Devices->set_active(-1);

    // Get the row...
    Gtk::TreeModel::Row CurrentRow = *TreeModelIterator;

    // Get the hardware platform's information...
    const int PlatformID            = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_ID];
    const string PlatformProfile    = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Profile];
    const string PlatformVersion    = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Version];
    const string PlatformName       = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Name];
    const string PlatformVendor     = CurrentRow[m_TreeColumns_Hardware_Platform.m_Column_Vendor];

    // Set the hardware platform labels...
    m_Label_Hardware_Platform_Profile->set_label(PlatformProfile);
    m_Label_Hardware_Platform_Version->set_label(PlatformVersion);
    m_Label_Hardware_Platform_Vendor->set_label(PlatformVendor);

    // Populate the list of devices...

        // Clear old ones...
        m_ListStore_Hardware_Devices = Gtk::ListStore::create(m_TreeColumns_Hardware_Devices);
        m_ComboBoxText_Hardware_Devices->set_model(m_ListStore_Hardware_Devices);

        // Get the list of hardware platforms since we need to query the
        //  selected one for its available devices...
        vector<cl::Platform> Platforms;
        cl::Platform::get(&Platforms);
        
        // Find the selected platform...
        const cl::Platform &SelectedPlatform = Platforms.at(PlatformID);

        // Storage for list of devices...
        vector<cl::Device> Devices;
        
        // Try to query its devices. Some implementations have a bug where if
        //  no devices are detected, CL_HPP_ENABLE_EXCEPTIONS is defined and
        //  CL_SUCCESS is returned instead of CL_DEVICE_NOT_FOUND a nasty
        //  unexpected exception is thrown...
        cl_int GetDevicesStatus = 0;
        try
        {
            // Perform query...
            GetDevicesStatus = SelectedPlatform.getDevices(CL_DEVICE_TYPE_ALL, &Devices);
        }
            // Failed...
            catch(const cl::Error &Exception)
            {
                // This isn't an implementation bug we recognize, so pass up
                //  the exception handler chain...
                if((GetDevicesStatus != CL_SUCCESS) || (Exception.what() != string("clGetDeviceIDs")))
                    throw Exception;
            }

        // Add each device OpenCL provided us...
        for(size_t Index = 0; Index < Devices.size(); ++Index)
        {
            // Get a device...
            const cl::Device  &CurrentDevice = Devices.at(Index);

            // Allocate a new row...
            Gtk::TreeModel::Row NewRow = *(m_ListStore_Hardware_Devices->append());

            // Populate the new row with the queried results from the device...
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_Name]                    = CurrentDevice.getInfo<CL_DEVICE_NAME>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_Type]                    = CurrentDevice.getInfo<CL_DEVICE_TYPE>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_Vendor]                  = CurrentDevice.getInfo<CL_DEVICE_VENDOR>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_MaxComputeUnits]         = CurrentDevice.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_GlobalMemory]            = CurrentDevice.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_MaxClockFrequency]       = CurrentDevice.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_MaxAllocatableMemory]    = CurrentDevice.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_LocalMemory]             = CurrentDevice.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_Available]               = CurrentDevice.getInfo<CL_DEVICE_AVAILABLE>();
            NewRow[m_TreeColumns_Hardware_Devices.m_Column_Extensions]              = CurrentDevice.getInfo<CL_DEVICE_EXTENSIONS>();
        }

        // If the list had any devices at all, select the first one...
        if(!Devices.empty())
            m_ComboBoxText_Hardware_Devices->set_active(0);
        
        // No devices on this hardware platform...
        else
        {
            // De-select, though not sure if this is necessary... 
            m_ComboBoxText_Hardware_Devices->set_active(-1);

            // Clear the device information textview back to default...

                // Get the text buffer...
                Glib::RefPtr<Gtk::TextBuffer> TextBuffer =
                    m_TextView_Hardware_DeviceInfo->get_buffer();

                // Clear the device information back to default...
                TextBuffer->property_text() = m_Hardware_DeviceInfo_DefaultText;
        }
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
        //This emits a bunch of warnings: m_ListStore_Hardware_Platform->clear(); 
        m_ListStore_Hardware_Platform = Gtk::ListStore::create(m_TreeColumns_Hardware_Platform);
        m_ComboBoxText_Hardware_Platform->set_model(m_ListStore_Hardware_Platform);

        // Add each platform OpenCL provided us...
        for(size_t Index = 0; Index < Platforms.size(); ++Index)
        {
            // Get a platform...
            const cl::Platform  &CurrentPlatform = Platforms.at(Index);

            // Allocate a new row...
            Gtk::TreeModel::Row NewRow = *(m_ListStore_Hardware_Platform->append());

            // Populate the new row with the details OpenCL provided us about
            //  the platform...
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_ID]         = Index;
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Profile]    = CurrentPlatform.getInfo<CL_PLATFORM_PROFILE>();
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Version]    = CurrentPlatform.getInfo<CL_PLATFORM_VERSION>();;
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Name]       = CurrentPlatform.getInfo<CL_PLATFORM_NAME>();
            NewRow[m_TreeColumns_Hardware_Platform.m_Column_Vendor]     = CurrentPlatform.getInfo<CL_PLATFORM_VENDOR>();
        }

        // Select the one that was stored in the settings backend...
        m_ComboBoxText_Hardware_Platform->set_active(SelectedPlatformID);
}

