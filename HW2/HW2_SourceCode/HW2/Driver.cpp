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
	
	// 데이터 저장 드라이버 
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
	
	
	
	// 저장된 데이터 불러오기 
	Student St[10];
	RecordingFile.Open((char*)"Students.dat", ios::in);
	
	i = 0;
	while (RecordingFile.Read() != -1) {
		St[i++].Unpack(Buffer);
		cout << St[i-1] << endl;
	}
	
	RecordingFile.Close();
	
	CourseRegistration cr[10];
	// 수업을 랜덤으로 생성 
	for (i = 0; i < 10; i++) {
		cr[i].setCourseRegistration(rand(), rand() % 3 + 1);
	}
	// 학생을 랜덤으로 삽입 
	for (i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++){
			cr[i].addstudent(St[rand()%10]);
		}
		cout << cr[i] << endl;
	}
	// 데이터 파일 저장 
	remove("CourseRegistration.dat");
	RecordingFile.Create ((char*)"CourseRegistration.dat", ios::out);
	for (int i = 0; i < 10 ; i++){
		cr[i].Pack(Buffer);
		RecordingFile.Write();
	}
	
	RecordingFile.Close();
	
	// 저장된 데이터 불러오 기 
	RecordingFile.Open((char*)"CourseRegistration.dat", ios::in);
	
	i = 0;
	while (RecordingFile.Read() != -1) {
		cr[i++].Unpack(Buffer);
		cout << cr[i-1] << endl;
	}
	
	// 데이터 누수 방지를 위해 포인터 해제 
	for (int i = 0; i < 10 ; i++){
		cr[i].delPointer();
	}
	
	
	RecordingFile.Close();
	
	return 0;
}