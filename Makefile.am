#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# Options for aclocal so it can find our custom M4 macros...
ACLOCAL_AMFLAGS = -I Macros

# Run the requested make target on the sub-projects...
SUBDIRS = Translations

# Product list containing only narayan-designer to be destined for the binary
#  prefix...
bin_PROGRAMS = narayan-designer

# Get build flags...
narayan_designer_CFLAGS     = $(AM_CFLAGS)
narayan_designer_CXXFLAGS   = $(AM_CXXFLAGS)
narayan_designer_CPPFLAGS   = -DSYSCONFDIR='"$(sysconfdir)"' -I$(srcdir)/Source $(AM_CPPFLAGS)
narayan_designer_LDFLAGS    = $(AM_LDFLAGS)
narayan_designer_LDADD      = $(AM_LDFLAGS)

# Preprocessor definitions to pass down to the compiler...
DEFS=
DEFS+= -DSYSCONFDIR='"$(sysconfdir)"' -DLOCALEDIR="\"$(localedir)\"" @DEFS@

# Locale directory...
localedir = $(datadir)/locale

# These files must exist before anything is compiled. Can be machine generated...
BUILT_SOURCES =                                 \
    Source/NarayanLogicLexerBase.h              \
    Source/NarayanLogicLexer.h                  \
    Source/NarayanLogicLexer.ih                 \
    Source/NarayanLogicLexerBase.cpp            \
    Source/NarayanLogicParserBase.h             \
    Source/NarayanLogicParser.h                 \
    Source/NarayanLogicParser.ih                \
    Source/NarayanLogicParser.cpp               \
    Source/Version.h
#    Tests/...

# narayan-designer product option variables containing list of sources...
narayan_designer_SOURCES =                      \
    Source/CommandLineOptions.cpp               \
    Source/CommandLineOptions.h                 \
    Source/ExplicitSingleton.h                  \
    Source/gettext.h                            \
    Source/Main.cpp                             \
    Source/NarayanLogicLexerBase.h              \
    Source/NarayanLogicLexer.h                  \
    Source/NarayanLogicLexer.ih                 \
    Source/NarayanLogicLexerBase.cpp            \
    Source/NarayanLogicParserBase.h             \
    Source/NarayanLogicParser.h                 \
    Source/NarayanLogicParser.ih                \
    Source/NarayanLogicParser.cpp               \
    Source/NarayanLogicParserPreinclude.h

