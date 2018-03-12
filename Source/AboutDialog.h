/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _ABOUT_DIALOG_H_
#define _ABOUT_DIALOG_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Gtkmm...
    #include <gtkmm/aboutdialog.h>
    #include <gtkmm/builder.h>

// About dialog...
class AboutDialog : public Gtk::AboutDialog
{
    // Public methods...
    public:
    
        // Constructor around Glade's already instantiated dialog...
        AboutDialog(
            BaseObjectType *CTypeObject,
            const Glib::RefPtr<Gtk::Builder> &Builder);

    // Protected methods...
    protected:

        // Signals...

            // Manually registered...

                // An action widget was clicked...
                void OnActionResponse(int ResponseID);

    // Protected attributes, classes, and enumerated types...
    protected:

        // Builder...
        Glib::RefPtr<Gtk::Builder>                  m_Builder;
};

// Multiple include protection...
#endif

