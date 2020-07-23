CC=g++
CFLAGS= -Wall 
OBJS = MySchoolTest.o
INCDIR=./include
LIBDIR=./lib
DIRS = buf fixed school var rec

.PHONY: all clean

all: MySchoolTest
%.o: %.cpp
	$(CC) -c -I$(INCDIR) $(CFLAGS) -o $@ $<

MySchoolTest: $(OBJS)
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d; \
	done
	$(CC) -o MySchoolTest $(OBJS) -L$(LIBDIR) -lmybuffer -lmyfixed -lmyrec -lmyschool -lmyvar
	export LD_LIBRARY_PATH=$(LIBDIR)

clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done
	-rm -rf MySchoolTest $(OBJS) 
