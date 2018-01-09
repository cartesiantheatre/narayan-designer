/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "PreferencesDialog.h"

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
    m_Settings(Settings),
    m_CheckButton_ShowSplash(nullptr),
    m_Button_Close(nullptr)
{
    // Find widgets...
    
        // Show splash check button...
        m_Builder->get_widget("CheckButton_ShowSplash", m_CheckButton_ShowSplash);
        g_assert(m_CheckButton_ShowSplash);
        
        // Close button...
        m_Builder->get_widget("Button_Close", m_Button_Close);
        g_assert(m_Button_Close);

    // Connect signals...
    m_Button_Close->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesDialog::OnCloseButton));
    
    // Bind settings to preference dialog's widgets...
    m_Settings->bind("show-splash", m_CheckButton_ShowSplash->property_active());
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

