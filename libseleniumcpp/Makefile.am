#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libseleniumcpp.la

#######################################
# Build information for each library

# Sources for libseleniumcpp
libseleniumcpp_la_SOURCES = \
	webdriver.cpp \
	webelement.cpp \
	by.cpp \
	actions.cpp \
	action.cpp \
	types.cpp \
	wait.cpp \
	expectedconditions.cpp \
	alert.cpp \
	switch_to.cpp \
	mobile.cpp \
	application_cache.cpp \
	cookie.cpp \
	script_arg.cpp \
	script_result.cpp \
	desired_capabilities.cpp \
	keys.cpp \
	color.cpp \
	colors.cpp

# Linker options libTestProgram
libseleniumcpp_la_LDFLAGS = $(COVERAGE_LDFLAGS)

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libseleniumcpp_la_CPPFLAGS = -I$(top_srcdir)/include -std=c++0x $(JSONCPP_CFLAGS) $(COVERAGE_CFLAGS)

