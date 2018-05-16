CC = g++
CPPFLAGS = -g -W -Wall -Werror -Wextra --std=c++11
SRCS = $(shell find . -type f -name '*.cpp')
HEDS = $(shell find . -type f -name '*.hpp')
OBJS = $(SRCS:%.cpp=%.o)
PROG = hpicview

JPEG = extern/jpeg
TRANSUPP = $(JPEG)/transupp.o
CDJPEG = $(JPEG)/cdjpeg.h

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
	./$(PROG) test_xga.jpg

jpegtran.o: $(CDJPEG)

$(PROG): .depend $(OBJS) $(TRANSUPP)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) $(LIBS) $(TRANSUPP) 

clean: 
	rm -f $(PROG)
	rm -f $(OBJS)
	rm -f .depend

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# Compute header file dependencies 
.depend : $(SRCS)
	$(CC) $(CPPFLAGS) -MM $^ > .depend

# Respect header file dependencies
include .depend

# checkout libjpeg from git submodule
# libjpeg version must match the one used by wxWidgets
$(JPEG)/configure:
  # TODO: make this rely on libjpeg as actually used by wxWidgets (the variant shown ehere assumes that wxWidgets is dynamically linked against the libjpeg as chosen by the current system)
	echo "#include <iostream>\n#include <jpeglib.h>\nint main(int, char **) { std::cout << JPEG_LIB_VERSION << std::endl; return 0; }" > jlv.cpp 
	$(CC) $(CPPFLAGS) -o jlv jlv.cpp $(LIBS)
	(cd $(JPEG) && git checkout $$(git tag | grep jpeg-$$(../../jlv | grep -o ^.) | sort -r | head -n 1) -- '*')
	rm jlv jlv.cpp
	
$(JPEG)/Makefile: $(JPEG)/configure
	( cd $(JPEG) && ./configure )

$(CDJPEG): $(JPEG)/Makefile

# automatically build transupp.o in libjpeg
$(TRANSUPP): $(JPEG)/Makefile
	$(MAKE) -C $(JPEG) transupp.o
	
cleanall: clean $(JPEG)/Makefile
	$(MAKE) -C $(JPEG) clean
