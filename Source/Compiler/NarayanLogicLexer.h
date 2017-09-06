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

    // All the token definitions needed for print()...
    #include "NarayanLogicParserBase.h"

    // Standard C++ / POSIX system headers...
    #include <sstream>

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

        NarayanLogicLexer(std::string const &infile, std::string const &outfile = "-");
        
        // Retrieve the next token, or zero if there are no more...
        int lex();

        // Enable printing of token and matching value...
        void setPrint(const bool Enabled = true) { m_Print = Enabled; }

    private:
        int lex__();

        // Execute an action for a given matched rule...
        int executeAction__(size_t ruleNr);

        // Print the token...
        void print();

        // Executed before a pattern match starts...
        void preCode();

        // Executed after a rule's action is executed...
        void postCode(PostEnum__ type);

    // Protected attributes...
    protected:

        // Print token and matching value...
        bool    m_Print;
};

// $insert scannerConstructors
inline NarayanLogicLexer::NarayanLogicLexer(std::istream &in, std::ostream &out)
:
    NarayanLogicLexerBase(in, out),
    m_Print(false)
{}

inline NarayanLogicLexer::NarayanLogicLexer(std::string const &infile, std::string const &outfile)
:
    NarayanLogicLexerBase(infile, outfile),
    m_Print(false)
{}

// Retrieve the next token, or zero if there are no more...
inline int NarayanLogicLexer::lex()
{
    // Try to retrieve the next token...
    try
    {
        // Extract from stream...
        const auto Value = lex__();
        
        // Return it to parser...
        return Value;
    }
    
    // Something went wrong...
    catch(const std::runtime_error &Error)
    {
        // Prefix filename, line number, message, and offending text...
        std::stringstream BetterErrorMessage;
        BetterErrorMessage
            << filename() << ":"
            << lineNr() << ": "
            << Error.what() 
            << ": \'" << matched() << "\'";

        // Propagate exception up...
        throw std::runtime_error(BetterErrorMessage.str());
    }
}

// Executed before a pattern match starts...
inline void NarayanLogicLexer::preCode() 
{

}

// Executed after a rule's action is executed...
inline void NarayanLogicLexer::postCode(PostEnum__ /*type*/) 
{

}

// Print the token and matching text...
inline void NarayanLogicLexer::print() 
{
    // Not enabled, skip...
    if(not m_Print)
        return;

    // Storage for token identifier...
    std::string Token;

    // Convert the token symbolic identifier to a string because C++14 still
    //  can't do this at compile time in 2017...
    switch(d_token__)
    {
        case NarayanLogicParserBase::Tokens__::AGENT:                   Token = "AGENT "; break;
        case NarayanLogicParserBase::Tokens__::AGENT_OPTIONS:           Token = "AGENT_OPTIONS "; break;
        case NarayanLogicParserBase::Tokens__::APPLY_COUNT:             Token = "APPLY_COUNT"; break;
        case NarayanLogicParserBase::Tokens__::CREATE_UNIT:             Token = "CREATE_UNIT"; break;
        case NarayanLogicParserBase::Tokens__::DAY:                     Token = "DAY"; break;
        case NarayanLogicParserBase::Tokens__::EVENT_FAIL:              Token = "EVENT_FAIL"; break;
        case NarayanLogicParserBase::Tokens__::EVENT_SUCCESS:           Token = "EVENT_SUCCESS"; break;
        case NarayanLogicParserBase::Tokens__::EVENT_TYPE_ALERT:        Token = "EVENT_TYPE_ALERT"; break;
        case NarayanLogicParserBase::Tokens__::EVENT_TYPE_AUDIO:        Token = "EVENT_TYPE_AUDIO"; break;
        case NarayanLogicParserBase::Tokens__::EVENT_TYPE_EFFECT:       Token = "EVENT_TYPE_EFFECT"; break;
        case NarayanLogicParserBase::Tokens__::EXECUTE_RULE_ON_FAIL:    Token = "EXECUTE_RULE_ON_FAIL"; break;
        case NarayanLogicParserBase::Tokens__::IDENTIFIER:              Token = "IDENTIFIER"; break;
        case NarayanLogicParserBase::Tokens__::IN:                      Token = "IN"; break;
        case NarayanLogicParserBase::Tokens__::MAP:                     Token = "MAP"; break;
        case NarayanLogicParserBase::Tokens__::NUMBER:                  Token = "NUMBER"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_COUNT:            Token = "OPTION_COUNT"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_ID:               Token = "OPTION_ID"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_OR:               Token = "OPTION_OR"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_REPEAT_AFTER:     Token = "OPTION_REPEAT_AFTER"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_SEND_TO:          Token = "OPTION_SEND_TO"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_SWITCH_TO:        Token = "OPTION_SWITCH_TO"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_USING:            Token = "OPTION_USING"; break;
        case NarayanLogicParserBase::Tokens__::OPTION_VIA:              Token = "OPTION_VIA"; break;
        case NarayanLogicParserBase::Tokens__::OUT:                     Token = "OUT"; break;
        case NarayanLogicParserBase::Tokens__::RANDOM:                  Token = "RANDOM"; break;
        case NarayanLogicParserBase::Tokens__::RATE:                    Token = "RATE"; break;
        case NarayanLogicParserBase::Tokens__::RELATIONAL_GREATER_THAN: Token = "RELATIONAL_GREATER_THAN"; break;
        case NarayanLogicParserBase::Tokens__::RELATIONAL_IS:           Token = "RELATIONAL_IS"; break;
        case NarayanLogicParserBase::Tokens__::RELATIONAL_LESS_THAN:    Token = "RELATIONAL_LESS_THAN"; break;
        case NarayanLogicParserBase::Tokens__::RULE_END:                Token = "RULE_END"; break;
        case NarayanLogicParserBase::Tokens__::RULE_START_MAP:          Token = "RULE_START_MAP"; break;
        case NarayanLogicParserBase::Tokens__::RULE_START_UNIT:         Token = "RULE_START_UNIT"; break;
        case NarayanLogicParserBase::Tokens__::RULE_START_ZONE:         Token = "RULE_START_ZONE"; break;
        case NarayanLogicParserBase::Tokens__::SAMPLE:                  Token = "SAMPLE"; break;
        case NarayanLogicParserBase::Tokens__::SCOPE_GLOBAL:            Token = "SCOPE_GLOBAL"; break;
        case NarayanLogicParserBase::Tokens__::SCOPE_LOCAL:             Token = "SCOPE_LOCAL"; break;
        case NarayanLogicParserBase::Tokens__::SCOPE_MAP:               Token = "SCOPE_MAP"; break;
        case NarayanLogicParserBase::Tokens__::TEST:                    Token = "TEST"; break;
        case NarayanLogicParserBase::Tokens__::TIME_TRIGGER:            Token = "TIME_TRIGGER"; break;
        case NarayanLogicParserBase::Tokens__::UNARY:                   Token = "UNARY"; break;
        default:                                                        Token = "?"; break;
    }

    // Show the token identifier with the matching text...
    std::cout << lineNr() << ":" << Token << ":\'" << matched() << "\'" << std::endl;

    // Show the token numeric identifier and the matched text...
//    print__();
}


#endif // NarayanLogicLexer_H_INCLUDED_

