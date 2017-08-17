#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# If unit tests were enabled, define a list of targets to create and test...
if ENABLE_TESTS

# Product list of programs to build during check target...
check_PROGRAMS =            \
    TestLexer

# Product list of scripts to generate during check target...
check_SCRIPTS =             \
    TestRuntimeSane

endif

# Test lexer program...
TestLexer_CFLAGS   = $(AM_CFLAGS)
TestLexer_SOURCES  = TestLexer.cpp
TestLexer_CPPFLAGS = -DSYSCONFDIR='"$(sysconfdir)"' -I$(top_srcdir)/Source -I$(top_builddir)/Source -I$(top_srcdir)/Source/Main $(AM_CPPFLAGS)
TestLexer_CXXFLAGS = $(AM_CXXFLAGS)
TestLexer_LDADD    = ../Source/Compiler/narayan_designer-NarayanLogicLexerBase.$(OBJEXT)

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                \
    GrowGrass.nl

# List of files to clean up during clean target...
CLEANFILES =                \
	$(check_SCRIPTS)        \
	$(check_PROGRAMS)

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Valgrind.sh
#endif

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS = $(check_SCRIPTS) $(check_PROGRAMS)

# Rule to create test script to verify the runtime works by just testing to see
#  it compiled and linked correctly...
TestRuntimeSane: Makefile.am
	@echo 'set -e -u' > $@
	@echo '$(top_builddir)/Source/narayan-designer --version | $(GREP) -q "@PACKAGE_NAME@"' >> $@
	@$(CHMOD) +x $@

