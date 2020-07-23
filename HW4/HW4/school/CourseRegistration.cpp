#include "CourseRegistration.h"

#include <strstream>
#include <cstring>
#include <string>

void CourseRegistration::setCourseRegistration(int tmpidentifier, int tmpclass_credit_hours) {
	setcourse_identifier(tmpidentifier);
	setclass_credit_hours(tmpclass_credit_hours);
	STD * tmpstd = (STD *) malloc( sizeof(STD) );
	tmpstd->std_identifier = -1;
	tmpstd->nxt_std = NULL;
	course_grades = tmpstd;
}

void CourseRegistration::setcourse_identifier(int tmpcourse_identifier) {
	_setcourse_identifier(tmpcourse_identifier);
}

void CourseRegistration::setclass_credit_hours(int tmpclass_credit_hours) {
	_setclass_credit_hours(tmpclass_credit_hours);
}

void CourseRegistration::addstudent(int tmpidentifier, int tmpgrade) {
	_addGrade(tmpidentifier, tmpgrade);
}

void CourseRegistration::addstudent(Student std) {
	_addGrade(std.getIdentifier(), 0);
}

void CourseRegistration::addGrade(int std_identifier, int addgrade) {
	_addGrade(std_identifier, addgrade);
}


void CourseRegistration::_setcourse_identifier(int tmpcourse_identifier) {
	course_identifier = tmpcourse_identifier;
}

void CourseRegistration::_setclass_credit_hours(int tmpclass_credit_hours) {
	class_credit_hours = tmpclass_credit_hours;
}

void CourseRegistration::_addGrade(int tmpidentifier, int tmpgrade) {
	STD * si = course_grades;
	STD * pre;

	int isvalid = 0;
	while (si != NULL) {
		pre = si;
		if (si->std_identifier == tmpidentifier) {
			isvalid = 1;
			break;
		}
		si = si->nxt_std;
	}

	if (isvalid == 0) {
		STD * tmpstd = (STD *) malloc( sizeof(STD) );
		tmpstd->std_identifier = tmpidentifier;
		tmpstd->grade_sum = tmpgrade;
		tmpstd->nxt_std = NULL;
		pre->nxt_std = tmpstd;
	}
	else {
		si->grade_sum = si->grade_sum + tmpgrade;
	}

}

int CourseRegistration::_getcourse_identifier(void){
	return course_identifier;
}
int CourseRegistration::_getclass_credit_hours(void){
	return class_credit_hours;
}

int CourseRegistration::getcourse_identifier(void){
	return _getcourse_identifier();
}
int CourseRegistration::getclass_credit_hours(void){
	return _getclass_credit_hours();
}

ostream& operator<<(ostream& os, const CourseRegistration & cr) {
	os << "Class_Identifier : " << cr.course_identifier << endl;
	os << "Class_Credit_Hours : " << cr.class_credit_hours << endl;
	
	if (cr.course_grades->nxt_std == NULL) return os;
	
	STD * si = cr.course_grades->nxt_std;
	
	cout << " ##### Blow the Students #####" << endl;
	int index = 1;
	while (si != NULL) {
		if (si->std_identifier != -1) {
			cout << "Student " << index++ << " : " << si->std_identifier << endl;
			cout << "Grade_Sum : " << si->grade_sum << endl << endl;
		}
		si = si->nxt_std;
	}
	return os;
}

istream& operator>>(istream& os, CourseRegistration & cr) {
	cout << "Input Course_Identifier : ";
	int tmp = 0;
	os >> tmp;
	cr.setcourse_identifier(tmp);
	cout << "Input Credit_Hours : ";
	os >> tmp;
	cr.setclass_credit_hours(tmp);
	return os;
}

void CourseRegistration::delPointer(void) {
	STD * si = course_grades;
	STD * pre;

	while (si != NULL) {
		pre = si;
		si = si->nxt_std;
		free(pre);
	}
}

void CourseRegistration::delStudent(int tmpidentifier) {
	STD * si = course_grades;
	STD * pre;

	int isvalid = 0;
	while (si != NULL) {
		if (si->std_identifier == tmpidentifier) {
			isvalid = 1;
			break;
		}
		pre = si;
		si = si->nxt_std;
	}
	if (isvalid == 1) {
		pre->nxt_std = si->nxt_std;
		free(si);
	}
}

int CourseRegistration::Pack (IOBuffer & Buffer) const
{// return TRUE if all succeed, FALSE o/w
	int numBytes;
	char buff[30];
	Buffer . Clear ();
	sprintf(buff,"%d",course_identifier);
	numBytes = Buffer . Pack (buff);
	if (numBytes == -1) return FALSE;
	
	sprintf(buff,"%d",class_credit_hours);
	numBytes = Buffer . Pack (buff);
	if (numBytes == -1) return FALSE;
	
	STD * si = course_grades->nxt_std;
	while (si != NULL) {
		sprintf(buff,"%d",si->std_identifier);
		numBytes = Buffer . Pack (buff);
		if (numBytes == -1) return FALSE;
		
		sprintf(buff,"%d",si->grade_sum);
		numBytes = Buffer . Pack (buff);
		if (numBytes == -1) return FALSE;
		
		si = si->nxt_std;
	}
	return TRUE;
}

int CourseRegistration::Unpack (IOBuffer & Buffer)
{// unpack with maximum size, and add null termination to strings
	
	int numBytes;
	char buff[max_addresslength];
	// 배열 초기화 
	memset(buff, 0, max_addresslength);
	numBytes = Buffer . Unpack (buff);
	if (numBytes == -1) return FALSE;
	setcourse_identifier(atoi(buff));
	
	memset(buff, 0, max_addresslength);
	numBytes = Buffer . Unpack (buff);
	if (numBytes == -1) return FALSE;
	setclass_credit_hours(atoi(buff));
	
	while ( numBytes != -1) {
		int tmpid, tmpgrade;
		memset(buff, 0, max_addresslength);
		numBytes = Buffer.Unpack(buff);
		if (numBytes == -1)	return TRUE;
		tmpid = atoi(buff);
		
		memset(buff, 0, max_addresslength);
		numBytes = Buffer.Unpack(buff);
		if (numBytes == -1) return FALSE;
		tmpgrade = atoi(buff);
	
		addGrade(tmpid, tmpgrade);
	}
	
	return TRUE;
}

char * CourseRegistration::Key () const
{// produce key as concatenation of Label and IdNum
	ostrstream key;   // this is replaced
	//ostringstream key;
	char id_buff[30];
	memset(id_buff, 0, 30);
	sprintf(id_buff,"%d", course_identifier);
	key << id_buff << ends;
	return key.str();	
}


void CourseRegistration::Print (ostream & os) const
{
	os << *this<< endl;	
}

