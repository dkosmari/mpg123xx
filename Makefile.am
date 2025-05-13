EXTRA_DIST = \
	bootstrap \
	COPYING \
	README.md



mpg123xx_HEADERS = \
	include/mpg123xx/basic_wrapper.hpp \
	include/mpg123xx/error.hpp \
	include/mpg123xx/format.hpp \
	include/mpg123xx/frame.hpp \
	include/mpg123xx/handle.hpp \
	include/mpg123xx/id3.hpp \
	include/mpg123xx/mpg123.hpp

mpg123xxdir = $(includedir)/mpg123xx



AM_CPPFLAGS = \
	$(MPG123_CFLAGS) \
	-I$(srcdir)/include


AM_CXXFLAGS = \
	-Wall -Wextra -Werror


LIBS = $(MPG123_LIBS)


lib_LIBRARIES = libmpg123xx.a


libmpg123xx_a_SOURCES = \
	src/error.cpp \
	src/format.cpp \
	src/frame.cpp \
	src/handle.cpp \
	src/id3.cpp \
	src/mpg123.cpp \
	src/utils.cpp \
	src/utils.hpp


noinst_PROGRAMS = \
	examples/read_id3


examples_read_id3_SOURCES = \
	examples/read_id3.cpp

examples_read_id3_LDADD = libmpg123xx.a



.PHONY: company
company: compile_flags.txt

compile_flags.txt: Makefile
	printf "%s" "$(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS)" | xargs -n1 | sort -u > $(srcdir)/compile_flags.txt
	$(CPP) -xc++ /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,-I,p' >> $(srcdir)/compile_flags.txt
