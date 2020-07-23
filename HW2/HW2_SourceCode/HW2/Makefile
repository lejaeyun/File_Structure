CC=gcc
CFLAGES=-g -Wall
OBJS=Driver.o Student.o CourseRegistration.o iobuffer.o buffile.o
TARGET=a.out

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lstdc++

Driver.o: Driver.cpp Student.h
Student.o: Student.cpp Student.h
CourseRegistration.o: CourseRegistration.cpp CourseRegistration.h
iobuffer.o: iobuffer.cpp iobuffer.h
buffile.o: buffile.cpp buffile.h iobuffer.h

clean:
	rm -f *.o
	rm -f $(TARGET)

