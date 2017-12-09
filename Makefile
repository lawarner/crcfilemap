#
# Simple Makefile for crcfilemap

CXXFLAGS=-std=c++14

PROGRAM=crcfilemap
POBJ=$(PROGRAM).o
OBJS=attributes.o direlement.o dirhandler.o

$(PROGRAM): $(OBJS) $(POBJ)
	$(CXX) -o $@ $^

clean:
	rm -f $(OBJS) $(POBJ) $(PROGRAM)
