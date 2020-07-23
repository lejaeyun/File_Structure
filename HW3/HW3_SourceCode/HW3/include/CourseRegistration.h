#include <iostream>
#include <time.h>
#include <string.h>
#include "Student.h"

#ifndef __COURSEREGISTRATION_H__
#define __COURSEREGISTRATION_H__

using namespace std;

typedef struct Linked_Student_Course_Grade {
	int std_identifier = -1;
	int grade_sum;
	Linked_Student_Course_Grade * nxt_std = NULL;
} STD;


class CourseRegistration {

	public :
		CourseRegistration() {		
			setCourseRegistration(0, 0);
			course_grades = (STD *) malloc( sizeof(STD) );
		}
		
		CourseRegistration(int tmpcourse_identifier,  int tmpclass_credit_hours) {	
			setCourseRegistration(tmpcourse_identifier, tmpclass_credit_hours);
			course_grades = (STD *) malloc( sizeof(STD) );
		}
		
		void setCourseRegistration(int , int);		
		void setcourse_identifier(int);
		void setclass_credit_hours(int);
		void addstudent(int, int);
		void addstudent(Student);
		void addGrade(int, int);
		
		int getcourse_identifier(void);
		int getclass_credit_hours(void);

		int Unpack(IOBuffer & Buffer);
		int Pack(IOBuffer & Buffer) const;
		void delPointer(void);
		void delStudent(int);
		
		friend ostream& operator<<(ostream& os, const CourseRegistration & );
		friend istream& operator>>(istream& os, CourseRegistration & );
		
	private :
		int course_identifier;
		int class_credit_hours;
		STD * course_grades;
		
		void _setcourse_identifier(int);
		void _setclass_credit_hours(int);
		void _addGrade(int, int);
		
		int _getcourse_identifier(void);
		int _getclass_credit_hours(void);
};

#endif
