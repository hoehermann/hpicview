CC = g++
CPPFLAGS = -g -W -Wall -Werror -Wextra --std=c++11
SRCS = $(shell find . -type f -name '*.cpp')
HEDS = $(shell find . -type f -name '*.hpp')
OBJS = $(SRCS:%.cpp=%.o)
PROG = hpicview

JPEG = extern/jpeg
TRANSUPP = $(JPEG)/transupp.o

CPPFLAGS += -DVERSION=\"`git describe --abbrev=7 --dirty --always --tags`\"
CPPFLAGS += `wx-config --cppflags`
CPPFLAGS += -I$(JPEG)
LIBS += `wx-config --libs`
LIBS += $(TRANSUPP)
LIBS += -L$(JPEG) -ljpeg 
LIBS += -lboost_system -lboost_filesystem

all: $(PROG)

.PHONY: clean all run test try

run: $(PROG)
	./$(PROG)
	
try: $(PROG)
	./$(PROG) test_xga.jpg

$(PROG): .depend $(OBJS) $(TRANSUPP)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS) $(LIBS)

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

# automatically build libjpeg

$(JPEG)/Makefile:
	( cd $(JPEG) && ./configure )

$(TRANSUPP): $(JPEG)/Makefile
	$(MAKE) -C $(JPEG)
	
cleanall: clean
	$(MAKE) -C $(JPEG) clean
