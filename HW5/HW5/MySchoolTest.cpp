// Headeers for template index
#include "btnode.h"
#include "./btindex/btnode.cpp" // for template method body
#include "btree.h"
#include "./btindex/btree.cpp"   // for template method body
#include <iostream>

#include "Student.h"
#include "recfile.h"
#include "./buffer/recfile.cpp" 

using namespace std;

void AddRecords_st()
{	
	FixedFieldBuffer Student_Buffer(5);
	Student S;
	S.InitBuffer(Student_Buffer);
	
	remove("Students.dat");
	RecordFile<Student> St_Rec2file (Student_Buffer);
	St_Rec2file.Create((char*)"Students.dat",ios::out);
	
	srand(time(NULL));
	
	// µ¥ÀÌÅÍ ÀúÀå µå¶óÀÌ¹ö 
	
	S.setStudent(201624548, (char *)"lee jae yoon", (char *)"Pusan", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	char * student = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0 ; i < 50; i++) {
		S.setStudent(rand(), student+i, student+i, rand(), rand() % 100 + 1);
		St_Rec2file.Write(S);
	}

	St_Rec2file.Close();
	
	// ÀúÀåµÈ µ¥ÀÌÅÍ ºÒ·¯¿À±â 
	
}

const int BTreeSize = 50;
int main (int argv, char ** argc)
{
	AddRecords_st();

	Student St[50];
	FixedFieldBuffer Student_Buffer(5);
	Student S;
	S.InitBuffer(Student_Buffer);
	
	RecordFile<Student> St_Rec2file (Student_Buffer);
	St_Rec2file.Open((char*)"Students.dat", ios::in);
	
	int i = 0;
	int addr = 0;

	int result;
	BTree <int> bt (BTreeSize);
	remove("testbt.dat");
	result = bt.Create ("testbt.dat",ios::in|ios::out);

	// Insert
	while (i < 50) {
		addr = St_Rec2file.Read(St[i]);
		result = bt.Insert(St[i].Key(), addr);
		cout << "Inserting Key : " << St[i].Key() << endl;
		i++;
		bt.Print(cout);
	}
	
	// Search
	int search_key = 0;
	Student rst;
	cout << "If you Want to Search Key, Enter key Else Enter -1" << endl;
	while (search_key != -1) {
		cout << "Enter Want Search key : ";
		cin >> search_key;
		addr = bt.Search(search_key,-1);
		cout << "addr in " << addr << endl;
		St_Rec2file.Read(rst, addr);
		cout << "Print Student " << endl;
		cout <<	rst << endl;
	}

	St_Rec2file.Close();

	// Remove
	int remove_key = 0;
	cout << "If you Want to remove Key, Enter key Else Enter -1" << endl;
	while (remove_key != -1) {
		cout << "Enter Want remove key : ";
		cin >> remove_key;
		bt.Remove(remove_key, -1);
		bt.Print(cout);
	}


	return -1;
}

