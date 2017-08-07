/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "CommandLineOptions.h"

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

// Entry point...
int main(int ArgumentCount, char * const Arguments[])
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

    // Try to compile Narayan simulation rule script...
    try
    {
        // Explicit instantiation of several subsystem singletons. Order can
        //  matter...
        CommandLineOptions::CreateSingleton();

        // Get a shortcut to the options singleton...
        CommandLineOptions &Options = CommandLineOptions::GetInstance();

        // Parse command line and user configuration, continuing if non-fatal
        //  error...
        if(!Options.Parse(ArgumentCount, Arguments))
            return EXIT_FAILURE;
    }

        // Runtime error...
        catch(const std::runtime_error &Error)
        {
            // Get the error string...
            const string ErrorMessage = Error.what();

            // Show error message...
            cerr << Error.what() << endl;

            // Exit with failure condition...
            return EXIT_FAILURE;
        }

    // Done...
    return EXIT_SUCCESS;
}

