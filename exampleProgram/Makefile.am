#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=exampleProgram

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=exampleProgram

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 
exampleProgram_SOURCES= exampleProgram.cpp

# Linker options for a.out
exampleProgram_LDFLAGS = \
	-stdlib=libc++ \
	$(top_srcdir)/libseleniumcpp/libseleniumcpp.la \
	$(JSONCPP_LIBS) \
	$(COVERAGE_LDFLAGS) \
	$(BOOST_THREAD_LIB) \
	-lboost_system \
	-lboost_regex \
	-lssl \
	-lcrypto

# Compiler options for a.out
exampleProgram_CPPFLAGS = -I$(top_srcdir)/include 	-std=c++11 $(AM_CPPFLAGS) $(JSONCPP_CFLAGS)
