#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# If unit tests were enabled, define a list of targets to create and test...
if ENABLE_TESTS

# Product list of programs to build during check target...
check_PROGRAMS =            \
    TestLexer               \
    TestParser

# Product list of scripts to generate during check target...
check_SCRIPTS =             \
    TestRuntimeSane         \
    TestLexer_1             \
    TestParser_1

endif

# Preprocessor flags for all tests. Note that the include search paths are
#  paired between source and build directory as per Automake §8.7 to facilitate
#  VPATH builds...
AM_CPPFLAGS =                           \
    -DSYSCONFDIR='"$(sysconfdir)"'      \
    -I$(top_srcdir)/Source              \
    -I$(top_builddir)/Source            \
    -I$(top_srcdir)/Source/Compiler     \
    -I$(top_builddir)/Source/Compiler   \
    -I$(top_srcdir)/Source/Main         \
    -I$(top_builddir)/Source/Main

# Libraries to add for all tests. For some reason Automake doesn't have an
#  AM_LDADD, so we use LDADD per Automake §8.1.2...
LDADD =                                                                                 \
    $(top_builddir)/Source/Compiler/narayan_designer-NarayanLogicLexerBase.$(OBJEXT)    \
    $(top_builddir)/Source/Compiler/narayan_designer-NarayanLogicParser.$(OBJEXT)

# Test lexer program...
TestLexer_CFLAGS    = $(AM_CFLAGS)
TestLexer_SOURCES   = TestLexer.cpp
TestLexer_CPPFLAGS  = $(AM_CPPFLAGS)
TestLexer_CXXFLAGS  = $(AM_CXXFLAGS)
TestLexer_LDADD     = $(LDADD)

# Test parser program...
TestParser_CFLAGS   = $(AM_CFLAGS)
TestParser_SOURCES  = TestParser.cpp
TestParser_CPPFLAGS = $(AM_CPPFLAGS)
TestParser_CXXFLAGS = $(AM_CXXFLAGS)
TestParser_LDADD    = $(LDADD)

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                \
    Scripts/GrowGrass.nl

# List of files to clean up during clean target...
CLEANFILES =                \
	$(check_SCRIPTS)        \
	$(check_PROGRAMS)

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Valgrind.sh
#endif

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS = $(check_SCRIPTS)

TestLexer_1: TestLexer $(srcdir)/Scripts/GrowGrass.nl Makefile.am
	@echo 'set -e -u' > $@
	@echo './$< "$(srcdir)/Scripts/GrowGrass.nl"' >> $@
	@$(CHMOD) +x $@

TestParser_1: TestParser $(srcdir)/Scripts/GrowGrass.nl Makefile.am
	@echo 'set -e -u' > $@
	@echo './$< "$(srcdir)/Scripts/GrowGrass.nl"' >> $@
	@$(CHMOD) +x $@

# Rule to create test script to verify the runtime works by just testing to see
#  it compiled and linked correctly...
TestRuntimeSane: Makefile.am
	@echo 'set -e -u' > $@
	@echo '$(top_builddir)/Source/narayan-designer --version | $(GREP) -q "@PACKAGE_NAME@"' >> $@
	@$(CHMOD) +x $@

