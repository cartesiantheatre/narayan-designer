/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanLogicParser.h"

    // Standard C++ / POSIX system headers...
    #include <cstdlib>
    #include <iostream>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Entry point...
int main(const int ArgumentCount, const char *Arguments[])
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

    // Try to parse the input...
    try
    {
        // Verify that we were provided with a single argument to a script...
        if(ArgumentCount != 2)
            throw runtime_error(_("expected path to NarayanLogic script"));

        // Retrieve path...
        const string ScriptPath = Arguments[1];

        // Initialize parser to sample NarayanLogic script...
        NarayanLogicParser Parser(ScriptPath);

        // Attempt to parse it and bail if unsuccessful...
        if(Parser.parse() != 0)
            return EXIT_FAILURE;
    }

    // Something went wrong...
    catch(const runtime_error &Error)
    {
        // Show the error message...
        cerr << Error.what() << endl;

        // Bail...
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

