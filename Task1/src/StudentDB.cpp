#include "StudentDB.h"

StudentDB::StudentDB(int size):DBsize(size),count(0){
	st =new Student[DBsize];
}

void StudentDB::addStudent()
{
	if (count < DBsize)
	{
		cout << "Enter student Id, Name, Age, Grade :" << endl;
		cin >> st[count].id >> st[count].name >> st[count].age >> st[count].grade;
		count++;
	}
	else
	{
		cout << "Reached maximum student count!" << endl;
	}
}

void StudentDB::searchById(int sid){
	
	for (int i = 0; i < count; i++)
	{
		if (st[i].id == sid)
		{
			cout << "Student Found!" << endl;
			cout << "Student Id" << st[i].id << endl
				 << "Student Name: " << st[i].name << endl
				 << "Student Age: " << st[i].age << endl
				 << "Student Grade: " << st[i].grade << endl;
			return;
		}
	}
	cout << "No record found with that ID!" << endl;
}
void StudentDB::avgGradeofClass()
{
	if (count > 0)
	{
		float total = 0.0;
		for (int i = 0; i < count; i++)
		{
			total += st[i].grade;
		}
		cout << "The Average grade of All Student: " << (total / (float)count) << endl;
	}
	else
	{
		cout << "The is no student st exist to calculate Avg!" << endl;
	}
}
void StudentDB::displayAll()
{
	cout << "Displaying all the student st" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << "Student Id: " << st[i].id << endl
			 << "Student Name: " << st[i].name << endl
			 << "Student Age: " << st[i].age << endl
			 << "Student Grade: " << st[i].grade << endl;
	}
}
