#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# Product list containing only narayan-designer to be destined for the binary
#  prefix...
bin_PROGRAMS = narayan-designer

# Product list of never installed libtool static convenience libraries...
noinst_LTLIBRARIES = liblexerparser.la

# Get build flags...
narayan_designer_CFLAGS     = $(AM_CFLAGS)
narayan_designer_CXXFLAGS   = $(AM_CXXFLAGS)
narayan_designer_LDFLAGS    = $(AM_LDFLAGS)
narayan_designer_LDADD      = $(AM_LDFLAGS) liblexerparser.la

# Preprocessor flags. Note that the include search paths are paired between
#  source and build directory as per Automake manual §8.7 to facilitate VPATH
#  builds...
narayan_designer_CPPFLAGS   =                   \
    -DSYSCONFDIR='"$(sysconfdir)"'              \
    -I$(srcdir)/                                \
    -I$(builddir)/                              \
    -I$(srcdir)/Compiler                        \
    -I$(builddir)/Compiler                      \
    -I$(srcdir)/Main                            \
    -I$(builddir)/Main                          \
    $(AM_CPPFLAGS)

# Source files for NarayanLogic lexer clobbered by each flexc++(1) invocation.
#  These should always be created within $(builddir)...
lexer_clobbered_source_files_only =             \
    NarayanLogicLexerBase.cpp                   \
    NarayanLogicLexerBase.h

lexer_clobbered_source_full_paths =             \
    Compiler/NarayanLogicLexerBase.cpp          \
    Compiler/NarayanLogicLexerBase.h

# Source files for NarayanLogic lexer generated once by flexc++(1), but
#  subsequently owned by the user. These should always be maintained within
#  $(sourcedir)...
lexer_unclobbered_source_files_only =           \
    NarayanLogicLexer.h                         \
    NarayanLogicLexer.ih

lexer_unclobbered_source_full_paths =           \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih

# Source files for NarayanLogic parser clobbered by each bisonc++(1) invocation.
#  These should always be created within $(builddir)...
parser_clobbered_source_files_only =            \
    NarayanLogicParserBase.h                    \
    NarayanLogicParser.cpp

parser_clobbered_source_full_paths =            \
    Compiler/NarayanLogicParserBase.h           \
    Compiler/NarayanLogicParser.cpp

# Source files for NarayanLogic parser generated once by bisonc++(1), but
#  subsequently owned by the user. These should always be maintained within
#  $(sourcedir)...
parser_unclobbered_source_files_only =          \
    NarayanLogicParser.h                        \
    NarayanLogicParser.ih

parser_unclobbered_source_full_paths =          \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih

# narayan-designer product option variables containing list of sources that need
#  to be compiled and linked to produce the product...
narayan_designer_SOURCES =                      \
    $(lexer_unclobbered_source_full_paths)      \
    $(parser_unclobbered_source_full_paths)     \
    Main/CommandLineOptions.cpp                 \
    Main/CommandLineOptions.h                   \
    Main/gettext.h                              \
    Main/Main.cpp                               \
    Patterns/ExplicitSingleton.h

# Both flexc++(1) and bisonc++(1) at the time of writing emit code that can
#  raise warnings, or even errors in the case of -Werror, when used with GCC 7
#  series compilers. I have submitted a number of patches to upstream with
#  varying degrees of success to address various issues. In the interim, the
#  best thing to do is to compartmentalize the necessary compilation flags for
#  code emitted by these two tools into a static libtool convenience library. 
#  This has the benefit of isolating the potential harm within the convenience
#  library that may have spilled over to other application code whenever
#  explicitly disabling useful safety measures, such as -Wall -Werror -Wshadow
#  -Wextra switches that raise issues to the emitted code's switch-case fall
#  through usage, unused variables, and so forth...
liblexerparser_la_SOURCES   =                   \
    $(lexer_clobbered_source_full_paths)        \
    $(parser_clobbered_source_full_paths)
