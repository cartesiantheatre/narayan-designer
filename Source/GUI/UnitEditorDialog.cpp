/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "GUI/UnitEditorDialog.h"
    #include "Main/NarayanDesignerApplication.h"

    // i18n...
    #include "Main/gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Constructor around Glade's already instantiated dialog...
UnitEditorDialog::UnitEditorDialog(
    BaseObjectType *CTypeObject,
    const Glib::RefPtr<Gtk::Builder> &Builder)
 :  Gtk::Dialog(CTypeObject),
    m_Builder(Builder),
    m_Button_Close(nullptr)
{
    // Find widgets...
        
        // Documents notebook...
        m_Builder->get_widget("UnitEditorDialog_Button_Close", m_Button_Close);
        g_assert(m_Button_Close);
    
    // Connect signals...
    m_Button_Close->signal_clicked().connect(
        sigc::mem_fun(*this, &UnitEditorDialog::OnClose));
}

// Close button clicked...
void UnitEditorDialog::OnClose()
{
    // Hide the window...
    hide();
}

