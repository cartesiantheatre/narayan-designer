/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "NarayanLogicLexer.h"

    // Standard C++ / POSIX system headers...
    #include <cstdlib>
    #include <iostream>
    #include <fstream>

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

    // Try to lex the input...
    try
    {
        // Verify that we were provided with a single argument to a script...
        if(ArgumentCount != 2)
            throw runtime_error(_("expected path to NarayanLogic script"));

        // Retrieve path...
        const string ScriptPath = Arguments[1];

        // Initialize lexer to sample NarayanLogic script...
        NarayanLogicLexer Lexer(ScriptPath);

        // Enable printing of tokens and matching value...
        Lexer.setPrint(true);

        // Keep reading tokens while there are some...
        while(const int Token = Lexer.lex())
        {
        }
        
        // We're done...
        return EXIT_SUCCESS;
    }

    // Something went wrong...
    catch(const runtime_error &Error)
    {
        // Show the error message...
        cerr << Error.what() << endl;

        // Bail...
        return EXIT_FAILURE;
    }
}

