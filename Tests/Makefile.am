#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# List of files to clean up during clean target...
CLEANFILES =        \
	Runtime_Sane.sh

# Manually add these things to distribution package when dist target is run...
#EXTRA_DIST =       \
    # Tests/...

# Product list of scripts to generate during check target...
# TODO: Migrate all of this into Tests/Makefile.am and study David's EasyTAG
#       logic.
check_SCRIPTS =     \
    Runtime_Sane.sh

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Valgrind.sh
#endif

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS = $(check_SCRIPTS)

# Rule to create test script to verify the runtime works by just testing to see
#  it compiled and linked correctly...
Runtime_Sane.sh: Makefile.am
	@$(MKDIR_P) Tests
	@echo 'set -e -u' > $@
	@echo '$(top_builddir)/Source/narayan-designer --version | $(GREP) -q "@PACKAGE_NAME@"' >> $@
	@$(CHMOD) +x $@

