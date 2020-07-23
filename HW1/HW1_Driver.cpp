#include "HW1_Student.h"
#include "HW1_CourseRegistration.h"
#include <time.h>
using namespace std;
/*
 * argv[1] : Student input if not exist input 0
 * argv[2] : Student input if not exist input 0
 */
int main(int argc, char* argv[]) {
	CourseRegistration cr[11];
	Student st[11];
	int i, j;
	srand(time(NULL));
	
	for (i = 0; i < 10; i++) {
		cr[i].setCourseRegistration(rand(), rand() % 3 + 1);
		st[i].setStudent(rand(), (char *)"lee jae yoon", (char *)"Pusan", time(NULL), rand() % 100 + 1);
	}
	cin >> cr[i];
	cin >> st[i];
	
	for (i = 0; i < 11; i++) {
		cr[i].addstudent(st[rand()%11]);
	}
		
	for (i = 0; i < 11; i++) {
		cout << "Class #" << i+1 << endl; 
		cout << cr[i] << endl;
		cout << "Student #" << i+1 << endl;
		cout << st[i] << endl;
	}
	return 0;
}
