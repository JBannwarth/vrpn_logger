
CC = gcc
CXX = g++-4.9

CFLAGS = -O
CCFLAGS = -std=c++11 -O


VRPNDIR = $(HOME)/vrpn
VRPNINC = -I$(VRPNDIR)/include
VRPNLIB = -L$(VRPNDIR)/lib -lvrpn -lquat -lpthread

INCS = $(VRPNINC)
LIBS = $(VRPNLIB) -lm

OBJS = vrpn_test.o
BINS = vrpn_test

all: $(BINS) $(OBJS)

.c.o :
	$(CC) $(CCFLAGS) $(INCS) -c $*.c

.C.o :
	$(CXX) $(CCFLAGS) $(INCS) -c $*.C

vrpn_test : vrpn_test.o tracked_object.o
	$(CXX) $(CCFLAGS) $(INCS) vrpn_test.o tracked_object.o $(LIBS) -o $@


clean :
	rm -f $(OBJS) $(BINS)
