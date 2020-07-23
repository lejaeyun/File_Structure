#include "HW1_Student.h"

void Student::_setIdentifier(int tmpIdentifier) {
	identifier = tmpIdentifier;
}

void Student::_setName(char * tmpName) {
	strcpy(name, tmpName);
}

void Student::_setAddress(char * tmpAddress) {
	strcpy(address, tmpAddress);
}

void Student::_setFirstEnrollment(time_t tmpFirst) {
	first_enrollment = tmpFirst;
}

void Student::_setCreditHours(int tmpHours) {
	credit_hours = tmpHours;
}

void Student::_addCreditHours(int tmpCredit) {
	credit_hours = credit_hours + tmpCredit;
}

void Student::setIdentifier(int tmpIdentifier) {
	_setIdentifier(tmpIdentifier);
}

void Student::setName(char * tmpName) {
	_setName(tmpName);
}

void Student::setAddress(char * tmpAddress) {
	_setAddress(tmpAddress);
}

void Student::setFirstEnrollment(time_t tmpFirst) {
	_setFirstEnrollment(tmpFirst);
}

void Student::setCreditHours(int tmpHours) {
	_setCreditHours(tmpHours);
}

void Student::addCreditHours(int tmpCredit) {
	_addCreditHours(tmpCredit);
}
		
int Student::_getIdentifier(void) {
	return identifier;
}

char * Student::_getName(void){
	return name;
}

char * Student::_getAddress(void){
	return address;
}

time_t Student::_getFirstEnrollment(void){
	return first_enrollment;
}

int Student::_getCreditHours(void){
	return credit_hours;
}

int Student::getIdentifier(void){
	return _getIdentifier();
}

char * Student::getName(void){
	return _getName();
}

char * Student::getAddress(void){
	return _getAddress();
}

time_t Student::getFirstEnrollment(void){
	return _getFirstEnrollment();
}

int Student::getCreditHours(void){
	return _getCreditHours();
}

void Student::setStudent(int tmpIdentifier, char * tmpName, char * tmpAddress, time_t tmpFirst, int tmpHours) {
	_setIdentifier(tmpIdentifier);
	if (tmpName != nullptr)
		_setName(tmpName);
	if (tmpAddress != nullptr)
		_setAddress(tmpAddress);
	_setFirstEnrollment(tmpFirst);
	_setCreditHours(tmpHours);
}

Student& Student::operator=(Student &st){
	if (this == &st)
		return *this;
	this->setStudent(st.identifier, st.name, st.address, st.first_enrollment, st.credit_hours);
	return *this;
}

ostream& operator<<(ostream& os, const Student & st) {
	struct tm tmpts;
	char tmpbuf[80];
	tmpts = *localtime(&st.first_enrollment);
	strftime(tmpbuf, sizeof(tmpbuf), "%Y-%m-%d-%a-%H-%M-%S",&tmpts);
	os << "id : " << st.identifier << endl;
	os << "name : " << st.name << endl;
	os << "address : " << st.address << endl;
	os << "first_enrollment : " << tmpbuf << endl;
	os << "credit_hours : " << st.credit_hours << endl;
	return os;
}

istream& operator>>(istream& os, Student & st) {
	int tmpInt;
	string tmpString;
	cout << "Enter id : ";
	os >> tmpInt;
	st.setIdentifier(tmpInt);
	cout << "Enter name : ";
	
	os.clear();
	os.ignore(256,'\n');
	
	getline(os, tmpString);
	st.setName( (char*) tmpString.c_str());
	cout << "Enter address : ";
	getline(os, tmpString);
	st.setAddress( (char*) tmpString.c_str());
	st.setFirstEnrollment(time(0));
	cout << "Enter credit_hours : ";
	os >> tmpInt;
	st.setCreditHours(tmpInt);
	return os;
}
