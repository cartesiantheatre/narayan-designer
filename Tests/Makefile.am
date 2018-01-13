#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
#

# If unit tests were enabled, define a list of targets to create and test...
if ENABLE_TESTS

# TODO: Add some tests incorporating tools from gettext-lint package...

# Product list of programs to build during check target...
check_PROGRAMS =                            \
    TestLexer                               \
    TestParser

# Product list of scripts to generate during check target, including pattern
#  matching stems...
check_SCRIPTS =                             \
    TestDesktopFileValidate                 \
    TestRuntimeSane                         \
    Rules/Unit/CreateAlloy.nl               \
    Rules/Zone/DevelopHouses.nl             \
    Rules/Unit/GoToWork.nl                  \
    Rules/Map/GrowGrass.nl                  \
    Rules/Unit/MustardFactory.nl            \
    Rules/Unit/ProducePower.nl

# List of tests expected to fail...
#XFAIL_TESTS =

# These files must exist before anything is compiled. Can be machine
#  generated...
BUILT_SOURCES = TestNarayanLogic

endif

# Custom test runner for NarayanLogic scripts per Automake §15.2.3...
TEST_EXTENSIONS = .nl
NL_LOG_COMPILER  = $(top_builddir)/Tests/TestNarayanLogic

# Preprocessor flags for all tests. Note that the include search paths are
#  paired between source and build directory as per Automake §8.7 to facilitate
#  VPATH builds...
AM_CPPFLAGS =                               \
    -DSYSCONFDIR='"$(sysconfdir)"'          \
    -I$(top_srcdir)/Source                  \
    -I$(top_builddir)/Source                \
    -I$(top_srcdir)/Source/Compiler         \
    -I$(top_builddir)/Source/Compiler       \
    -I$(top_srcdir)/Source/Main             \
    -I$(top_builddir)/Source/Main

# Libraries to add for all tests. For some reason Automake doesn't have an
#  AM_LDADD, so we use LDADD per Automake §8.1.2...
LDADD = $(top_builddir)/Source/liblexerparser.la

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
EXTRA_DIST =                                \
    Rules/Unit/CreateAlloy.nl               \
    Rules/Zone/DevelopHouses.nl             \
    Rules/Unit/GoToWork.nl                  \
    Rules/Map/GrowGrass.nl                  \
    Rules/Unit/MustardFactory.nl            \
    Rules/Unit/ProducePower.nl

# List of files to clean up during clean target...
CLEANFILES =                                \
	$(check_SCRIPTS)                        \
	$(check_PROGRAMS)                       \
	TestNarayanLogic

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Valgrind.sh
#endif

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS = $(check_SCRIPTS)

# Test script to validate our desktop file entry...
TestDesktopFileValidate: Makefile.am $(top_builddir)/Data/com.cartesiantheatre.narayan-designer.desktop
	@echo 'set -e -u' > $@
	@echo 'echo "$$(DESKTOP_FILE_VALIDATE) $$(top_builddir)/$$(desktop_DATA) || exit 1"' >> $@
	@$(CHMOD) +x $@

# This script is used as a test harness for each Narayan Logic script to test.
#  It runs the latter through both the lexer and parser to verify successful
#  consumption...
TestNarayanLogic: TestLexer TestParser
	@echo 'set -e -u' > $@
	@echo 'echo "./TestLexer $$1"' >> $@
	@echo './TestLexer "$$1"' >> $@
	@echo 'echo "./TestParser $$1"' >> $@
	@echo './TestParser "$$1"' >> $@
	@$(CHMOD) +x $@

# Test script to verify the runtime works by just testing to see it compiled and
#  linked correctly...
TestRuntimeSane: Makefile.am
	@echo 'set -e -u' > $@
	@echo 'GSETTINGS_SCHEMA_DIR=$(top_builddir)/Data $(top_builddir)/Source/narayan-designer --version | $(GREP) -q "@PACKAGE_NAME@"' >> $@
	@$(CHMOD) +x $@

