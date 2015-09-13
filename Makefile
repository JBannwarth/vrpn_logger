
CC = gcc
CXX = g++ -std=c++11

CFLAGS = -O
CCFLAGS = -std=c++11 -O


VRPNDIR = /usr/local
VRPNINC = -I$(VRPNDIR)
VRPNLIB = -L$(VRPNDIR)/lib -lvrpn -lquat

INCS = $(VRPNINC)
LIBS = $(VRPNLIB) -lm

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
