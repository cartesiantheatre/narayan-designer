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

        // Enable throwing of exceptions...
        #define CL_HPP_ENABLE_EXCEPTIONS

        // Target version 1.2 since at this time hardly anything supports
        //  anything version 2 and up...
        #define CL_HPP_TARGET_OPENCL_VERSION 120
        #define CL_HPP_MINIMUM_OPENCL_VERSION 120

        // Wrapper...
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

    // GtkSourceViewMM...
    #include <gtksourceviewmm.h>
    #include <gtksourceviewmm/styleschemechooserwidget.h>

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
        
        // Check if any usable hardware was detected...
        bool IsAnyDeviceUsable() const { return m_AnyDeviceUsable; }

    // Protected methods...
    protected:

        // Clear the devices list and information widget...
        void ClearDevices();

        // Find a widget and bind it to a particular setting...
        template <typename WidgetType>
        void FindAndBindActiveProperty(
            const std::string &WidgetName,
            WidgetType &&WidgetObject,
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

                // Copy device info button clicked...
                void OnCopyDeviceInfo();

                // Colour scheme cursor changed in tree view...
                void OnEditorColourSchemeChanged();

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
                
                // Column to use for string IDs, the name column. This is a
                //  Gtkmm construct and not to be confused with the numeric
                //  OpenCL hardware ID...
                static constexpr size_t             m_StringIDColumn =  3;
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
                    add(m_Column_Vendor);
                    add(m_Column_MaxComputeUnits);
                    add(m_Column_GlobalMemory);
                    add(m_Column_MaxClockFrequency);
                    add(m_Column_MaxAllocatableMemory);
                    add(m_Column_LocalMemory);
                    add(m_Column_Available);
                    add(m_Column_Extensions);
                }
                
                // Columns...
                Gtk::TreeModelColumn<std::string>   m_Column_Name;
                /*
                    These should be using OpenCL types like cl_uint, 
                    cl_device_type, etc., but there appears to be a bug in GCC
                    7.2 which emits a false positive error regarding ignored
                    template parameter attributes being ignored.
                    
                    <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=84055>
                */
                Gtk::TreeModelColumn<unsigned long> m_Column_Type;
                Gtk::TreeModelColumn<std::string>   m_Column_Vendor;
                Gtk::TreeModelColumn<unsigned int>  m_Column_MaxComputeUnits;
                Gtk::TreeModelColumn<unsigned long> m_Column_GlobalMemory;
                Gtk::TreeModelColumn<unsigned int>  m_Column_MaxClockFrequency;
                Gtk::TreeModelColumn<unsigned long> m_Column_MaxAllocatableMemory;
                Gtk::TreeModelColumn<unsigned long> m_Column_LocalMemory;
                Gtk::TreeModelColumn<bool>          m_Column_Available;
                Gtk::TreeModelColumn<std::string>   m_Column_Extensions;
        };

        // Notebook tab ordinals...
        enum
        {
            Tab_General = 0,
            Tab_Editor,
            Tab_Hardware
        };

        // True if we managed to detect at least one usable device...
        bool                                        m_AnyDeviceUsable;

        // Builder...
        Glib::RefPtr<Gtk::Builder>                  m_Builder;

        // Settings

            // Preferences notebook...
            Gtk::Notebook                          *m_Notebook_Preferences;
        
            // Backend...
            Glib::RefPtr<Gio::Settings>             m_Settings;
            

        // General tab...

            // Show startup splash check button...
            Gtk::CheckButton                       *m_CheckButton_General_StartupShowSplash;
            
            // Show startup usage tips check button...
            Gtk::CheckButton                       *m_CheckButton_General_StartupShowUsageTips;
            
            // Play sound effects check button...
            Gtk::CheckButton                       *m_CheckButton_General_PlaySoundEffects;
        
        // Editor tab...
            
            // Use system monospace font...
            Gtk::CheckButton                       *m_CheckButton_Editor_UseSystemDefaultMonospaceFont;
            
            // Custom font to use...
            Gtk::FontButton                        *m_FontButton_Editor_CustomFont;
            
            // Use dark theme variant, if available...
            Gtk::CheckButton                       *m_CheckButton_Editor_UseDarkTheme;
            
            // Style scheme chooser...
            Gsv::StyleSchemeChooserWidget          *m_StyleSchemeChooserWidget_Editor;
        
        // Hardware tab...

            // Platform combobox text, tree columns definition, and the actual
            //  ListStore for the storage each row...
            Gtk::ComboBoxText                      *m_ComboBoxText_Hardware_Platform;
            HardwarePlatformTreeColumns             m_TreeColumns_Hardware_Platform;
            Glib::RefPtr<Gtk::ListStore>            m_ListStore_Hardware_Platform;

            // Platform labels...
            Gtk::Label                             *m_Label_Hardware_Platform_Profile;
            Gtk::Label                             *m_Label_Hardware_Platform_Version;
            Gtk::Label                             *m_Label_Hardware_Platform_Vendor;

            // Device combobox text, tree columns definition, the ListStore for
            //  the storage of the rows, and a custom cell renderer...
            Gtk::ComboBoxText                      *m_ComboBoxText_Hardware_Devices;
            HardwareDevicesTreeColumns              m_TreeColumns_Hardware_Devices;
            Glib::RefPtr<Gtk::ListStore>            m_ListStore_Hardware_Devices;
            Gtk::CellRendererText                   m_CellRendererText_Hardware_Devices_Type;

            // Device textview and default text...
            Gtk::TextView                          *m_TextView_Hardware_DeviceInfo;
            const std::string                       m_Hardware_DeviceInfo_DefaultText;

            // Copy device info button...
            Gtk::Button                            *m_Button_DeviceInfo_Copy;

            // Refresh hardware button...
            Gtk::Button                            *m_Button_Hardware_Refresh;

        // Help button...
        Gtk::Button                                *m_Button_Help;

        // Close button...
        Gtk::Button                                *m_Button_Close;
};

// Multiple include protection...
#endif

