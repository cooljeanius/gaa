dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.50])
AC_INIT([gaa], [1.6.6])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])

gaadatadir=$datadir/gaa
gaadocdir=$datadir/doc/gaa
gaasampledir=$datadir/gaa/sample

AC_SUBST(gaadatadir)
AC_SUBST(gaadocdir)
AC_SUBST(gaasampledir)
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE
AM_SANITY_CHECK
AC_ISC_POSIX
AM_SET_LEADING_DOT
AC_EXEEXT

dnl Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_GCC_TRADITIONAL
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB

dnl AX_* macros require the autoconf-archive package
AX_CHECK_GNU_MAKE

dnl Checks for libraries.
AC_CHECK_LIB([c], [getline])

if test $ac_cv_c_compiler_gnu != no; then
  CFLAGS="${CFLAGS} -ggdb3 -Wall -Wpointer-arith"
fi

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stddef.h stdio.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

dnl We depend on BISON (other yacc's may not do)
AC_PROG_YACC
AC_PATH_PROG([BISON], [bison])
if test -z "$BISON"; then
  YACC=:
else
  YACC="$BISON -y"
fi
AC_SUBST(YACC)

AC_ARG_WITH([bison-bin],
AS_HELP_STRING([--with-bison-bin=PATH], [specify where to find the bison program]),
[bison_bin="${withval}"
 AC_DEFINE_UNQUOTED([BISON_BIN], ["${bison_bin}"],
                    [Path of directory of bison program.])
 GDB_AC_DEFINE_RELOCATABLE([BISON_BIN], [bison], [${bison_bin}])
])

AM_PROG_LEX

dnl Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([getline memset strdup strncasecmp strstr])

AC_CONFIG_FILES([source/Makefile Makefile doc/Makefile source/skel/Makefile sample/Makefile])

AC_OUTPUT