liblexerparser_la_CXXFLAGS  = -Wimplicit-fallthrough=0 -Wno-unused-parameter
liblexerparser_la_CPPFLAGS  =                   \
    -DSYSCONFDIR='"$(sysconfdir)"'              \
    -I$(srcdir)/                                \
    -I$(builddir)/                              \
    -I$(srcdir)/Compiler                        \
    -I$(builddir)/Compiler                      \
    -I$(srcdir)/Main                            \
    -I$(builddir)/Main                          \
    $(AM_CPPFLAGS)

# These files must exist before anything is compiled. Can be machine
#  generated...
BUILT_SOURCES =                                 \
    Compiler/lexer.stamp                        \
    $(lexer_clobbered_source_full_paths)        \
    $(parser_clobbered_source_full_paths)       \
    Compiler/parser.stamp                       \
    Main/Version.h

# Product option variables for list of source not to be distributed because
#  they are machine generated...
#  Note: Migrated into libtool convenience library until upstream 
#  {flex,bison}c++(1) fix all reported issues...
#nodist_narayan_designer_SOURCES =               \
#    $(lexer_clobbered_source_full_paths)        \
#    $(parser_clobbered_source_full_paths)

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                \
    Compiler/lexer.stamp                        \
    Compiler/parser.stamp

CLEANFILES =                                    \
    Compiler/lexer.stamp                        \
    Compiler/parser.stamp                       \
    $(lexer_clobbered_source_full_paths)        \
    $(parser_clobbered_source_full_paths)

# Actually clean all derived and maintainer files...
MAINTAINERCLEANFILES =                          \
	$(srcdir)/Main/config.h.in

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                                    \
    Compiler/NarayanLogicLexer.lpp              \
    Compiler/NarayanLogicParser.ypp

# Extend silent mode for flexc++(1) inputs per Automake manual §21.3...
AX_V_FLEXCPP = $(AX_V_FLEXCPP_@AM_V@)
AX_V_FLEXCPP_ = $(AX_V_FLEXCPP_@AM_DEFAULT_V@)
AX_V_FLEXCPP_0 = @echo "  FLEXCPP  $(lexer_clobbered_source_full_paths)";

# Extend silent mode for bisonc++(1) inputs per Automake manual §21.3...
AX_V_BISONCPP = $(AX_V_BISONCPP_@AM_V@)
AX_V_BISONCPP_ = $(AX_V_BISONCPP_@AM_DEFAULT_V@)
AX_V_BISONCPP_0 = @echo "  BISONCPP $(parser_clobbered_source_full_paths)";

# Temporary directory to place flexc++(1) and bisonc++(1) generated files...
COMPILER_TMP=$(builddir)/Compiler/tmp

# Generate the Narayan Logic lexer source from its regular expression token
#  descriptions via flexc++, using that file as a witness. After that generate
#  a stamp target for the entire set of derived lexer files...
$(lexer_clobbered_source_full_paths): Compiler/lexer.stamp
Compiler/lexer.stamp: Compiler/NarayanLogicLexer.lpp Compiler/parser.stamp
	@$(MKDIR_P) $(COMPILER_TMP)
	$(AX_V_FLEXCPP)$(FLEXCPP) --target-directory=$(COMPILER_TMP) $<
	@for lexer_file in $(lexer_clobbered_source_files_only); do \
		mv $(COMPILER_TMP)/$$lexer_file Compiler/; \
	done
	@rm -Rf $(COMPILER_TMP)
	@echo "timestamp for $^" > $@

# Generate the Narayan Logic parser source from its Backus-Naur grammar rules
#  via bisonc++, using that file as a witness. After that generate a stamp 
#  target for the entire set of derived lexer files...
$(parser_clobbered_source_full_paths): Compiler/parser.stamp
Compiler/parser.stamp: Compiler/NarayanLogicParser.ypp
	@$(MKDIR_P) $(COMPILER_TMP)
	$(AX_V_BISONCPP)$(BISONCPP) --target-directory=$(COMPILER_TMP) $<
	@for parser_file in $(parser_clobbered_source_files_only); do \
		mv $(COMPILER_TMP)/$$parser_file Compiler/; \
	done
	@rm -Rf $(COMPILER_TMP)
	@echo "timestamp for $^" > $@

