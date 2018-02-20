#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
#

# Options for aclocal so it can find our custom M4 macros...
ACLOCAL_AMFLAGS = -I Macros

# Run the requested make target recursively on child makefiles...
SUBDIRS =                                                   \
    Source                                                  \
    Tests                                                   \
    Translations

# Preprocessor definitions to pass down to the compiler...
DEFS=
DEFS+= -DSYSCONFDIR='"$(sysconfdir)"' -DLOCALEDIR="\"$(localedir)\"" @DEFS@

# Locale directory...
localedir = $(datadir)/locale

# List of files to clean up during clean target...
CLEANFILES =                                                \
	Translations/*.gmo

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                            \
	_configs.sed                                            \
    $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.*

# Actually clean all derived and maintainer files...
MAINTAINERCLEANFILES =                                      \
	$(srcdir)/Auxiliary/config.h.in                         \
	$(srcdir)/Auxiliary/config.guess                        \
	$(srcdir)/Auxiliary/config.rpath                        \
	$(srcdir)/Auxiliary/config.sub                          \
	$(srcdir)/Auxiliary/depcomp                             \
	$(srcdir)/Auxiliary/install-sh                          \
	$(srcdir)/Auxiliary/missing                             \
	$(srcdir)/Translations/Makevars.template                \
	$(srcdir)/ABOUT-NLS                                     \
	$(srcdir)/aclocal.m4                                    \
	$(srcdir)/config.guess                                  \
	$(srcdir)/config.sub                                    \
	$(srcdir)/configure                                     \
	$(srcdir)/depcomp                                       \
	$(srcdir)/install-sh                                    \
	$(srcdir)/Makefile.in                                   \
	$(srcdir)/missing

# Miscellaneous data files...
dist_pkgdata_DATA =                                         \
    Authors                                                 \
    News                                                    \
    ReadMe

# System manual pages...
man1_MANS =                                                 \
    Manual/narayan-designer.man

# Magic for file(1)...
magicdir = $(datarootdir)/file/narayan/
magic_DATA = Data/magic

# Bash completion script...
bash_completiondir=$(datarootdir)/bash-completion/completions/
if USE_BASH_COMPLETION
bash_completion_DATA = Manual/narayan-designer
else
bash_completion_DATA =
endif

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                                                    \
    Data/com.cartesiantheatre.narayan-designer.desktop.in       \
    Data/com.cartesiantheatre.narayan-designer.gresource.xml    \
    Data/magic                                                  \
	Manual/narayan-designer                                     \
    Authors                                                     \
    ChangeLog                                                   \
    Copying                                                     \
    Install                                                     \
    News                                                        \
    ReadMe

# Make sure gettext is present...
check-gettext:
	@if test x$(USE_NLS) != "xyes" ; then echo "Missing gettext. Re-run configure and check for" \
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

# Update the machine dependent message catalogs...
update-gmo: check-gettext
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-gmo

# Update the list of files to translate in POTFILES.in and then update the .pot
#  message translation template file..
update-po: check-gettext
	@echo "Checking if POTFILES.in needs to be updated..."
	@cd $(srcdir) ; \
	find Data \( -iname "*.desktop.in" \) -print > Translations/POTFILES.in.2 ; \
	find Data \( -iname "*.gschema.xml" \) -print >> Translations/POTFILES.in.2 ; \
	find Data \( -iname "*.ui" \) -print >> Translations/POTFILES.in.2 ; \
	find Source \( -iname "*.lpp" -o -iname "*.ypp" \) -print >> Translations/POTFILES.in.2 ; \
	find Source \( -iname "*.cpp" -o -iname "*.cpp.in" \) -print >> Translations/POTFILES.in.2 ; \
	find Source \( -iname "*.h" -o -iname "*.h.in" -o -iname "*.ih" \) -print >> Translations/POTFILES.in.2 ; \
	$(SED) -i '/config.h$$/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/NarayanLogicLexerBase.cpp/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/NarayanLogicLexerBase.h/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/NarayanLogicParserBase.h/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/NarayanLogicParser.cpp/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/Version.h$$/d' Translations/POTFILES.in.2 ; \
	$(SORT) Translations/POTFILES.in.2 --output=Translations/POTFILES.in.2 ; \
	if diff Translations/POTFILES.in Translations/POTFILES.in.2 >/dev/null 2>&1 ; then \
		echo "No update to POTFILES.in required..." ; \
		$(RM) -f Translations/POTFILES.in.2 ; \
	else \
		echo "POTFILES.in updated..." ; \
		mv -v Translations/POTFILES.in.2 Translations/POTFILES.in ; \
	fi
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-po

# Targets which aren't actually files...
.PHONY: check-gettext force-update-gmo maintainer-clean-local update-gmo update-po

