CC=g++
CFLAGS= -Wall 
OBJS = MySchoolTest.o
INCDIR=./include
LIBDIR=./lib
DIRS = buffer fixed btindex school

.PHONY: all clean

all: MySchoolTest
%.o: %.cpp
	$(CC) -c -I$(INCDIR) $(CFLAGS) -o $@ $<

MySchoolTest: $(OBJS)
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d; \
	done
	$(CC) -o MySchoolTest $(OBJS) -L$(LIBDIR) -lmybuffer -lmyfixed -lmybtree -lmyschool -lc
	export LD_LIBRARY_PATH=$(LIBDIR)

clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done
	-rm -rf MySchoolTest $(OBJS) 
	-rm -rf *.dat
	-rm -rf *.ind
