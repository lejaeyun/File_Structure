#include "HW1_CourseRegistration.h"

void CourseRegistration::setCourseRegistration(int tmpidentifier, int tmpclass_credit_hours) {
	setcourse_identifier(tmpidentifier);
	setclass_credit_hours(tmpclass_credit_hours);
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
	STD * si = cr.course_grades->nxt_std;
	
	cout << " ##### Blow the Students #####" << endl;
	int index = 1;
	while (si != NULL) {
		cout << "Student " << index++ << " : " << si->std_identifier << endl;
		cout << "Grade_Sum : " << si->grade_sum << endl << endl;
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
