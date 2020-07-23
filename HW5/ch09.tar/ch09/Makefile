CC=g++
CFLAGS= -Wall 
OBJS = testbtree.o
INCDIR=./include
LIBDIR=./lib
DIRS = btindex buffer fixed

.PHONY: all clean


all: testBtree
%.o: %.cpp
	$(CC) -c -I$(INCDIR) $(CFLAGS) -o $@ $<

testBtree: $(OBJS)
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d; \
	done
	$(CC) -o testBtree $(OBJS) -L$(LIBDIR) -lmybuffer -lmyfixed -lmybtree -lc
	export LD_LIBRARY_PATH=$(LIBDIR)

clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done
	-rm -rf testBtree testbt.dat $(OBJS) 
