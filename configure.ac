# Narayan Designer, a modelling tool for the Narayan simulation engine.
# Copyright (C) 2017 Cartesian Theatre™. All rights reserved.

# Minimum version of Autoconf used to successfully process configure.ac...
AC_PREREQ([2.67])

# Initialize Autoconf...
AC_INIT(
    [narayan-designer],
    [0.0.0],
    [Cartesian Theatre <info@cartesiantheatre.com>],
    [narayan-designer],
    [https://www.cartesiantheatre.com])

# Clear default C / C++ compiler flags. Otherwise -g -O2 is automatically set
#  for the GNU C++ by AC_PROG_CC and AC_PROG_CXXCPP. Can still be overridden by
#  user. This needs to be right here after AC_INIT or these variables will get
#  clobbered...
: ${CFLAGS=""}
: ${CXXFLAGS=""}

# Location to find auxiliary automake scripts...
AC_CONFIG_AUX_DIR([Auxiliary])

# Location to find Autoconf plugins...
AC_CONFIG_MACRO_DIR([Macros])

# Preserve all arguments for products that want them into config.h...
config_flags="$0 $*"
AC_DEFINE_UNQUOTED(
    [CONFIGURATION_FLAGS],
    ["$config_flags"],
    [All flags that were passed to configure at configuration time.])

# Store build date stamp...
package_build_date=$(date --rfc-2822)
AC_DEFINE_UNQUOTED(
    [PACKAGE_BUILD_DATE],
    ["$package_build_date"],
    [Date and time this package was built.])
AC_SUBST([PACKAGE_BUILD_DATE], [$package_build_date])

# Copyright notice...
copyright_notice="Copyright (C) 2017 Cartesian Theatre™. All rights reserved."
AC_COPYRIGHT([$copyright_notice])
AC_DEFINE_UNQUOTED(
    [COPYRIGHT_NOTICE],
    ["$copyright_notice"],
    [Upstream vendor's copyright notice.])
AC_SUBST([COPYRIGHT_NOTICE], [$copyright_notice])

# Initialize Automake...

    # Setup flags...
    AM_INIT_AUTOMAKE([color-tests dist-bzip2 no-dist-gzip silent-rules \
        subdir-objects tar-pax -Wall -Werror foreign])

    # Set by default to use silent build rules...
    AM_SILENT_RULES([yes])

# Prepare canonical values for the platform we are compiling on and the platform
#  to host the generated files on...
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Sanity check to ensure generated ./configure script knows the directory on
#  which it is being executed is actually the project directory by providing any
#  unique source file...
AC_CONFIG_SRCDIR([Source/Main.cpp])

# Configure config.h...

    # Location to generate headers from templates containing Autoconf
    #  substitution variables...
    AC_CONFIG_HEADERS([Source/config.h])

# Check for command-line options...

    # Bash completion...
    AC_ARG_ENABLE([bash-completion],
        [AS_HELP_STRING([--enable-bash-completion],
            [enable bash completion @<:@default: yes@:>@])], # Quadrigraph escaped
        [enable_bash_completion=${enableval}],
        [enable_bash_completion=yes])
    AM_CONDITIONAL(USE_BASH_COMPLETION, [test x"$enable_bash_completion" = xyes])

# Initialize i18n from GNU gettext...
AM_GNU_GETTEXT_VERSION([0.19.8])
AM_GNU_GETTEXT([external], [need-ngettext])

# Make sure we are not being run as root...
if test $UID == 0; then
   AC_MSG_ERROR([there is never a good reason to run this script as root..."])
fi

# Make sure paths are sane...

    # Alert user...
    AC_MSG_NOTICE([checking paths are sane...])

    # Build directory must not contain spaces...
    if echo $PWD | grep -E ' ' >/dev/null ; then
        AC_MSG_ERROR([your build path must not contain spaces...])
    fi

    # Source directory must not contain spaces...
    if echo $srcdir | grep -E ' ' >/dev/null ; then
        AC_MSG_ERROR([your source path must not contain spaces...])
    fi

# Checks for programs needed to build everything and perform unit tests...

    # Bison C++ parser generator...
    AX_PROG_BISONCPP([5.02])

    # chmod...
    AC_PATH_PROG([CHMOD], [chmod])

    # C++14 compiler with strict conformance required...
    AC_PROG_CXX
    AX_CXX_COMPILE_STDCXX_14([noext],[mandatory])

    # C++ preprocessor...
    AC_PROG_CXXCPP

    # Flex C++ lexer generator...
    AX_PROG_FLEXCPP([2.05])

    # Grep required for test suite...
    AC_PROG_GREP

    # Install utility to copy files and set attributes...
    AC_PROG_INSTALL

    # mkdir -p functionality required in several places...
    AC_PROG_MKDIR_P

    # mktemp tool required to perform test suite...
    AC_PATH_PROG([MKTEMP], [mktemp])
    if test "x$MKTEMP" = "x"; then
        AC_MSG_ERROR([mktemp tool is required to perform test suite...])
    fi

    # Sed tool...
    AC_PROG_SED

    # rmdir necessary in various places...
    AC_PATH_PROG([RMDIR], [rmdir])
    if test "x$RMDIR" = "x"; then
        AC_MSG_ERROR([rmdir required, but unavailable...])
    fi

    # Valgrind optional, but used in unit testing if enabled by default...
    AX_VALGRIND_CHECK
    if test "x$enable_valgrind" = "xyes" && test "$VALGRIND" = ""; then
        AC_MSG_ERROR([valgrind required to perform test suite, but not found; either install or reconfigure with --disable-valgrind])
    fi

# Select our native language of C++ to perform tests in, unless we specify
#  otherwise later...
AC_LANG([C++])

# Substitute autoconfig macros in various non-make related files...

    # System manual...
    AC_CONFIG_FILES([Manual/narayan-designer.man])

    # Update version string...
    AC_CONFIG_FILES([Source/Version.h])

# Checks for system headers and features...

    # SIMD extensions...
    case "$host_cpu" in
        i?86) ;&
        x86_64) CXXFLAGS="$CXXFLAGS -mfpmath=sse -msse -msse2" ;;
    esac

    # Check for amd64 or i386 like architecture to use software traps...
    case "$host_cpu" in
        arm*) AC_DEFINE([BREAKPOINT_TRAP], [{ asm volatile("bkpt"); }], [Trigger a software trap...]) ;;
        i?86) ;&
        x86_64) AC_DEFINE([BREAKPOINT_TRAP], [{ asm volatile("int $0x03"); }], [Trigger a software trap...]) ;;
    esac

    # Standard C++ headers...
    AC_CHECK_HEADERS(
        [cassert cerrno cstddef cctype iostream stdexcept memory],
        [], [AC_MSG_ERROR([missing some required standard C++ headers...])])

    # POSIX headers for all sub-projects...
    AC_LANG_PUSH([C])
    AC_CHECK_HEADERS([getopt.h unistd.h], [],
        [AC_MSG_ERROR([missing a required POSIX header...])])
    AC_LANG_POP([C])

    # Locates pkg-config tool on system, checks compatibility, verifies sane...
    PKG_PROG_PKG_CONFIG([0.25])

    # Bash completion requested...
    if test "x${enable_bash_completion}" = xyes; then

        # Initialize path for bash completion scripts to be installed to...
        bash_completiondir=$sysconfdir/bash_completion.d
        AC_SUBST(bash_completiondir)

    fi

# Check for headers and libraries...

    # Gtk+ C++ headers and libraries...
    PKG_CHECK_MODULES(
        [libgtkmm], [gtkmm-3.0 >= 3.22.0], [],
        [AC_MSG_ERROR([gtkmm-3.0 >= 3.22.0 not found...])])
    CXXFLAGS="$CXXFLAGS $libgtkmm_CFLAGS"
    LIBS="$LIBS $libgtkmm_LIBS"

    # GtkSourceView C++ headers and libraries...
    PKG_CHECK_MODULES(
        [libgtksourceviewmm], [gtksourceviewmm-3.0 >= 3.18.0], [],
        [AC_MSG_ERROR([gtksourceviewmm-3.0 >= 3.18.0 not found...])])
    CXXFLAGS="$CXXFLAGS $libgtksourceviewmm_CFLAGS"
    LIBS="$LIBS $libgtksourceviewmm_LIBS"

    # libcanberra Gtk+ 3.0 headers and libraries...
    PKG_CHECK_MODULES(
        [libcanberra_gtk3], [libcanberra-gtk3 >= 0.30], [],
        [AC_MSG_ERROR([libcanberra-gtk3 >= 0.30 not found...])])
    CXXFLAGS="$CXXFLAGS $libcanberra_gtk3_CFLAGS"
    LIBS="$LIBS $libcanberra_gtk3_LIBS"

    # OpenCL C++...
    
        # Headers...
        AC_CHECK_HEADERS(
            [CL/cl2.hpp],
            [], [AC_MSG_ERROR([missing OpenCL 2.0 header...])])

        # Dispatch library acts as a proxy to actual vendor implementation, such
        #  as Intel, nVidia, AMD, etc...
        AC_CHECK_LIB(
            [OpenCL], [clGetPlatformInfo], [],
            [AC_MSG_ERROR([missing OpenCL dispatch library or no clGetPlatformfInfo function found...])])

    # YAML C++ headers and libraries...
    PKG_CHECK_MODULES(
        [libyaml_cpp], [yaml-cpp >= 0.5.2], [],
        [AC_MSG_ERROR([yaml-cpp >= 0.5.2 not found...])])
    CXXFLAGS="$CXXFLAGS $libyaml_cpp_CFLAGS"
    LIBS="$LIBS $libyaml_cpp_LIBS"

# Checks for typedefs, structures, and compiler characteristics...

    # Endianness...
    AC_C_BIGENDIAN

    # Fixed width primitives...
    AC_TYPE_INT8_T
    AC_TYPE_INT16_T
    AC_TYPE_INT32_T
    AC_TYPE_UINT8_T
    AC_TYPE_UINT16_T
    AC_TYPE_UINT32_T

    # Other basic types...
    AC_TYPE_SIZE_T

# Checks for individual functions within libraries...

    # POSIX, Standard C, GNU C library extensions...
    AC_CHECK_FUNCS([clock getenv getopt_long realpath sigaction], [],
        [AC_MSG_ERROR([missing some POSIX, standard C, or GNU C library functions...])])

# Set additional compilation flags...

    # Enable all warnings and treat them as errors...
    CXXFLAGS="$CXXFLAGS -Wall -Werror -Wshadow -Wextra"

# Generate makefiles from templates containing Autoconf substitution variables
#  for root makefile...
AC_CONFIG_FILES([               \
    Makefile                    \
    Translations/Makefile.in])

# Generates config.status which generates all files from templates...
AC_OUTPUT

# Show a user summary of the configuration...
echo \
"-----------------------------------------------------

${PACKAGE_NAME} ${PACKAGE_VERSION}
$copyright_notice

Prefix........................: $prefix

Optional package features:
    Bash completion...........: $enable_bash_completion
    Native language support...: $USE_NLS
    Valgrind unit test........: $enable_valgrind

Compiler......................: $CXX
Linker........................: $LD

C++ Flags.....................: $CFLAGS $CXXFLAGS
C++ Preprocessor..............: $CPPFLAGS
Linker Flags..................: $LDFLAGS
Linker Libs...................: $LIBS

Now type 'make @<:@<target>@:>@' where the optional
<target> is:
    all            ...builds all products (default)
    check          ...perform all self diagnostics
    clean          ...clean the build
    dist           ...builds redistributable archive
    distcheck      ...self diagnostics on previous
    install        ...install to $prefix

-----------------------------------------------------"

