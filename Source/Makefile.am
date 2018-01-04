#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
#

# Product list containing only narayan-designer to be destined for the binary
#  prefix...
bin_PROGRAMS = narayan-designer

# Product list of never installed libtool static convenience libraries...
noinst_LTLIBRARIES = liblexerparser.la

# Application data that should not be installed...
dist_noinst_DATA =                                              \
	$(top_srcdir)/Data/com.cartesiantheatre.narayan-designer.desktop.in

# Location for desktop data...
desktopdir = $(datadir)/applications

# Desktop data includes desktop entry...
desktop_DATA = $(top_builddir)/Data/com.cartesiantheatre.narayan-designer.desktop

# There isn't any way I know of to add glib-compile-resources(1) dynamically
#  generated dependency rules at build time in a portable manner. Every example
#  I can find incorporates its output into the generated source's target
#  dependency list via a non-portable $(shell ) construct. For the time being,
#  just manually list the contents referenced in the ...gsettings.xml file...
GRESOURCE_LIST =                                                                \
    $(top_srcdir)/Data/Icons/48x48/com.cartesiantheatre.narayan-designer.png    \
    $(top_srcdir)/Data/MainWindow.ui                                            \
    $(top_srcdir)/Data/Menus.ui                                                 \
    $(top_srcdir)/Data/PreferencesDialog.ui

# GSettings schema. Note that for some reason the expansion of the
#  GLIB_GSETTINGS macro seems to know to find this within the srcdir and not
#  builddir. If we explicitly prefix with the 
#  $(top_srcdir)/Data/com.cartesiantheatre..., though technically more correct,
#  then the gschema.valid stamp ends up getting placed in the srcdir which
#  defeats the purpose of remote builds. I'm not sure if this was intentional
#  behaviour on the part of the GLIB_GSETTINGS macro author...
gsettings_SCHEMAS = ../Data/com.cartesiantheatre.narayan-designer.gschema.xml

# Standard prefix for icon themes...
iconthemedir = $(datadir)/icons/hicolor

# Subdirectories for application icon of varying dimensions...
appicon48dir = $(iconthemedir)/48x48/apps
appiconscalabledir = $(iconthemedir)/scalable/apps
appiconsymbolicdir = $(iconthemedir)/symbolic/apps
dist_appicon48_DATA =                                                               \
	$(top_srcdir)/Data/Icons/48x48/com.cartesiantheatre.narayan-designer.png
dist_appiconscalable_DATA =                                                         \
	$(top_srcdir)/Data/Icons/scalable/com.cartesiantheatre.narayan-designer.svg
dist_appiconsymbolic_DATA =                                                         \
	$(top_srcdir)/Data/Icons/symbolic/com.cartesiantheatre.narayan-designer.svg

# Command to run to update the desktop environment's icon cache...
UPDATE_ICON_CACHE = gtk-update-icon-cache --ignore-theme-index --force

# Get build flags...
narayan_designer_CFLAGS     = $(AM_CFLAGS)
narayan_designer_CXXFLAGS   = $(AM_CXXFLAGS)
narayan_designer_LDFLAGS    = $(AM_LDFLAGS)
narayan_designer_LDADD      = $(AM_LDFLAGS) liblexerparser.la

# Preprocessor flags. Note that the include search paths are paired between
#  source and build directory as per Automake manual §8.7 to facilitate VPATH
#  builds...
narayan_designer_CPPFLAGS   =                                                       \
    -DSYSCONFDIR='"$(sysconfdir)"'                                                  \
    -I$(srcdir)/                                                                    \
    -I$(builddir)/                                                                  \
    -I$(srcdir)/Compiler                                                            \
    -I$(builddir)/Compiler                                                          \
    -I$(srcdir)/GUI                                                                 \
    -I$(builddir)/GUI                                                               \
    -I$(srcdir)/Main                                                                \
    -I$(builddir)/Main                                                              \
    $(AM_CPPFLAGS)

# Source files for NarayanLogic lexer clobbered by each flexc++(1) invocation.
#  These should always be created within $(builddir)...
lexer_clobbered_source_files_only =                                                 \
    NarayanLogicLexerBase.cpp                                                       \
    NarayanLogicLexerBase.h

lexer_clobbered_source_full_paths =                                                 \
    Compiler/NarayanLogicLexerBase.cpp                                              \
    Compiler/NarayanLogicLexerBase.h

# Source files for NarayanLogic lexer generated once by flexc++(1), but
#  subsequently owned by the user. These should always be maintained within
#  $(sourcedir)...
lexer_unclobbered_source_files_only =                                               \
    NarayanLogicLexer.h                                                             \
    NarayanLogicLexer.ih

lexer_unclobbered_source_full_paths =                                               \
    Compiler/NarayanLogicLexer.h                                                    \
    Compiler/NarayanLogicLexer.ih

# Source files for NarayanLogic parser clobbered by each bisonc++(1) invocation.
#  These should always be created within $(builddir)...
parser_clobbered_source_files_only =                                                \
    NarayanLogicParserBase.h                                                        \
    NarayanLogicParser.cpp

parser_clobbered_source_full_paths =                                                \
    Compiler/NarayanLogicParserBase.h                                               \
    Compiler/NarayanLogicParser.cpp

# Source files for NarayanLogic parser generated once by bisonc++(1), but
#  subsequently owned by the user. These should always be maintained within
#  $(sourcedir)...
parser_unclobbered_source_files_only =                                              \
    NarayanLogicParser.h                                                            \
    NarayanLogicParser.ih

parser_unclobbered_source_full_paths =                                              \
    Compiler/NarayanLogicParser.h                                                   \
    Compiler/NarayanLogicParser.ih

