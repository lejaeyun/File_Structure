CC=gcc
CFLAGES=-g -Wall
OBJS=HW1_Driver.o HW1_Student.o HW1_CourseRegistration.o
TARGET=a.out

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lstdc++

HW1_Driver.o: HW1_Driver.cpp HW1_Student.h
HW1_Student.o: HW1_Student.cpp HW1_Student.h
HW1_CourseRegistration.o: HW1_CourseRegistration.cpp HW1_CourseRegistration.h

clean:
	rm -f *.o
	rm -f $(TARGET)

