#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
noinst_LTLIBRARIES = libseleniumcpptest.la

#######################################
# Build information for each library

# AUTOMAKE_OPTIONS = subdir-objects

# Sources for libseleniumcpp
libseleniumcpptest_la_SOURCES = \
	main.cpp \
	selenium_testcase.cpp \
	$(top_srcdir)/third_party/gmock-1.7.0/gtest/src/gtest-all.cc \
	$(top_srcdir)/third_party/gmock-1.7.0/src/gmock-all.cc \
	test_environment.cpp \
	pages.cpp

# Linker options libTestProgram
libseleniumcpptest_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(COVERAGE_LDFLAGS) \
	-stdlib=libc++

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libseleniumcpptest_la_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/third_party/gmock-1.7.0/include \
	-I$(top_srcdir)/third_party/gmock-1.7.0 \
	-I$(top_srcdir)/third_party/gmock-1.7.0/gtest \
	-I$(top_srcdir)/third_party/gmock-1.7.0/gtest/include \
	-I$(top_srcdir)/third_party/boost-process   \
	-std=c++11 \
	$(AM_CPPFLAGS) \
	$(JSONCPP_CFLAGS)

