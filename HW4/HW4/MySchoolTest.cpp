// maketxtindxfile.cpp

// Headeers for template index
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "recording.h"
#include "fixfld.h"
#include "indfile.h"

#include "./index/indfile.cpp"  // for template method body
#include <iostream>

#include "Student.h"
#include "CourseRegistration.h"
#include "recfile.h"
#include "./buf/recfile.cpp" 

using namespace std;

void AddRecords_st(TextIndexedFile<Student> & indexFile)
{
	int recaddr;	
	srand(time(NULL));
	Student S;	
	S.setStudent(201624548, (char *)"lee jae yoon", (char *)"Pusan", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(*(&S));
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"LJY", (char *)"BUSAN", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(*(&S));
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"BONG", (char *)"Daejeon", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(*(&S));
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"Ann", (char *)"Jeonju", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(*(&S));
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;

	S.setStudent(rand(), (char *)"John", (char *)"Daegu", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(S);
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"Elen", (char *)"Pohang", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(S);
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"Yoon", (char *)"Daegu", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(S);
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"Choi", (char *)"Ulsan", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(S);
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"Moon", (char *)"Busan", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(S);
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	
	S.setStudent(rand(), (char *)"Sun", (char *)"Dokdo", rand(), rand() % 100 + 1);
	recaddr = indexFile.Append(S);
	cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
}


void AddRecords_cr(TextIndexedFile<CourseRegistration> & indexFile, Student * St)
{
	CourseRegistration cr[10];
	int i = 0;
	int recaddr;	
	srand(time(NULL));
	for (i = 0; i < 10; i++) {
		cr[i].setCourseRegistration(rand(), rand() % 3 + 1);
	}

	for (i = 0; i < 10; i++) {

		for (int j = 0; j < 5; j++){
			cr[i].addstudent(St[rand()%10]);
		}
		recaddr = indexFile.Append(cr[i]);
		cr[i].delPointer();
		cout <<"Recording at recaddr "<<recaddr<<" is added to TextIndexFile"<<endl;
	}

}


// make an indexed file from a recording file
template <class RecType>
int ReadIndexRecordingFile (char* myfile, TextIndexedFile<RecType> & indexFile, RecType * st_or_cr)
{
	int recaddr, result;
	DelimFieldBuffer Buffer; // create a buffer
	BufferFile RecFile(Buffer); 

	// open recordFile using the filename
	result = RecFile . Open (myfile,ios::in);
	if (!result)
	{
		cout << "Unable to open file "<<myfile<<endl;
		return 0;
	}
	int i = 0;
	while (1) // loop until the read fails
	{
		RecType indRec;
		recaddr = RecFile . Read (); // read next record
		if (recaddr < 0) break;
		st_or_cr[i]. Unpack (Buffer);
		cout <<"\nLooking for record with key:"
			<<st_or_cr[i].Key()<<endl;
		result = indexFile . Read(st_or_cr[i].Key(),indRec);
		if (result<0) cout <<"record not found";
		else {
			indRec.Print(cout);
			indRec.delPointer();
		}
		i++;
	}
	cout << endl;
	return 1;
}

int Student_driver(Student * St) {

	// create Record file.
	char *strRecording = "Student";
	char *myfile="Student.dat";
	remove("Student.dat");
	remove("Student.ind");
	int result;

	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Student> IndFile (Buffer, 12, 10);
	result = IndFile . Create(strRecording);
	if (!result) 
	{
		cout<<"Unable to create indfile "<<result<<endl;
		return 0;
	}	
	//file create

	AddRecords_st(IndFile);
	

	ReadIndexRecordingFile (myfile, IndFile, St);

	Student indRec;
	cout<<"Search Test"<<endl;
	char key[30];
	memset(key,0,30);
	while (strcmp(key,"-1")  != 0) {
		cout << "Enter Finding Student Key : ";
		cin >> key;
		result=IndFile.Read(key,indRec);
		if (result<0) cout <<"record not found"<<endl;
		else {
			indRec.Print(cout);
			cout << endl;
		}
		indRec.delPointer();
	}

	IndFile.Close();

	return -1;
}


int CourseRegistration_driver(CourseRegistration * Cr, Student * St) {

	// create Record file.
	char *strRecording = "CourseRegistration";
	char *myfile="CourseRegistration.dat";
	remove("CourseRegistration.dat");
	remove("CourseRegistration.ind");
	int result;

	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<CourseRegistration> IndFile (Buffer, 12, 10);
	result = IndFile . Create(strRecording);
	if (!result) 
	{
		cout<<"Unable to create indfile "<<result<<endl;
		return 0;
	}	
	//file create

	AddRecords_cr(IndFile, St);

	ReadIndexRecordingFile (myfile, IndFile, Cr);

	CourseRegistration indRec;
	cout<<"Search Test"<<endl;
	char key[30];
	memset(key,0,30);
	while (strcmp(key,"-1")  != 0) {
		cout << "Enter Finding CourseRegistration Key : ";
		cin >> key;
		result=IndFile.Read(key,indRec);
		if (result<0) cout <<"record not found"<<endl;
		else {
			indRec.Print(cout);
			cout << endl;
		}
		indRec.delPointer();
	}

	IndFile.Close();
	return -1;
}

int main (int argv, char ** argc)
{
	Student St[10];
	CourseRegistration Cr[10];
	Student_driver(St);
	CourseRegistration_driver(Cr, St);
	return -1;
}

