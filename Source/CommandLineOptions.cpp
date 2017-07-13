/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "CommandLineOptions.h"
    #include "Version.h"

    // Gtkmm...
    #include "gtkmm.h"

    // Standard C++ and POSIX system headers...
    #include <cassert>
    #include <iostream>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Default constructor...
CommandLineOptions::CommandLineOptions()
{

}

// Get the input file name only without path...
string CommandLineOptions::GetInputFileNameOnly() const
{
    // There should always be a file name already...
    assert(!m_InputFile.empty());
    
    // Make a copy of the complete input file name and path...
    string FileNameOnly = m_InputFile;
    
    // Strip the path so only file name remains...
    const size_t PathIndex = FileNameOnly.find_last_of("\\/");
    if(PathIndex != string::npos)
        FileNameOnly.erase(0, PathIndex + 1);

    // Done...
    return FileNameOnly;
}

// Parse command line options and continue execution if return true...
bool CommandLineOptions::Parse(
    const size_t ArgumentCount, char * const Arguments[])
{
    // Variables...
    int         OptionCharacter = '\x0';
    int         OptionIndex     = 0;
    std::string Token;

    // Command line option structure...
    option CommandLineLongOptions[] =
    {
        {"help",            no_argument,        nullptr,    option_long_help},
        {"verbose",         no_argument,        nullptr,    option_long_verbose},
        {"version",         no_argument,        nullptr,    option_long_version},

        // End of array marker...
        {nullptr, 0, nullptr, 0}
    };

    // Keep processing each option until there are none left...
    while((OptionCharacter = ::getopt_long(
        ArgumentCount, Arguments, "hVv", CommandLineLongOptions, &OptionIndex)) != -1)
    {
        // Which option?
        switch(OptionCharacter)
        {
            // Special case to set a flag, which we don't use...
            case 0:
            {
                /* If this option set a flag, do nothing else now. */
                if(CommandLineLongOptions[OptionIndex].flag != false)
                    break;

                // Done...
                cout << endl;
                break;
            }

            // Help...
            case 'h':
            case option_long_help:
            {
                // Show help...
                ShowHelp();

                // Exit...
                return false;
            }

            // Verbose...
            case 'V':
            case option_long_verbose: { m_Verbose = true; break; }

            // Version...
            case 'v':
            case option_long_version:
            {
                // Dump version information...
                ShowVersion();

                // Exit...
                return false;
            }

            // Unknown option...
            case '?':
            {
                // get_opt_long already dumped an error message...
                return false;
            }

            // Unknown option...
            default:
            {
                //cout << "Exiting on option " << (int) OptionCharacter << endl;

                // Exit...
                return false;
            }
        }
    }

    // We need at least one additional parameter, the input...

        // Fetch...
        if(optind + 1 <= static_cast<int>(ArgumentCount))
        {
            // Get the unnormalized path...
            const char *UnnormalizedPath = Arguments[optind++];
            
            // Get the system's maximum path length...
            #ifdef MAX_PATH
                /* Do nothing if already defined */
            #elif PATH_MAX
                #define MAX_PATH PATH_MAX
            #elif MAXPATHLEN
                #define MAX_PATH MAXPATHLEN
            #else
                #define MAX_PATH 4096
            #endif

            // In case the next call fails, exception handler will be able to
            //  display problematic input path...
            m_InputFile = UnnormalizedPath;

            // Try to normalize, throwing error if bad path...
            char NormalizedPath[MAX_PATH];
            if(!::realpath(UnnormalizedPath, NormalizedPath))
                throw runtime_error(::strerror(errno));
            
            // Save result...
            m_InputFile = NormalizedPath;
        }

        // Wasn't provided...
        else
            throw runtime_error(_("need input file, see man page"));

    // Check for extraneous arguments...
    if(optind + 1 <= static_cast<int>(ArgumentCount))
    {
        // Format error string...
        stringstream Error;
        Error
            << _("error: ")
            << _("unknown parameter: ")
            << optind + 1 << "/" << ArgumentCount
            << " ("
            << Arguments[optind] << _("), see man page") << endl;
        
        // Pass up the exception chain...
        throw runtime_error(Error.str());
    }

    // Parsing complete...
    return true;
}

// Show help...
void CommandLineOptions::ShowHelp() noexcept
{
    cout << _("Usage: ") << PACKAGE_NAME << " " << _("[options] [file]") << endl
         << _("See man page.\n\n")

         << _("Narayan Designer, a modelling tool for the Narayan simulation engine.\n")
         << _(COPYRIGHT_NOTICE) << endl << endl

         << _("Report bugs to: ") << NARAYAN_DESIGNER_BUGREPORT << endl;
}

// Show version information...
void CommandLineOptions::ShowVersion() noexcept
{
    // Application name and vendor copyright notice...
    cout << PACKAGE_NAME " " NARAYAN_DESIGNER_VERSION << endl
         << _(COPYRIGHT_NOTICE) << endl << endl;

    // Show build date...
    cout << _("Built on: ") << NARAYAN_DESIGNER_BUILD_DATE << endl << endl;

    // Relevant dependencies...
    cout << _("Compiled against:") << endl

         <<  "  Gtkmm "
            << GTKMM_MAJOR_VERSION << "."
            << GTKMM_MINOR_VERSION << "."
            << GTKMM_MICRO_VERSION << endl << endl;

    cout << _("Configured with: ") << CONFIGURATION_FLAGS << endl;
}

// Deconstructor...
CommandLineOptions::~CommandLineOptions()
{

}

