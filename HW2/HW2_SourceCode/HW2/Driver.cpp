#include <iostream>
#include "Student.h"
#include "CourseRegistration.h"
#include "buffile.h"
#include "iobuffer.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int recaddr, i;
	IOBuffer Buffer;
	BufferFile RecordingFile (Buffer);
	srand(time(NULL));
	
	// ������ ���� ����̹� 
	remove("Students.dat");
	Student S;
	RecordingFile.Create ((char*)"Students.dat", ios::out);
	S.setStudent(201624548, (char *)"lee jae yoon", (char *)"Pusan", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"KIM", (char *)"Seoul", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"BONG", (char *)"Daejeon", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"Ann", (char *)"Jeonju", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"John", (char *)"Daegu", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"Elen", (char *)"Pohang", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"Yoon", (char *)"Daegu", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"Choi", (char *)"Ulsan", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"Moon", (char *)"Busan", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	S.setStudent(rand(), (char *)"Sun", (char *)"Dokdo", rand(), rand() % 100 + 1);
	S.Pack(Buffer);
	RecordingFile.Write();
	
	RecordingFile.Close();
	
	
	
	// ����� ������ �ҷ����� 
	Student St[10];
	RecordingFile.Open((char*)"Students.dat", ios::in);
	
	i = 0;
	while (RecordingFile.Read() != -1) {
		St[i++].Unpack(Buffer);
		cout << St[i-1] << endl;
	}
	
	RecordingFile.Close();
	
	CourseRegistration cr[10];
	// ������ �������� ���� 
	for (i = 0; i < 10; i++) {
		cr[i].setCourseRegistration(rand(), rand() % 3 + 1);
	}
	// �л��� �������� ���� 
	for (i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++){
			cr[i].addstudent(St[rand()%10]);
		}
		cout << cr[i] << endl;
	}
	// ������ ���� ���� 
	remove("CourseRegistration.dat");
	RecordingFile.Create ((char*)"CourseRegistration.dat", ios::out);
	for (int i = 0; i < 10 ; i++){
		cr[i].Pack(Buffer);
		RecordingFile.Write();
	}
	
	RecordingFile.Close();
	
	// ����� ������ �ҷ��� �� 
	RecordingFile.Open((char*)"CourseRegistration.dat", ios::in);
	
	i = 0;
	while (RecordingFile.Read() != -1) {
		cr[i++].Unpack(Buffer);
		cout << cr[i-1] << endl;
	}
	
	// ������ ���� ������ ���� ������ ���� 
	for (int i = 0; i < 10 ; i++){
		cr[i].delPointer();
	}
	
	
	RecordingFile.Close();
	
	return 0;
}