# List of files to clean up during clean target...
CLEANFILES =                                    \
    Source/NarayanLogicLexerBase.h              \
    Source/NarayanLogicLexer.h                  \
    Source/NarayanLogicLexer.ih                 \
    Source/NarayanLogicLexerBase.cpp            \
    Source/NarayanLogicParserBase.h             \
    Source/NarayanLogicParser.h                 \
    Source/NarayanLogicParser.ih                \
    Source/NarayanLogicParser.cpp               \
	Tests/Runtime_Sane.sh                       \
	Translations/*.gmo

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES = \
	_configs.sed \
    $(top_builddir)/$(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.*

# Actually clean all derived and maintainer files...
MAINTAINERCLEANFILES =                          \
	$(srcdir)/Auxiliary/config.h.in             \
	$(srcdir)/Auxiliary/config.guess            \
	$(srcdir)/Auxiliary/config.rpath            \
	$(srcdir)/Auxiliary/config.sub              \
	$(srcdir)/Auxiliary/depcomp                 \
	$(srcdir)/Auxiliary/install-sh              \
	$(srcdir)/Auxiliary/missing                 \
	$(srcdir)/Translations/Makevars.template    \
	$(srcdir)/ABOUT-NLS                         \
	$(srcdir)/aclocal.m4                        \
	$(srcdir)/Source/config.h.in                \
	$(srcdir)/config.guess                      \
	$(srcdir)/config.sub                        \
	$(srcdir)/configure                         \
	$(srcdir)/depcomp                           \
	$(srcdir)/install-sh                        \
	$(srcdir)/Makefile.in                       \
	$(srcdir)/missing

# Miscellaneous data files...
dist_pkgdata_DATA =                             \
    Authors                                     \
    News                                        \
    ReadMe

# System manual pages...
man1_MANS =                                     \
    $(top_builddir)/Manual/narayan-designer.man

# Bash completion script...
bash_completiondir=$(datarootdir)/bash-completion/completions/
if USE_BASH_COMPLETION
bash_completion_DATA = Manual/narayan-designer
else
bash_completion_DATA =
endif

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                                    \
	Manual/narayan-designer                     \
    Source/NarayanLogicLexer.lpp                \
    Source/NarayanLogicParser.ypp               \
    Authors                                     \
    ChangeLog                                   \
    Copying                                     \
    Install                                     \
    News                                        \
    ReadMe
    # Tests/...

# Product list of scripts to generate during check target...
check_SCRIPTS =                                 \
    Tests/Runtime_Sane.sh

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Tests/Valgrind.sh
#endif

# Extend silent mode for flexc++(1) inputs per Automake manual §21.3...
AX_V_FLEXCPP = $(AX_V_FLEXCPP_@AM_V@)
AX_V_FLEXCPP_ = $(AX_V_FLEXCPP_@AM_DEFAULT_V@)
AX_V_FLEXCPP_0 = @echo "  FLEXCPP  $@";

# Extend silent mode for bisonc++(1) inputs per Automake manual §21.3...
AX_V_BISONCPP = $(AX_V_BISONCPP_@AM_V@)
AX_V_BISONCPP_ = $(AX_V_BISONCPP_@AM_DEFAULT_V@)
AX_V_BISONCPP_0 = @echo "  BISONCPP $@";

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS = $(check_SCRIPTS)

# Make sure gettext is present...
check-gettext:
	@if test x$(USE_NLS) != "xyes" ; then echo "Missing gettext. Rerun configure and check for" \
	"'checking whether to use NLS... yes'!" ; exit 1 ; fi

# Force an update to the machine dependent message catalogs...
force-update-gmo: check-gettext
	find Translations/ -type f -name "*.po" -execdir touch {} \;
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-gmo

# Before we prepare a distribution, run this hook...
dist-hook:
	$(RM) -r `find $(distdir) -name .git`
	$(RM) -r `find $(distdir) -name .hg`
	$(RM) -r `find $(distdir) -name .svn`

# Maintainer clean local hook to remove Autotools configuration output files...
maintainer-clean-local:
	$(RM) -r '$(srcdir)/Auxiliary'

# Generate the Narayan Logic lexer source from its regular expression token
#  descriptions via flexc++, using that file as a witness...
Source/NarayanLogicLexerBase.h Source/NarayanLogicLexer.h Source/NarayanLogicLexer.ih: Source/NarayanLogicLexerBase.cpp
Source/NarayanLogicLexerBase.cpp: Source/NarayanLogicLexer.lpp
	$(AX_V_FLEXCPP)$(FLEXCPP) --target-directory=$(top_builddir)/Source $< ; \
	$(SED) -i '/#include "NarayanLogicLexer.ih"/a #include "NarayanLogicParserBase.h" \/\/ Added manually...' $(top_builddir)/Source/NarayanLogicLexerBase.cpp

# Generate the Narayan Logic parser source from its Backus-Naur grammar rules
#  via bisonc++, using that file as a witness...
Source/NarayanLogicParserBase.h Source/NarayanLogicParser.h Source/NarayanLogicParser.ih: Source/NarayanLogicParser.cpp
Source/NarayanLogicParser.cpp: Source/NarayanLogicParser.ypp
	$(AX_V_BISONCPP)$(BISONCPP) --thread-safe --target-directory=$(top_builddir)/Source $<

# Rule to create test script to verify the runtime works by just testing to see
#  it compiled and linked correctly...
Tests/Runtime_Sane.sh: Makefile.am
	@$(MKDIR_P) $(top_builddir)/Tests
	@echo 'set -e -u' > $@
	@echo './narayan-designer --version | $(GREP) -q "@PACKAGE_NAME@"' >> $@
	@$(CHMOD) +x $@

# Update the machine dependent message catalogs...
update-gmo: check-gettext
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-gmo

# Create the .pot message translation template file..
update-po: check-gettext
	find $(srcdir)/ -iname "*.cpp" -print | sort > $(srcdir)/Translations/POTFILES.in.2 ; \
	find $(srcdir)/ -iname "*.cpp.in" -print | sort >> $(srcdir)/Translations/POTFILES.in.2 ; \
	find $(srcdir)/ \( -iname "*.h" ! -name config.h ! -name Version.h \) -print | sort >> $(srcdir)/Translations/POTFILES.in.2 ; \
	find $(srcdir)/ -iname "*.h.in" -print | sort >> $(srcdir)/Translations/POTFILES.in.2 ; \
	if diff $(srcdir)/Translations/POTFILES.in $(srcdir)/Translations/POTFILES.in.2 >/dev/null 2>&1 ; then \
		$(RM) -f $(srcdir)/Translations/POTFILES.in.2 ; \
	else \
		mv $(srcdir)/Translations/POTFILES.in.2 $(srcdir)/Translations/POTFILES.in ; \
	fi
#	sed --in-place $(srcdir)/Translations/$(PACKAGE).pot --expression=s/CHARSET/UTF-8/ # CHARSET warning hack
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-po

# Targets which aren't actually files...
.PHONY: check-gettext force-update-gmo maintainer-clean-local update-gmo update-po

