#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#include<iostream>
using namespace std;
struct Student{
	int id;
	string name;
	float grade;
	int age;
};

class StudentDB{
	private:
		int DBsize;
		Student* st;
		int count;
	public:
		StudentDB(int size);
		void addStudent();
		void searchById(int id);
		void avgGradeofClass();
		void displayAll();
};
#endif
