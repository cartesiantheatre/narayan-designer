/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _NARAYAN_LOGIC_PARSER_H_
#define _NARAYAN_LOGIC_PARSER_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Parser base class...
    #include "NarayanLogicParserBase.h"

    // CAVEAT: between the baseclass-include directive and the 
    // #undef directive in the previous line references to NarayanLogicParser 
    // are read as NarayanLogicParserBase.
    // If you need to include additional headers in this file 
    // you should do so after these comment-lines.
    #undef NarayanLogicParser

    // Lexer user class...
    #include "NarayanLogicLexer.h"

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// NarayanLogic parser class...
class NarayanLogicParser: public NarayanLogicParserBase
{
    // Public methods...
    public:

        // Default constructor expecting input from stdin...
        NarayanLogicParser() = default;

        // Constructor expecting path to input file...
        NarayanLogicParser(const std::string &InputFile);

        // Parse input...
        int parse();

    // Private methods...
    private:

        // Called on syntax errors...
        void error();

        // Returns the next token from the lexical scanner...
        int lex();

        void print();                   // use, e.g., d_token, d_loc

        // Semantic error raised an exception during a semantic action...
        void exceptionHandler(std::exception const &exc);

    // support functions for parse():
        void executeAction__(int ruleNr);
        void errorRecovery__();
        void nextCycle__();
        void nextToken__();
        void print__();

    // Protected attributes...
    protected:

        // Lexer...
        NarayanLogicLexer   d_scanner;
};


#endif
