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
	/usr/src/gmock/gtest/src/gtest-all.cc \
	/usr/src/gmock/src/gmock-all.cc \
	test_environment.cpp \
	pages.cpp

# Linker options libTestProgram
libseleniumcpptest_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	$(COVERAGE_LDFLAGS)

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libseleniumcpptest_la_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I/usr/src/gmock/ \
	-I/usr/src/gmock/gtest \
	-I/usr/src/gmock/gtest/include \
	-I$(top_srcdir)/third_party/boost-process   \
	-std=c++0x \
	$(AM_CFLAGS) \
	$(JSONCPP_CFLAGS)

