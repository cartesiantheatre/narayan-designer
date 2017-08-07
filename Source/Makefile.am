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
narayan_designer_CPPFLAGS   = -DSYSCONFDIR='"$(sysconfdir)"' -I$(srcdir)/ -I$(srcdir)/Compiler $(AM_CPPFLAGS)
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
    Compiler/NarayanLogicParserPreinclude.h     \
    Main/CommandLineOptions.cpp                 \
    Main/CommandLineOptions.h                   \
    Main/gettext.h                              \
    Main/Main.cpp                               \
    Patterns/ExplicitSingleton.h

# Product option variables for list of source not to be distributed because
#  they are machine generated...
nodist_narayan_designer_SOURCES =               \
    Compiler/NarayanLogicLexerBase.cpp          \
    Compiler/NarayanLogicLexerBase.h            \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih               \
    Compiler/NarayanLogicParserBase.h           \
    Compiler/NarayanLogicParser.cpp             \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                \
    Compiler/NarayanLogicLexerBase.cpp          \
    Compiler/NarayanLogicLexerBase.h            \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih               \
    Compiler/NarayanLogicParserBase.h           \
    Compiler/NarayanLogicParser.cpp             \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih

# Actually clean all derived and maintainer files...
MAINTAINERCLEANFILES =                          \
	$(srcdir)/Main/config.h.in                  \
    Compiler/NarayanLogicLexerBase.cpp          \
    Compiler/NarayanLogicLexerBase.h            \
    Compiler/NarayanLogicLexer.h                \
    Compiler/NarayanLogicLexer.ih               \
    Compiler/NarayanLogicParserBase.h           \
    Compiler/NarayanLogicParser.cpp             \
    Compiler/NarayanLogicParser.h               \
    Compiler/NarayanLogicParser.ih

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
Compiler/NarayanLogicLexerBase.cpp Compiler/NarayanLogicLexerBase.h Compiler/NarayanLogicLexer.h Compiler/NarayanLogicLexer.ih: Compiler/lexer.stamp
Compiler/lexer.stamp: Compiler/NarayanLogicLexer.lpp
	$(AX_V_FLEXCPP)$(FLEXCPP) --target-directory=Compiler $<
	@echo "timestamp for $^" > $@

# Generate the Narayan Logic parser source from its Backus-Naur grammar rules
#  via bisonc++, using that file as a witness. After that generate a stamp 
#  target for the entire set of derived lexer files...
Compiler/NarayanLogicParser.cpp Compiler/NarayanLogicParserBase.h Compiler/NarayanLogicParser.h Compiler/NarayanLogicParser.ih: Compiler/parser.stamp
Compiler/parser.stamp: Compiler/NarayanLogicParser.ypp
	$(AX_V_BISONCPP)$(BISONCPP) --target-directory=Compiler $<
	@echo "timestamp for $^" > $@

