CC = g++
CPPFLAGS = -g -W -Wall -Werror -Wextra --std=c++11
SRCS = directory_iteration.cpp GUIFrame.cpp hpicviewApp.cpp hpicviewMain.cpp jpegtran.cpp rotate.cpp zoom.cpp # formerly $(shell find . -type f -name '*.cpp')
OBJS = $(SRCS:%.cpp=%.o)
PROG = hpicview

JPEG = extern/libjpeg
TRANSUPP = $(JPEG)/transupp.o
CDJPEG = $(JPEG)/cdjpeg.h
include libjpeg.version

CPPFLAGS += -DVERSION=\"`git describe --abbrev=7 --dirty --always --tags`\"
CPPFLAGS += `wx-config --cppflags`
CPPFLAGS += -I$(JPEG)
LIBS += -ljpeg
LIBS += `wx-config --libs`
LIBS += -lboost_system -lboost_filesystem

all: $(PROG)

.PHONY: clean all run test try

run: $(PROG)
	./$(PROG)

try: $(PROG)
	./$(PROG) test.jpg

jpegtran.o: $(CDJPEG)

$(PROG): $(OBJS) $(TRANSUPP)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) $(LIBS) $(TRANSUPP) 

clean: 
	rm -f $(PROG)
	rm -f $(OBJS)
	rm -f .depend

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# checkout libjpeg from git submodule
$(JPEG)/configure:
	git submodule update --init
	(cd $(JPEG) && git checkout $$(git tag | grep jpeg-$(JPEG_LIB_VERSION_MAJOR) | sort -r | head -n 1) -- '*')
	# apply patch so transupp.c resets the orientation tag
	(cd $(JPEG) && git apply ../libjpeg-reset-orientation-tag.patch)

jpeglib.version:
	echo "Create a file jpeglib.version containing a line JPEG_LIB_VERSION_MAJOR = x where x is the major version your wxWidgets build is built against."

$(JPEG)/Makefile: $(JPEG)/configure
	( cd $(JPEG) && ./configure )

$(CDJPEG): $(JPEG)/Makefile

# automatically build transupp.o in libjpeg
$(TRANSUPP): $(JPEG)/Makefile $(JPEG)/transupp.c
	$(MAKE) -C $(JPEG) transupp.o
	
cleanall: clean $(JPEG)/Makefile
	$(MAKE) -C $(JPEG) clean
