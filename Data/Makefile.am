#
#   Narayan Designer, a modelling tool for the Narayan simulation engine.
#   Copyright (C) 2017 Cartesian Theatre. All rights reserved.
#

# Application data that should not be installed...
dist_noinst_DATA =                                      \
	com.cartesiantheatre.narayan-designer.desktop.in

# Location for desktop data...
desktopdir = $(datadir)/applications

# Desktop data includes desktop entry...
desktop_DATA = com.cartesiantheatre.narayan-designer.desktop

# GSettings schema...
gsettings_SCHEMAS = com.cartesiantheatre.narayan-designer.gschema.xml

# Standard prefix for icon themes...
iconthemedir = $(datadir)/icons/hicolor

# Subdirectories for application icon of varying dimensions...
appicon48dir = $(iconthemedir)/48x48/apps
appiconscalabledir = $(iconthemedir)/scalable/apps
appiconsymbolicdir = $(iconthemedir)/symbolic/apps
dist_appicon48_DATA = \
	Icons/48x48/com.cartesiantheatre.narayan-designer.png
dist_appiconscalable_DATA = \
	Icons/scalable/com.cartesiantheatre.narayan-designer.svg
dist_appiconsymbolic_DATA = \
	Icons/symbolic/com.cartesiantheatre.narayan-designer.svg

# Clean target removes these files...
CLEANFILES =                                                \
    $(desktop_DATA)                                         \
    com.cartesiantheatre.narayan-designer.desktop           \
    com.cartesiantheatre.narayan-designer.gresource.xml.d

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                                                \
    com.cartesiantheatre.narayan-designer.desktop.in        \
    com.cartesiantheatre.narayan-designer.gresource.xml     \
    $(gsettings_SCHEMAS)

# Command to run to update the desktop environment's icon cache...
UPDATE_ICON_CACHE = gtk-update-icon-cache --ignore-theme-index --force

# Insert GSettings compilation rules...
@GSETTINGS_RULES@

# During the install hook target, run the following...
install-data-hook: install-update-icon-cache

# During the uninstall hook target, run the following...
uninstall-hook: uninstall-update-icon-cache

# Update the icon cache during installation...
install-update-icon-cache:
	$(AM_V_at)$(POST_INSTALL)
	test -n "$(DESTDIR)" || $(UPDATE_ICON_CACHE) "$(iconthemedir)"

# Update the icon cache during uninstallation...
uninstall-update-icon-cache:
	$(AM_V_at)$(POST_UNINSTALL)
	test -n "$(DESTDIR)" || $(UPDATE_ICON_CACHE) "$(iconthemedir)"

# Generate a .desktop file from template and translation catalogue...
com.cartesiantheatre.narayan-designer.desktop: com.cartesiantheatre.narayan-designer.desktop.in
	$(AM_V_GEN)$(MSGFMT) --desktop --template $< -d $(top_srcdir)/Translations -o $@

# Generate dependency list for all resources by scanning GResource manifest file...
com.cartesiantheatre.narayan-designer.gresource.xml.d: com.cartesiantheatre.narayan-designer.gresource.xml
	$(AM_V_GEN) glib-compile-resources --sourcedir=$(srcdir) --generate-phony-targets --generate-dependencies --dependency-file=$@ $< > /dev/null 2>&1

