dnl# GDB_AC_DEFINE_RELOCATABLE([VARIABLE],[ARG-NAME],[SHELL-VARIABLE])
dnl# For use in processing directory values for --with-foo.
dnl# If the path in SHELL_VARIABLE is relative to the prefix, then the
dnl# result is relocatable, then this will define the C macro
dnl# VARIABLE_RELOCATABLE to 1; otherwise it is defined as 0.
AC_DEFUN([GDB_AC_DEFINE_RELOCATABLE],[
  if test "x${exec_prefix}" = xNONE || test "x${exec_prefix}" = 'x${prefix}'; then
     if test "x${prefix}" = xNONE; then
     	test_prefix=/usr/local
     else
	test_prefix=${prefix}
     fi
  else
     test_prefix=${exec_prefix}
  fi
  value=0
  case [$3] in
     "${test_prefix}"|"${test_prefix}/"*|\
	'${exec_prefix}'|'${exec_prefix}/'*)
     value=1
     ;;
  esac
  AC_DEFINE_UNQUOTED([$1]_RELOCATABLE,[${value}],[Define if the $2 directory should be relocated when GDB is moved.])
])

