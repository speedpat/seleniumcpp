dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(libseleniumcpp, 1.0)

AC_PROG_CC

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL
AC_PROG_CXX

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS(include)

PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES([JSONCPP], [jsoncpp])
AC_SUBST(JSONCPP_CFLAGS)

AX_BOOST_BASE([1.49])
AX_BOOST_THREAD

AC_ARG_ENABLE(coverage, AS_HELP_STRING([--enable-coverage]), [COVERAGE_CFLAGS="--coverage"]
        [COVERAGE_LDFLAGS="--coverage"] ,)



AC_SUBST(COVERAGE_CFLAGS)
AC_SUBST(COVERAGE_LDFLAGS)



AC_CONFIG_FILES(Makefile
                exampleProgram/Makefile
                tests/Makefile
                libseleniumcpp/Makefile
                include/Makefile
                tests/support/Makefile)
AC_OUTPUT
