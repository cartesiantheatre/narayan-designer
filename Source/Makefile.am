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
narayan_designer_CPPFLAGS   = -DSYSCONFDIR='"$(sysconfdir)"' -I$(srcdir)/ -I$(srcdir)/Compiler -I$(srcdir)/Main $(AM_CPPFLAGS)
narayan_designer_LDFLAGS    = $(AM_LDFLAGS)
narayan_designer_LDADD      = $(AM_LDFLAGS)

# These files must exist before anything is compiled. Can be machine
#  generated...
BUILT_SOURCES =                                 \
    Compiler/lexer.stamp                        \
    Compiler/parser.stamp                       \
    Main/Version.h

# narayan-designer product option variables containing list of sources...
narayan_designer_SOURCES =                      \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih               \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih              \
    Compiler/NarayanLogicParserPreinclude.h     \
    Main/CommandLineOptions.cpp                 \
    Main/CommandLineOptions.h                   \
    Main/gettext.h                              \
    Main/Main.cpp                               \
    Patterns/ExplicitSingleton.h

# Source files for NarayanLogic lexer clobbered by each flexc++(1) invocation...
lexer_clobbered_source =                        \
    Compiler/NarayanLogicLexerBase.cpp          \
    Compiler/NarayanLogicLexerBase.h

# Source files for NarayanLogic parser clobbered by each bisonc++(1)
#  invocation...
parser_clobbered_source =                       \
    Compiler/NarayanLogicParserBase.h           \
    Compiler/NarayanLogicParser.cpp

# Product option variables for list of source not to be distributed because
#  they are machine generated...
nodist_narayan_designer_SOURCES =               \
    $(lexer_clobbered_source)                   \
    $(parser_clobbered_source)

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                \
    Compiler/lexer.stamp                        \
    Compiler/parser.stamp                       \
    $(lexer_clobbered_source)                   \
    $(parser_clobbered_source)

# Actually clean all derived and maintainer files...
MAINTAINERCLEANFILES =                          \
	$(srcdir)/Main/config.h.in                  \
    $(lexer_clobbered_source)                   \
    $(parser_clobbered_source)

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
	$(AX_V_FLEXCPP)$(FLEXCPP) --target-directory=Compiler $<
	@echo "timestamp for $^" > $@

# Generate the Narayan Logic parser source from its Backus-Naur grammar rules
#  via bisonc++, using that file as a witness. After that generate a stamp 
#  target for the entire set of derived lexer files...
$(parser_clobbered_source): Compiler/parser.stamp
Compiler/parser.stamp: Compiler/NarayanLogicParser.ypp
	@$(RM) -vf $(parser_clobbered_source)
	$(AX_V_BISONCPP)$(BISONCPP) --target-directory=Compiler $<
	@echo "timestamp for $^" > $@

