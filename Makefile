#
# Simple Makefile for crcfilemap

CXXFLAGS=-std=c++14 -g -O0

PROGRAM=crcfilemap
POBJ=$(PROGRAM).o
OBJS=attributes.o direlement.o dirhandler.o matcher.o
SRCS=$(PROGRAM).cpp $(OBJS:.o=.cpp)

$(PROGRAM): $(OBJS) $(POBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(POBJ) $(PROGRAM)

.PHONY: depends
depends: $(SRCS) $(INCS)
	$(CXX) $(CXXFLAGS) -MM $(SRCS) > .makedepends
	touch .mkdep-timestamp

.makedepends: depends

include .makedepends
