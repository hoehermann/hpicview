CC = g++
CPPFLAGS = -g -W -Wall -Werror -Wextra --std=c++11
SRCS = $(shell find . -type f -name '*.cpp')
HEDS = $(shell find . -type f -name '*.hpp')
OBJS = $(SRCS:%.cpp=%.o)
PROG = hpicview

CPPFLAGS += -DVERSION=\"`git describe --abbrev=7 --dirty --always --tags`\"
CPPFLAGS += `wx-config --cppflags`
CPPFLAGS += -Iextern/libjpeg
LIBS += `wx-config --libs`
LIBS +=  extern/libjpeg/transupp.o
LIBS += -Lextern/libjpeg -ljpeg 
LIBS += -lboost_system -lboost_filesystem

all: $(PROG)

.PHONY: clean all run test

run: $(PROG)
	./$(PROG)
	
try: $(PROG)
	./$(PROG) test_xga.jpg

$(PROG): .depend $(OBJS)
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
