#include<iostream>
#include "StudentDB.h"
using namespace std;
int main()
{
    int size,choice;
    cout<<"Enter max No. of Students in DB";
    cin>>size;
	StudentDB st(size);
	while (true)
	{

		cout << "1.Add Student" << endl
			 << "2.Search by ID" << endl
			 << "3.Average grade of all students" << endl
			 << "4.Display all students" << endl
			 << "5.Exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			st.addStudent();
			break;
		case 2:
		{
			cout << "Enter Student Id to Search: ";
			int sid;
			cin >> sid;
			st.searchById(sid);
		}
		break;
		case 3:
			st.avgGradeofClass();
			break;
		case 4:
			st.displayAll();
			break;
		case 5:
			cout << "Exiting the Program!!!" << endl;
			return 0;
		default:
			cout << "Invalid Input" << endl;
			break;
		}
	}
	return 0;
}
