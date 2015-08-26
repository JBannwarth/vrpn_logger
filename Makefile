
CC = gcc
CXX = g++

CFLAGS = -O
CCFLAGS = -std=c++11 -O


VRPNDIR = $(HOME)/vrpn
VRPNINC = -I$(VRPNDIR)/include
VRPNLIB = -L$(VRPNDIR)/lib -lvrpn -lquat -lpthread

INCS = $(VRPNINC)
LIBS = $(VRPNLIB) -lm -lboost_system

OBJS = vrpn_logger.o
BINS = vrpn_logger

all: $(BINS) $(OBJS)

.c.o :
	$(CC) $(CCFLAGS) $(INCS) -c $*.c

.C.o :
	$(CXX) $(CCFLAGS) $(INCS) -c $*.C

vrpn_logger : vrpn_logger.o tracked_object.o
	$(CXX) $(CCFLAGS) $(INCS) vrpn_logger.o tracked_object.o $(LIBS) -o $@


clean :
	rm -f $(OBJS) $(BINS)
