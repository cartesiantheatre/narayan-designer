/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _PREFERENCES_DIALOG_H_
#define _PREFERENCES_DIALOG_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanDesignerApplication.h"

    // OpenCL C++...
    #include <CL/cl2.hpp>

    // Gtkmm...
    #include <gtkmm/builder.h>
    #include <gtkmm/button.h>
    #include <gtkmm/checkbutton.h>
    #include <gtkmm/comboboxtext.h>
    #include <gtkmm/dialog.h>
    #include <gtkmm/fontbutton.h>
    #include <gtkmm/liststore.h>
    #include <gtkmm/notebook.h>
    #include <gtkmm/textview.h>
    #include <gtkmm/treeview.h>

    // Standard C++ / POSIX system headers...
    #include <string>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Preferences dialog...
class PreferencesDialog : public Gtk::Dialog
{
    // Public methods...
    public:
    
        // Constructor around Glade's already instantiated dialog...
        PreferencesDialog(
            BaseObjectType *CTypeObject,
            const Glib::RefPtr<Gtk::Builder> &Builder,
            Glib::RefPtr<Gio::Settings> &Settings);

    // Protected methods...
    protected:

        // Find a widget and bind it to a particular setting...
        template <typename WidgetType>
        void FindAndBindActiveProperty(
            const std::string &WidgetName,
            WidgetType *& WidgetObject,
            const std::string &Key) const;

        // Signals...

            // Overridden defaults...
        
                // Window is being closed...
                bool on_delete_event(GdkEventAny *Event) override;
            
            // Manually registered...

                // OpenCL device type needing to be rendered in a combobox cell...
                void OnCellDataOpenCLDeviceType(
                    const Gtk::TreeModel::const_iterator &Iterator);
                
                // Close button clicked...
                void OnCloseButton();

                // Colour scheme cursor changed in tree view...
                void OnColourSchemeChanged();

                // Hardware device combobox text selection changed...
                void OnHardwareDeviceChanged();

                // Hardware platform combobox text selection changed...
                void OnHardwarePlatformChanged();

                // Help button clicked...
                void OnHelpButton();

                // Populate platform and device combo boxes...
                void OnRefreshHardware();

    // Protected attributes, classes, and enumerated types...
    protected:

        // Hardware platform tree model columns...
        class HardwarePlatformTreeColumns : public Gtk::TreeModel::ColumnRecord
        {
            // Public methods and attributes...
            public:
                
                // Default constructor...
                HardwarePlatformTreeColumns()
                {
                    // ...merely adds columns...
                    add(m_Column_ID);
                    add(m_Column_Profile);
                    add(m_Column_Version);
                    add(m_Column_Name);
                    add(m_Column_Vendor);
                }
                
                // Columns...
                Gtk::TreeModelColumn<int>           m_Column_ID;
                Gtk::TreeModelColumn<std::string>   m_Column_Profile;
                Gtk::TreeModelColumn<std::string>   m_Column_Version;
                Gtk::TreeModelColumn<std::string>   m_Column_Name;
                Gtk::TreeModelColumn<std::string>   m_Column_Vendor;
        };
        
        // Hardware devices tree model columns...
        class HardwareDevicesTreeColumns : public Gtk::TreeModel::ColumnRecord
        {
            // Public methods and attributes...
            public:
                
                // Default constructor...
                HardwareDevicesTreeColumns()
                {
                    // ...merely adds columns...
                    add(m_Column_Name);
                    add(m_Column_Type);
                }
                
                // Columns...
                Gtk::TreeModelColumn<std::string>   m_Column_Name;
                /*
                    This should be cl_device_type, but there appears to be a bug
                    in GCC 7.1 which emits a false positive error regarding
                    ignored template parameter attributes being ignored. 
                */
                Gtk::TreeModelColumn<unsigned long> m_Column_Type; 
        };

        // Notebook tab ordinals...
        enum
        {
            Tab_General,
            Tab_Editor,
            Tab_Hardware
        };

        // Builder...
        Glib::RefPtr<Gtk::Builder>          m_Builder;

        // Settings

            // Preferences notebook...
            Gtk::Notebook                  *m_Notebook_Preferences;
        
            // Backend...
            Glib::RefPtr<Gio::Settings>     m_Settings;
            

        // General tab...

            // Show splash check button...
            Gtk::CheckButton               *m_CheckButton_General_ShowSplash;
        
        // Editor tab...
            
            // Use system monospace font...
            Gtk::CheckButton               *m_CheckButton_Editor_UseSystemDefaultMonospaceFont;
            
            // Custom font to use...
            Gtk::FontButton                *m_FontButton_Editor_CustomFont;
            
            // Use dark theme variant, if available...
            Gtk::CheckButton               *m_CheckButton_Editor_UseDarkTheme;
            
            // Colour scheme...
            Gtk::TreeView                  *m_TreeView_Editor_ColourScheme;
        
        // Hardware tab...

            // Platform combobox text, tree columns definition, and the actual
            //  ListStore for the storage each row...
            Gtk::ComboBoxText              *m_ComboBoxText_Hardware_Platform;
            HardwarePlatformTreeColumns     m_TreeColumns_Hardware_Platform;
            Glib::RefPtr<Gtk::ListStore>    m_ListStore_Hardware_Platform;

            // Platform labels...
            Gtk::Label                     *m_Label_Hardware_Platform_Profile;
            Gtk::Label                     *m_Label_Hardware_Platform_Version;
            Gtk::Label                     *m_Label_Hardware_Platform_Vendor;

            // Device combobox text, tree columns definition, the ListStore for
            //  the storage of the rows, and a custom cell renderer...
            Gtk::ComboBoxText              *m_ComboBoxText_Hardware_Devices;
            HardwareDevicesTreeColumns      m_TreeColumns_Hardware_Devices;
            Glib::RefPtr<Gtk::ListStore>    m_ListStore_Hardware_Devices;
            Gtk::CellRendererText           m_CellRendererText_Hardware_Devices_Type;

            // Device textview...
            Gtk::TextView                  *m_TextView_Hardware_DeviceInfo;

            // Refresh hardware button...
            Gtk::Button                    *m_Button_Hardware_Refresh;

        // Help button...
        Gtk::Button                        *m_Button_Help;

        // Close button...
        Gtk::Button                        *m_Button_Close;
};

// Multiple include protection...
#endif

