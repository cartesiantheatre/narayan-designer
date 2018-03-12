/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "AboutDialog.h"
    #include "NarayanDesignerApplication.h"

    // Standard C++ / POSIX system headers...
    #include <vector>

    // Gdkmm...
    #include <gdkmm/pixbuf.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Constructor around Glade's already instantiated dialog...
AboutDialog::AboutDialog(
    BaseObjectType *CTypeObject, 
    const Glib::RefPtr<Gtk::Builder> &Builder)
 :  Gtk::AboutDialog(CTypeObject),
    m_Builder(Builder)
{
    // Set the program name...
    set_program_name(_("Narayan Designer"));
    
    // Set version...
    set_version(PACKAGE_VERSION);
    
    // Set copyright...
    set_copyright(COPYRIGHT_NOTICE);
    
    // Set comments...
    set_comments(_("A modelling tool for the Narayan simulation engine used in Avaneya."));
    
    // Set license type...
    set_license_type(Gtk::License::LICENSE_GPL_3_0);
    
    // Set website label and URL...
    set_website_label(_("Website"));
    set_website("https://www.cartesiantheatre.com");

    // Set contributors...

        // Testing...
        vector<Glib::ustring> Testers;
        Testers.push_back("Adam Gornowicz <adam@avaneya.com>");
        Testers.push_back("Joseph Liau <joseph@liau.ca>");
        add_credit_section(_("Testing"), Testers);

        // Created by...
        vector<Glib::ustring> CreatedBy;
        CreatedBy.push_back("Cartesian Theatre https://www.cartesiantheatre.com");
        add_credit_section(_("Created by"), CreatedBy);

        // Engineering...
        vector<Glib::ustring> Engineers;
        Engineers.push_back("Kip Warner <kip@thevertigo.com>");
        add_credit_section(_("Engineering"), Engineers);

        // Set artists...
        vector<Glib::ustring> Artists;
        Artists.push_back("Paul Laberge https://www.paullaberge.net");
        Artists.push_back("Simon Lazzari https://simonj-design.blogspot.ca/");
        set_artists(Artists);

        // Documenters...
        vector<Glib::ustring> Documenters;
        Documenters.push_back("Kip Warner <kip@thevertigo.com>");
        Documenters.push_back("Johann Tan <johanntan@ymail.com>");
        set_documenters(Documenters);

    // Translators: Put your name in this string, separating multiple names with
    //  \n character...
    set_translator_credits(_("translator-credits"));

    // Set the window icon...
    set_logo(Gdk::Pixbuf::create_from_resource(
        NARAYAN_DESIGNER_RESOURCE_ROOT "Artwork/AboutDialog.png"));

    // Connect signals...
    signal_response().connect(
        sigc::mem_fun(*this, &AboutDialog::OnActionResponse));
}

// An action widget was clicked...
void AboutDialog::OnActionResponse(int ResponseID)
{
    // Which action widget?
    switch(ResponseID)
    {
        // Delete or close events...
        case Gtk::RESPONSE_DELETE_EVENT:
        case Gtk::RESPONSE_CLOSE:
            
            // Hide the window...
            hide();
            break;
    }
}

