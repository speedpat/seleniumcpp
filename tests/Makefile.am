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
	dummy_test.cpp \
	alerts_test.cpp \
	children_finding_test.cpp \
	children_finding_shortcut_test.cpp \
	clear_test.cpp \
	click_scrolling_test.cpp \
	click_test.cpp \
	correct_event_firing_test.cpp \
	cookie_implementation_test.cpp \
	cookie_test.cpp \
	css_value_test.cpp \
	element_attribute_test.cpp \
	element_equality_test.cpp \
	element_finding_test.cpp \
	element_finding_shortcut_test.cpp \
	element_selecting_test.cpp \
	executing_async_javascript_test.cpp	\
	executing_javascript_test.cpp \
	form_handling_test.cpp \
	frame_switching_test.cpp \
	typing_test.cpp \
	scriptarg_test.cpp \
	scriptresult_test.cpp \
	window_switching_test.cpp \
	basic_keyboard_interface_test.cpp \
	basic_mouse_interface_test.cpp

# Linker options for a.out
tests_LDFLAGS = \
	-stdlib=libc++ \
	$(top_srcdir)/tests/support/libseleniumcpptest.la \
	$(top_srcdir)/libseleniumcpp/libseleniumcpp.la \
	$(JSONCPP_LIBS) \
	$(COVERAGE_LDFLAGS) \
	-lboost_system \
	$(BOOST_THREAD_LIB) \
	-lboost_regex \
	-lcppnetlib-uri \
	-lcppnetlib-client-connections \
	-lcrypto \
	-lssl
#	-lpthread

# Compiler options for a.out
tests_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/third_party/gmock-1.7.0/include \
	-I$(top_srcdir)/third_party/gmock-1.7.0/gtest/include \
	-I$(top_srcdir)/third_party/boost-process \
	$(AM_CPPFLAGS) \
	-std=c++11 \
	$(JSONCPP_CFLAGS)

tests_DEPENDENCIES = $(top_srcdir)/tests/support/libseleniumcpptest.la

SUBDIRS=support

