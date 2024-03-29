dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.50])dnl
AC_INIT([gaa],[1.6.6],[nmav@gnutls.org])dnl
AC_CONFIG_SRCDIR([config.h.in])dnl
AC_CONFIG_HEADERS([config.h])dnl
AC_CONFIG_MACRO_DIR([m4])dnl
AC_CONFIG_AUX_DIR([config])dnl
AC_REQUIRE_AUX_FILE([depcomp])dnl

gaadatadir=${datadir}/gaa
gaadocdir=${datadir}/doc/gaa
gaasampledir=${datadir}/gaa/sample

AC_SUBST([gaadatadir])dnl
AC_SUBST([gaadocdir])dnl
AC_SUBST([gaasampledir])dnl
AC_CANONICAL_TARGET dnl# also checks the "_BUILD" and "_HOST" versions

AM_INIT_AUTOMAKE([check-news gnits])dnl
AM_MAINTAINER_MODE
AM_SANITY_CHECK
AC_SEARCH_LIBS([strerror],[cposix]) dnl# used to be AC\_ISC\_POSIX
AM_SET_LEADING_DOT
AC_EXEEXT

dnl# Checks for programs.
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_GCC_TRADITIONAL
AC_PROG_INSTALL
AC_PROG_LN_S
LT_INIT
if test "x${RANLIB}" = "x"; then
	test -z "${RANLIB}"
	AC_PROG_RANLIB
else
	test ! -z "${RANLIB}" && export RANLIB
	AC_SUBST([RANLIB])
fi

dnl# Documentation tools.
AC_ARG_WITH([docs],
            [AS_HELP_STRING([--with-docs],[build documentation])],
[build_docs="${withval}"
 AC_SUBST([want_docs])dnl
])dnl

AS_IF([test "x${build_docs}" = "xyes"],[
  AC_PATH_PROG([LATEX_BIN],[latex],[latex])dnl
  AC_PATH_PROG([LATEX2HTML_BIN],[latex2html],[latex2html])dnl
  AC_PATH_PROG([DVIPS_BIN],[dvips],[dvips])dnl
  AC_PATH_PROG([TEXI2DVI_BIN],[texi2dvi],[texi2dvi])dnl
],[
  AC_SUBST([LATEX_BIN],[false])dnl
  AC_SUBST([LATEX2HTML_BIN],[false])dnl
  AC_SUBST([DVIPS_BIN],[false])dnl
  AC_SUBST([TEXI2DVI_BIN],[false])dnl
])dnl

AM_CONDITIONAL([BUILD_DOCS],[test "x${build_docs}" = "xyes"])dnl

dnl# AX_* macros come from the autoconf-archive package
AX_CHECK_GNU_MAKE

dnl# Checks for libraries.
AC_CHECK_LIB([c],[getline])dnl

if test "x${ac_cv_c_compiler_gnu}" != "xno"; then
  CFLAGS="${CFLAGS} -ggdb3 -Wall -Wpointer-arith -Wno-unused"
fi

dnl# Checks for header files.
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([stddef.h stdio.h])dnl

if test "x${ac_cv_header_unistd_h}" = "x"; then
  test -z "${ac_cv_header_unistd_h}"
  AC_CHECK_HEADERS([unistd.h])
fi

dnl# Checks for typedefs, structures, and compiler characteristics.
AC_C_BIGENDIAN
AC_C_CONST
AC_C_PROTOTYPES
AC_TYPE_SIZE_T

dnl# We depend on BISON (other yaccs may not do)
AC_PROG_YACC
AC_PATH_PROG([BISON],[bison])
if test -z "${BISON}"; then
  YACC=:
else
  YACC="${BISON} -y"
fi
AC_SUBST([YACC])dnl

AC_ARG_WITH([bison-bin],[
AS_HELP_STRING([--with-bison-bin=PATH],[specify where to find the bison program])],
[bison_bin="${withval}"
 AC_DEFINE_UNQUOTED([BISON_BIN],["${bison_bin}"],
                    [Path of directory of bison program.])dnl
 GDB_AC_DEFINE_RELOCATABLE([BISON_BIN],[bison],[${bison_bin}])dnl
])dnl

AC_PROG_LEX([yywrap]) ## (bug in autoconf/automake makes us put both of these)
AM_PROG_LEX

dnl# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([getline memset strdup strncasecmp strstr])dnl

# Output.
AC_CONFIG_FILES([source/Makefile \
                 Makefile \
                 doc/Makefile \
                 source/skel/Makefile \
                 sample/Makefile])dnl
AC_OUTPUT
