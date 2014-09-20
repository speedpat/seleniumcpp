#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=exampleProgram

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=tests

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 
tests_SOURCES= \
	main.cpp \
	selenium_testcase.cpp \
	in_process_web_server.cpp \
	/usr/src/gtest/src/gtest-all.cc \
	test_environment.cpp \
	pages.cpp \
	dummy_test.cpp \
	alerts_test.cpp

# Linker options for a.out
tests_LDFLAGS = $(top_srcdir)/libseleniumcpp/libseleniumcpp.la -lpthread -lcppnetlib-client-connections -lboost_system -lboost_thread -lcppnetlib-uri 

# Compiler options for a.out
tests_CPPFLAGS = -I$(top_srcdir)/include -I/usr/src/gtest -I$(top_srcdir)/ -std=c++0x
