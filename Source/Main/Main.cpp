/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanDesignerApplication.h"

    // Glibmm...
    #include <glibmm/miscutils.h>

    // Standard C++ / POSIX system headers...
    #include <cstdlib>
    #include <iostream>
    #include <stdexcept>
    
    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Fatal error occured. Display the message and return the system exit code for
//  failure...
template <typename ErrorType>
int FatalError(const ErrorType &Error);

// Entry point...
int main(int ArgumentCount, char *Arguments[])
{
    // Initialize i18n if configured with native language support...

        // Select user's preferred locale according to environment variable and
        //  check for error...
        if(!::setlocale(LC_ALL, ""))
        {
            // Alert and abort...
            cerr << "error: failed to set user locale" << endl;
            return EXIT_FAILURE;
        }

    #if ENABLE_NLS

        // Set the current message domain and check for error...
        if(!::textdomain(PACKAGE))
        {
            // Alert and abort...
            cerr << "error: failed to set text domain ("
                 << ::strerror(errno) << ")" << endl;
            return EXIT_FAILURE;
        }

    #endif

    // This environment variable can be set to the name of a directory that is
    //  considered in addition to the glib-2.0/schemas subdirectories of the XDG
    //  system data dirs when looking for compiled schemas for GSettings. Since
    //  we may be running this application from a location other than where it
    //  was configured to be installed, we should set it...
    Glib::setenv("GSETTINGS_SCHEMA_DIR", ".", false);

    // Try to run the application...
    try
    {
        // Create an instance of the main application class...
        auto ApplicationInstance = NarayanDesignerApplication::create();
        
        // Start the main event loop which will begin by showing the initial
        //  window and responding to user events. Control returns when the last
        //  window is closed...
        return ApplicationInstance->run(ArgumentCount, Arguments);
    }

        // Runtime general error...
        catch(const runtime_error &Error)
        {
            // Exit with failure condition...
            return FatalError(Error);
        }

        // Some kind of unhandled Glib exception...
        catch(const Glib::Exception &Error)
        {
            // Exit with failure condition...
            return FatalError(Error);
        }

    // Done...
    return EXIT_SUCCESS;
}

// Fatal error occured. Display the message and return the system exit code for
//  failure...
template <typename ExceptionType>
int FatalError(const ExceptionType &Error)
{
    // Get the error string...
    const string ErrorMessage = Error.what();

    // Show error message...
    cerr << Error.what() << endl;

    // Exit with failure condition...
    return EXIT_FAILURE;
}

