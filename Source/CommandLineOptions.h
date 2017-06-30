/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _COMMAND_LINE_OPTIONS_H_
#define _COMMAND_LINE_OPTIONS_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "ExplicitSingleton.h"

    // GLibC option parsing...
    #include <getopt.h>

    // Standard C++ / POSIX system headers...
    #include <cstddef>
    #include <string>

// Command line options explicit singleton class...
class CommandLineOptions : public ExplicitSingleton<CommandLineOptions>
{
    // Because we are a singleton, only ExplicitSingleton can control our
    //  creation...
    friend class ExplicitSingleton<CommandLineOptions>;

    // Public methods...
    public:

        // Get the input file, if any...
        const std::string &GetInput() const noexcept { return m_InputFile; }

        // Get the input file name only without path...
        std::string GetInputFileNameOnly() const;

        // Get verbose mode flag...
        bool GetVerbose() const noexcept { return m_Verbose; }

        // Parse command line options and continue execution if return true...
        bool Parse(const size_t ArgumentCount, char * const Arguments[]);

        // Show help...
        void ShowHelp() noexcept;

        // Show version information...
        void ShowVersion() noexcept;

    // Private methods...
    private:

        // Default constructor...
        CommandLineOptions();

        // Deconstructor...
       ~CommandLineOptions();

    // Protected constants...
    protected:

        // Enumerator of long command line option identifiers...
        enum option_long_enum
        {
            option_long_help        = 256, /* Ensures no clashes with short option char identifiers */
            option_long_verbose,
            option_long_version
        };

    // Protected data...
    protected:

        // Input file...
        std::string     m_InputFile;

        // Verbose mode...
        bool            m_Verbose;
};

// Multiple include protection...
#endif

