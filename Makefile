CC = g++
CPPFLAGS = -g -W -Wall -Werror -Wextra --std=c++11
SRCS = $(shell find . -type f -name '*.cpp')
HEDS = $(shell find . -type f -name '*.hpp')
OBJS = $(SRCS:%.cpp=%.o)
PROG = hpicview

CPPFLAGS += `wx-config --cppflags` -Iextern/libjpeg
LIBS += `wx-config --libs` -Lextern/libjpeg extern/libjpeg/transupp.o -ljpeg -lboost_system -lboost_filesystem

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
