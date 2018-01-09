/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Gtkmm...
    #include <gtkmm/applicationwindow.h>
    #include <gtkmm/builder.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Main window...
class MainWindow : public Gtk::ApplicationWindow
{
    // Public methods...
    public:
    
        // Constructor around already Glade instantiated window...
        MainWindow(
            BaseObjectType *CTypeObject,
            const Glib::RefPtr<Gtk::Builder> &Builder);

        // Deconstructor...
        virtual ~MainWindow();

    // Protected methods...
    protected:
        
        // Signals...

            // Overridden defaults...
        
                // Window is being closed...
                bool on_delete_event(GdkEventAny *Event) override;

            // Manually registered...

                // Actions...
                void OnActionShowLog();

    // Protected attributes...
    protected:

        // Gtk::Builder...
        Glib::RefPtr<Gtk::Builder>  m_Builder;
};

// Multiple include protection...
#endif

