#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# Product list containing only narayan-designer to be destined for the binary
#  prefix...
bin_PROGRAMS = narayan-designer

# Get build flags...
narayan_designer_CFLAGS     = $(AM_CFLAGS)
narayan_designer_CXXFLAGS   = $(AM_CXXFLAGS)
narayan_designer_LDFLAGS    = $(AM_LDFLAGS)
narayan_designer_LDADD      = $(AM_LDFLAGS)

# Preprocessor flags. Note that the include search paths are paired between
#  source and build directory as per Automake manual §8.7 to facilitate VPATH
#  builds...
narayan_designer_CPPFLAGS   =       \
    -DSYSCONFDIR='"$(sysconfdir)"'  \
    -I$(srcdir)/                    \
    -I$(builddir)/                  \
    -I$(srcdir)/Compiler            \
    -I$(builddir)/Compiler          \
    -I$(srcdir)/Main                \
    -I$(builddir)/Main              \
    $(AM_CPPFLAGS)

# narayan-designer product option variables containing list of sources...
narayan_designer_SOURCES =                      \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih               \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih              \
    Main/CommandLineOptions.cpp                 \
    Main/CommandLineOptions.h                   \
    Main/gettext.h                              \
    Main/Main.cpp                               \
    Patterns/ExplicitSingleton.h

# Source files for NarayanLogic lexer clobbered by each flexc++(1) invocation.
#  These should always be created within $(builddir)...
lexer_clobbered_source =                        \
    Compiler/NarayanLogicLexerBase.cpp          \
    Compiler/NarayanLogicLexerBase.h

# Source files for NarayanLogic lexer generated once by flexc++(1), but
#  subsequently owned by the user. These should always be maintained within
#  $(sourcedir)...
lexer_unclobbered_source =                      \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih

# Source files for NarayanLogic parser clobbered by each bisonc++(1) invocation.
#  These should always be created within $(builddir)...
parser_clobbered_source =                       \
    Compiler/NarayanLogicParserBase.h           \
    Compiler/NarayanLogicParser.cpp

# Source files for NarayanLogic parser generated once by bisonc++(1), but
#  subsequently owned by the user. These should always be maintained within
#  $(sourcedir)...
parser_unclobbered_source =                     \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih

# These files must exist before anything is compiled. Can be machine
#  generated...
BUILT_SOURCES =                                 \
    Compiler/lexer.stamp                        \
    $(lexer_clobbered_source)                   \
    $(parser_clobbered_source)                  \
    Compiler/parser.stamp                       \
    Main/Version.h

# Product option variables for list of source not to be distributed because
#  they are machine generated...
nodist_narayan_designer_SOURCES =               \
    $(lexer_clobbered_source)                   \
    $(parser_clobbered_source)

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                \
    Compiler/lexer.stamp                        \
    Compiler/parser.stamp

CLEANFILES =                                    \
    Compiler/lexer.stamp                        \
    Compiler/parser.stamp                       \
    $(lexer_clobbered_source)                   \
    $(parser_clobbered_source)

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
AX_V_FLEXCPP_0 = @echo "  FLEXCPP  $@";

# Extend silent mode for bisonc++(1) inputs per Automake manual §21.3...
AX_V_BISONCPP = $(AX_V_BISONCPP_@AM_V@)
AX_V_BISONCPP_ = $(AX_V_BISONCPP_@AM_DEFAULT_V@)
AX_V_BISONCPP_0 = @echo "  BISONCPP $@";

# Generate the Narayan Logic lexer source from its regular expression token
#  descriptions via flexc++, using that file as a witness. After that generate
#  a stamp target for the entire set of derived lexer files...
$(lexer_clobbered_source): Compiler/lexer.stamp
Compiler/lexer.stamp: Compiler/NarayanLogicLexer.lpp
	@$(RM) -vf $(lexer_clobbered_source)
	$(AX_V_FLEXCPP)$(FLEXCPP) --target-directory=Compiler $< && $(RM) -f $(lexer_unclobbered_source)
	@echo "timestamp for $^" > $@

# Generate the Narayan Logic parser source from its Backus-Naur grammar rules
#  via bisonc++, using that file as a witness. After that generate a stamp 
#  target for the entire set of derived lexer files...
$(parser_clobbered_source): Compiler/parser.stamp
Compiler/parser.stamp: Compiler/NarayanLogicParser.ypp
	@$(RM) -vf $(parser_clobbered_source)
	$(AX_V_BISONCPP)$(BISONCPP) --target-directory=Compiler $< && $(RM) -f $(parser_unclobbered_source)
	@echo "timestamp for $^" > $@

