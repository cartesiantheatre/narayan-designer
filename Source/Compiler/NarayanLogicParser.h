/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _NARAYAN_LOGIC_PARSER_H_
#define _NARAYAN_LOGIC_PARSER_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Parser base class...
    #include "NarayanLogicParserBase.h"
    
    // Lexer user class...
    #include "NarayanLogicLexer.h"

    // Standard C++ / POSIX system headers...
    #include <cmath>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

#undef NarayanLogicParser
    // CAVEAT: between the baseclass-include directive and the 
    // #undef directive in the previous line references to NarayanLogicParser 
    // are read as NarayanLogicParserBase.
    // If you need to include additional headers in this file 
    // you should do so after these comment-lines.


class NarayanLogicParser: public NarayanLogicParserBase
{
    // $insert scannerobject
    NarayanLogicLexer d_scanner;
        
    public:
        NarayanLogicParser() = default;
        int parse();

    private:
        void error();                   // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc
        void exceptionHandler(std::exception const &exc);

    // support functions for parse():
        void executeAction__(int ruleNr);
        void errorRecovery__();
        void nextCycle__();
        void nextToken__();
        void print__();
};


#endif
