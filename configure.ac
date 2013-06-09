#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([zmpi], [0.1], [more.andres@gmail.com])
AM_INIT_AUTOMAKE
LT_INIT
AC_CONFIG_SRCDIR([src/zmpi.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([check], [suite_create])
AC_CHECK_LIB([zmq], [zmq_ctx_new])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 t/Makefile])
AC_OUTPUT