# narayan-designer product option variables containing list of sources that need
#  to be compiled and linked to produce the product...
narayan_designer_SOURCES =                                                          \
    $(lexer_unclobbered_source_full_paths)                                          \
    $(parser_unclobbered_source_full_paths)                                         \
    GUI/MainWindow.cpp                                                              \
    GUI/MainWindow.h                                                                \
    GUI/PreferencesDialog.cpp                                                       \
    GUI/PreferencesDialog.h                                                         \
    Main/gettext.h                                                                  \
    Main/Main.cpp                                                                   \
    Main/NarayanDesignerApplication.cpp                                             \
    Main/NarayanDesignerApplication.h                                               \
    Patterns/ExplicitSingleton.h

# Don't redistribute the resources files which are large and generated by
#  glib-compile-resources(1)...
nodist_narayan_designer_SOURCES =                                                   \
    Main/Resources.cpp                                                              \
    Main/Resources.h

# Both flexc++(1) and bisonc++(1) at the time of writing emit code that can
#  raise warnings, or even errors in the case of -Werror, when used with GCC 7
#  series compilers. I have submitted a number of patches to upstream with
#  varying degrees of success to address various issues. In the interim, the
#  best thing to do is to compartmentalize the necessary compilation flags for
#  code emitted by these two tools into a static libtool convenience library. 
#  This has the benefit of isolating the potential harm within the convenience
#  library that may have spilled over to other application code whenever
#  explicitly disabling useful safety measures, such as -Wall -Werror -Wshadow
#  -Wextra switches that raise issues like switch-case fall throughs, unused
#  variables, and so forth...
liblexerparser_la_SOURCES   =                                                       \
    $(lexer_clobbered_source_full_paths)                                            \
    $(parser_clobbered_source_full_paths)
liblexerparser_la_CXXFLAGS  = -Wimplicit-fallthrough=0 -Wno-unused-parameter
liblexerparser_la_CPPFLAGS  =                                                       \
    -DSYSCONFDIR='"$(sysconfdir)"'                                                  \
    -I$(srcdir)/                                                                    \
    -I$(builddir)/                                                                  \
    -I$(srcdir)/Compiler                                                            \
    -I$(builddir)/Compiler                                                          \
    -I$(srcdir)/Main                                                                \
    -I$(builddir)/Main                                                              \
    $(AM_CPPFLAGS)

# These files must exist before anything is compiled. Can be machine
#  generated...
BUILT_SOURCES =                                                                     \
    Compiler/lexer.stamp                                                            \
    $(lexer_clobbered_source_full_paths)                                            \
    $(parser_clobbered_source_full_paths)                                           \
    Compiler/parser.stamp                                                           \
    Main/Resources.cpp                                                              \
    Main/Resources.h                                                                \
    Main/Version.h

# Product option variables for list of source not to be distributed because
#  they are machine generated...
#  Note: Migrated into libtool convenience library until upstream 
#  {flex,bison}c++(1) fix all reported issues...
#nodist_narayan_designer_SOURCES =                              \
#    $(lexer_clobbered_source_full_paths)                       \
#    $(parser_clobbered_source_full_paths)

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                                                    \
    Compiler/lexer.stamp                                                            \
    Compiler/parser.stamp                                                           \
    Main/Resources.cpp                                                              \
    Main/Resources.h

# Additional files to remove when running vanilla clean target...
CLEANFILES =                                                                        \
    Compiler/lexer.stamp                                                            \
    $(lexer_clobbered_source_full_paths)                                            \
    $(parser_clobbered_source_full_paths)                                           \
    Compiler/parser.stamp                                                           \
    Main/Resources.cpp                                                              \
    Main/Resources.h                                                                \
    $(desktop_DATA)

# Actually clean all derived and maintainer files...
MAINTAINERCLEANFILES =                                                              \
	$(srcdir)/Main/config.h.in

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                                                                        \
    Compiler/NarayanLogicLexer.lpp                                                  \
    Compiler/NarayanLogicParser.ypp                                                 \
    $(top_srcdir)/Data/com.cartesiantheatre.narayan-designer.desktop.in             \
    $(top_srcdir)/Data/com.cartesiantheatre.narayan-designer.gresource.xml          \
    $(GRESOURCE_LIST)                                                               \
    $(gsettings_SCHEMAS)

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

# Generate a .desktop file from template and translation catalogue...
$(top_builddir)/Data/com.cartesiantheatre.narayan-designer.desktop: $(top_srcdir)/Data/com.cartesiantheatre.narayan-designer.desktop.in
	@$(MKDIR_P) $(@D)
	$(AM_V_GEN)$(MSGFMT) --desktop --template $< -d $(top_srcdir)/Translations -o $@

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

# Insert GSettings compilation rules...
@GSETTINGS_RULES@

# During the install hook target, run the following...
install-data-hook: install-update-icon-cache

# Update the icon cache during installation...
install-update-icon-cache:
	$(AM_V_at)$(POST_INSTALL)
	test -n "$(DESTDIR)" || $(UPDATE_ICON_CACHE) "$(iconthemedir)"

# All user interface related data files compiled into C++ code via
#  glib-compile-resources(1). Create the source and header file...
Main/Resources.cpp Main/Resources.h: $(top_srcdir)/Data/com.cartesiantheatre.narayan-designer.gresource.xml $(GRESOURCE_LIST)
	$(AM_V_GEN) glib-compile-resources --target=$@ --sourcedir=$(top_srcdir)/Data --generate --c-name narayan_designer $<

# During the uninstall hook target, run the following...
uninstall-hook: uninstall-update-icon-cache

# Update the icon cache during uninstallation...
uninstall-update-icon-cache:
	$(AM_V_at)$(POST_UNINSTALL)
	test -n "$(DESTDIR)" || $(UPDATE_ICON_CACHE) "$(iconthemedir)"

