#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
noinst_LTLIBRARIES = libseleniumcpptest.la

#######################################
# Build information for each library

AM_OPTION=subdir-objects

# Sources for libseleniumcpp
libseleniumcpptest_la_SOURCES = \
	main.cpp \
	selenium_testcase.cpp \
	in_process_web_server.cpp \
	/usr/src/gtest/src/gtest-all.cc \
	test_environment.cpp \
	pages.cpp

# Linker options libTestProgram
libseleniumcpptest_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libseleniumcpptest_la_CPPFLAGS = -I$(top_srcdir)/include -I/usr/src/gtest  -I$(top_srcdir)/  -std=c++0x

