/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "Compiler/NarayanLogicLexer.h"

    // Standard C++ / POSIX system headers...
    #include <cstdlib>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <vector>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Entry point...
int main()
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

    // Open sample script...
    ifstream InputStream("Scripts/GrowGrass.nl");

    // Output buffer for any tokens not understood...
    stringstream OutputStream;

    // Initialize lexer to sample NarayanLogic script...
    NarayanLogicLexer Lexer(InputStream, OutputStream);

    // Try to lex the input...
    try
    {
        // Keep reading tokens while there are some...
        while(const int Token = Lexer.lex())
        {
            // Fetch the token's value...
            const string &Value = Lexer.matched();

            //TokensRead.push_back(Token);
            cout << _("token: ") << Token << ": " << Value << endl;
        }
    }

    // Something went wrong...
    catch(const runtime_error &Error)
    {
        // Format the error message...
        stringstream ErrorMessage;
        ErrorMessage << Lexer.lineNr() << ": " << Error.what();

        // Show the error message...
        cerr << ErrorMessage.str() << endl;

        // Bail...
        return EXIT_FAILURE;
    }

    // If there were no errors, the output stream should have been empty...
    if(OutputStream.str().empty())
        return EXIT_SUCCESS;

    // Otherwise we have a problem...
    else
    {
        // Show an error message...
        cerr << _("error: unrecognized tokens: ") << OutputStream.str() << endl;

        // Bail...
        return EXIT_FAILURE;
    }
}

