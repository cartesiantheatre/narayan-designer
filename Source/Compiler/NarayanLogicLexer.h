/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _NARAYAN_LOGIC_LEXER_H_
#define _NARAYAN_LOGIC_LEXER_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Lexer base class...
    #include "NarayanLogicLexerBase.h"

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// NarayanLogic lexer class...
class NarayanLogicLexer: public NarayanLogicLexerBase
{
    public:
        explicit NarayanLogicLexer(std::istream &in = std::cin,
                                std::ostream &out = std::cout);

        NarayanLogicLexer(std::string const &infile, std::string const &outfile);
        
        // $insert lexFunctionDecl
        int lex();

    private:
        int lex__();
        int executeAction__(size_t ruleNr);

        void print();
        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts

        void postCode(PostEnum__ type);    
                            // re-implement this function for code that must 
                            // be exec'ed after the rules's actions.
};

// $insert scannerConstructors
inline NarayanLogicLexer::NarayanLogicLexer(std::istream &in, std::ostream &out)
:
    NarayanLogicLexerBase(in, out)
{}

inline NarayanLogicLexer::NarayanLogicLexer(std::string const &infile, std::string const &outfile)
:
    NarayanLogicLexerBase(infile, outfile)
{}

// $insert inlineLexFunction
inline int NarayanLogicLexer::lex()
{
    return lex__();
}

inline void NarayanLogicLexer::preCode() 
{
    // optionally replace by your own code
}

inline void NarayanLogicLexer::postCode(PostEnum__ /*type*/) 
{
    // optionally replace by your own code
}

inline void NarayanLogicLexer::print() 
{
    print__();
}


#endif // NarayanLogicLexer_H_INCLUDED_

