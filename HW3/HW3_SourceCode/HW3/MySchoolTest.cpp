#include <iostream>
#include "Student.h"
#include "CourseRegistration.h"
#include "buffile.h"
#include "delim.h"
#include "fixfld.h"
#include "recfile.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int i;
	FixedFieldBuffer Student_Buffer(5);
	Student S;
	S.InitBuffer(Student_Buffer);
	
	remove("Students.dat");
	RecordFile<Student> St_Rec2file (Student_Buffer);
	St_Rec2file.Create((char*)"Students.dat",ios::out);
	
	srand(time(NULL));
	
	// 데이터 저장 드라이버 
	
	S.setStudent(201624548, (char *)"lee jae yoon", (char *)"Pusan", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"KIM", (char *)"Seoul", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"BONG", (char *)"Daejeon", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"Ann", (char *)"Jeonju", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"John", (char *)"Daegu", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"Elen", (char *)"Pohang", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"Yoon", (char *)"Daegu", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"Choi", (char *)"Ulsan", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"Moon", (char *)"Busan", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	
	S.setStudent(rand(), (char *)"Sun", (char *)"Dokdo", rand(), rand() % 100 + 1);
	St_Rec2file.Write(S);
	St_Rec2file.Close();
	
	// 저장된 데이터 불러오기 
	Student St[10];
	St_Rec2file.Open((char*)"Students.dat", ios::in);
	
	i = 0;
	while (i < 10) {
		St_Rec2file.Read(St[i]);
		cout << i+1 << endl;
		cout << St[i++] << endl;
	}
	
	St_Rec2file.Close();
	
	DelimFieldBuffer Courseregistration_Buffer;
	remove("CourseRegistration.dat");
	RecordFile<CourseRegistration> Cr_Rec2file (Courseregistration_Buffer);
	
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

	// 저장된 데이터 불러오 기 
	remove("CourseRegistration.dat");
	Cr_Rec2file.Create((char*)"CourseRegistration.dat",ios::out);
	for (int i = 0; i < 10 ; i++){
		Cr_Rec2file.Write(cr[i]);
	}
	
	Cr_Rec2file.Close();
	
	Cr_Rec2file.Open((char*)"CourseRegistration.dat", ios::in);
	i = 0;
	while (i < 10) {
		Cr_Rec2file.Read(cr[i]);
		cout << i+1 << endl;
		cout << cr[i++] << endl;
	}
	Cr_Rec2file.Close();
	
	
	// 데이터 누수 방지를 위해 포인터 해제 
	for (int i = 0; i < 10 ; i++){
		cr[i].delPointer();
	}
	
	return 0;
}
