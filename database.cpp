//Write a C++ Program to create student record file
//Menu includes add, display, update, delete and search record functions.

#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

class Student
{
	int rno;
	char name[20], dept[20], course[10];
	char gen;
	
	public :
		void input();
		void display();
		int get_rno() { return rno;}
};

void Student :: input ()
{
	cout << "\n\n\n\t Enter Student Details :-\n";
	cout << "\t----------------------------------\n";
	cout << "\t Enter Roll no : ";
	cin >> rno;
	cout << "\t Enter Name: ";
	fflush (stdin);
	cin.getline (name , 20);
	cout << "\t Enter Department : ";
	fflush(stdin);
	cin.getline (dept , 20);
	cout << "\t Enter course : ";
	fflush (stdin);
	cin.getline (course , 10);
	cout << "\t Enter Gender : ";
	fflush(stdin);
	cin.get(gen);
}

void Student :: display()
{
	cout << "\t " << setw(6) << rno << "  ";
	cout << setw(20) << name;
	cout << setw(16) << dept;
	cout << setw(10) << course;
	cout << setw(8) << gen << endl;
}

main()
{
	Student s , s1;
	fstream file;
	ifstream inf;
	ofstream outf;
	int ch;
	int rno, f;
	int loc;
	
	do
	{
		system ("cls");
		cout << endl << endl << endl;
		cout << "\t\t-------------------------------------\n";
		cout << "\t\t                MENU\n";
		cout << "\t\t-------------------------------------\n";
		cout << "\t\t 1. Add a Record\n";
		cout << "\t\t 2. Display all Records\n";
		cout << "\t\t 3. Update a Record\n";
		cout << "\t\t 4. Delete a Record\n";
		cout << "\t\t 5. Search a Record\n";
		cout << "\t\t 6. Exit\n";
		cout << "\t\t-------------------------------------\n";
		
		cout << "\n\n\tYour Choice ? ";
		cin >> ch;
		
		switch (ch)
		{
			case 1 : s.input();
				file.open("Files/19_Student.txt", ios::app|ios::binary);
				file.write((char*)&s , sizeof(s));
				file.close();
				cout << "\n\n\tSTUDENT ADDED!!";
				break;
				
			case 2 : file.open("Files/19_Student.txt",ios::in|ios::binary);
				if(!file)
				{
					cout << "Error in Opening File!!";
					break;
				}
				
				system("cls");
				cout << "\n\n\t------------------------------------------------------------------\n";
				cout << "\t " << setw(8) << "ROLL NO.";
				cout << setw(20) << "NAME";
				cout << setw(16) << "DEPARTMENT";
				cout << setw(10) << "COURSE";
				cout << setw(8) << "GENDER" << endl;
				cout << "\t------------------------------------------------------------------\n";
				
				while (file.read((char*)&s , sizeof(s)))
					s.display();
				
				cout << "\t------------------------------------------------------------------\n";
				file.close();
				
				break;
			
			case 3 : cout << "\n\tEnter roll no of student to update : ";
				cin >> rno;
				
				cout << "\n\n\tENTER NEW DETAILS :";
				s1.input();

				file.open("Files/19_Student.txt", ios::binary|ios::ate|ios::in|ios::out);
				if(!file)
				{
					cout << "\n\tError in Opening File!!";
					break;
				}

				file.seekg(0);
				
				while (file.read((char*)&s , sizeof(s)))
					if(rno == s.get_rno())
					{
						int x = file.tellg();
						file.seekp(x - sizeof(s));
						file.write((char*)&s1 , sizeof(s1));
						break;
					}
									
				
				file.close();
				
				cout << "\n\tRECORD UPDATED!!";
				break;
							
			case 4 : cout << "\n\tEnter roll no of student to delete : ";
				cin >> rno;
				
				inf.open("Files/19_Student.txt", ios::binary);
				if(!inf)
				{
					cout << "\n\tError in Opening File!!";
					break;
				}
				
				outf.open("Files/19_Temp.txt" , ios::binary);
				while (inf.read((char*)&s , sizeof(s)))
					if(rno != s.get_rno())
						outf.write((char*)&s , sizeof(s));
				
				inf.close();
				outf.close();
				
				inf.open("Files/19_Temp.txt", ios::binary);
				if(!inf)
				{
					cout << "\n\tError in Opening File!!";
					break;
				}
				
				outf.open("Files/19_Student.txt" , ios::binary);
				while (inf.read((char*)&s , sizeof(s)))
					outf.write((char*)&s , sizeof(s));
				
				inf.close();
				outf.close();
				
				cout << "\n\tRECORD DELETED!!";
				break;
			
			case 5 : cout << "\n\tEnter roll no of student to search : ";
				cin >> rno;
				
				file.open("Files/19_Student.txt", ios::in|ios::binary);
				if(!file)
				{
					cout << "\n\tError in Opening File!!";
					break;
				}
				
				f=0;
				while (file.read((char*)&s , sizeof(s)))
				{
					if(rno == s.get_rno())
					{
						cout << "\n\tRECORD FOUND!!\n\n";
						s.display();
						f = 1;
						break;
					}
				}
				
				if (f == 0)
					cout << "\tRoll No. not found!!";
				file.close();
				
				break;
			
			case 6 : cout << "\n\n\t......THANK YOU......";
				exit(0);
				
			default : cout << "\n\n\tINVALID INPUT!!";
				cout << "\nENTER AGAIN!!";
				break;
		}
		
		cout << "\n\n\tPRESS ENTER TO CONTINUE : ";
		getch();
	}while (1);
	
	return 0;
}

