#include <iostream>
#include <time.h>
#include <string.h>
#include "iobuffer.h"
#include "fixfld.h"

#ifndef __STUDENT_H__
#define __STUDENT_H__

#define max_namelength 30
#define max_addresslength 100
using namespace std;

class Student {

	public :
		Student() {
			setStudent(0, nullptr, nullptr, (time_t) 0, 0);
		}
		
		Student(int tmpIdentifier, char * tmpName, char * tmpAddress, time_t tmpFirst, int tmpHours) {
			setStudent(tmpIdentifier, tmpName, tmpAddress, tmpFirst, tmpHours);
		}
		
		//char * Key(void) const;		
		int Key(void) const;		
		void Print(ostream&) const;
		void delPointer(void) {};	

		void setStudent(int , char * , char * , time_t , int );
		
		void setIdentifier(int);
		void setName(char * );
		void setAddress(char * );
		void setFirstEnrollment(time_t);
		void setCreditHours(int);
		
		int getIdentifier(void);
		char * getName(void);
		char * getAddress(void);
		time_t getFirstEnrollment(void);
		int getCreditHours(void);
		
		void addCreditHours(int);
		Student& operator=(Student &st);
		
		int Unpack(IOBuffer & Buffer);
		int Pack(IOBuffer & Buffer) const;
		void Clear(void);
		int InitBuffer(FixedFieldBuffer & Buffer);
		
		friend ostream& operator<<(ostream& os, const Student & );
		friend istream& operator>>(istream& os, Student & );
		
	private :
		int identifier;
		char name[max_namelength];
		char address[max_addresslength];
		time_t first_enrollment;
		int credit_hours;
		
		void _setIdentifier(int);
		void _setName(char * );
		void _setAddress(char * );
		void _setFirstEnrollment(time_t);
		void _setCreditHours(int);
		void _addCreditHours(int);
		
		
		int _getIdentifier(void);
		char * _getName(void);
		char * _getAddress(void);
		time_t _getFirstEnrollment(void);
		int _getCreditHours(void);
};

#endif
