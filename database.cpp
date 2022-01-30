#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;
main()
{
    FILE *fp, *ft;
    char another;
    int choice;

    struct student
    {
        char first_name[50], last_name[50];
        char course[100];
        char section;
    };

    struct student e;
    char xfirst_name[50], xlast_name[50];
    long int recsize;

    fp=fopen("users.txt","rb+");

    if (fp == NULL)
    {
        fp = fopen("users.txt","wb+");

        if (fp==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }


    recsize = sizeof(e);

    while(1)
    {
        system("cls");

        cout << "\t\t==========================================\n";
        cout << "\t\t    STUDENT DATABASE MANAGEMENT SYSTEM\n";
        cout << "\t\t------------------------------------------";
        cout << "\n \t\t\t 1. Add    Records";
        cout << "\n \t\t\t 2. List   Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
        cout << "\n \t\t\t 5. Exit   Program\n";
        cout << "\t\t==========================================";
        cout << "\n\n";
        cout << "\t\t\t Your Choice ? ";
        cin >> choice;
        switch(choice)
        {
	        case 1 :
	            fseek(fp,0,SEEK_END);
	            another ='Y';
	            while(another == 'Y' || another == 'y')
	            {
	                system("cls");
	                cout << "Enter the First Name : ";
	                cin >> e.first_name;
	                cout << "Enter the Last Name  : ";
	                cin >> e.last_name;
	                cout << "Enter the Course     : ";
	                cin >> e.course;
	                cout << "Enter the Section    : ";
	                cin >> e.section;
	                fwrite(&e,recsize,1,fp);
	                cout << "\n Add Another Record (Y/N) ";
	                fflush(stdin);
	                another = getchar();
	            }
	            break;
	        case 2:
	            system("cls");
	            rewind(fp);
	            cout << "=== View the Records in the Database ===";
	            cout << "\n\n";
	            
	            cout << "=============================================================================================\n";
	            cout << setw(12) << "FIRST NAME" << setw(12) << "LAST NAME" << setw(12) << "COURSE" << setw (12) << "SECTION\n";
	            cout << "=============================================================================================\n";
	            
	            while (fread(&e,recsize,1,fp) == 1)
	            	cout << setw(12) << e.first_name << setw(12) << e.last_name << setw(12) << e.course << setw (12) << e.section << endl;
	            
	            cout << "\n\n";
	            break;
	
	        case 3 :
	            system("cls");
	            another = 'Y';
	            while (another == 'Y'|| another == 'y')
	            {
	                cout << "\n Enter the last name of the student : ";
	                cin >> xlast_name;
	
	                rewind(fp);
	                while (fread(&e,recsize,1,fp) == 1)
	                {
	                    if (strcmp(e.last_name,xlast_name) == 0)
	                    {
	                        cout << "Enter new the Firt Name : ";
	                        cin >> e.first_name;
	                        cout << "Enter new the Last Name : ";
	                        cin >> e.last_name;
	                        cout << "Enter new the Course    : ";
	                        cin >> e.course;
	                        cout << "Enter new the Section   : ";
	                        cin >> e.section;
	                        fseek(fp, - recsize, SEEK_CUR);
	                        fwrite(&e,recsize,1,fp);
	                        break;
	                    }
	                    else
	                        cout<<"record not found";
	                }
	                cout << "\n Modify Another Record (Y/N) ";
	                fflush(stdin);
	                another = getchar();
	            }
	            break;
	
	
	        case 4:
	            system("cls");
	            another = 'Y';
	            while (another == 'Y'|| another == 'y')
	            {
	                cout << "\n Enter the last name of the student to delete : ";
	                cin >> xlast_name;
	
	                ft = fopen("temp.dat", "wb");
	
	                rewind(fp);
	                while (fread (&e, recsize,1,fp) == 1)
	
	                    if (strcmp(e.last_name,xlast_name) != 0)
	                    {
	                        fwrite(&e,recsize,1,ft);
	                    }
	                fclose(fp);
	                fclose(ft);
	                remove("users.txt");
	                rename("temp.dat","users.txt");
	
	                fp=fopen("users.txt","rb+");
	
	                cout << "\n Delete Another Record (Y/N) ";
	                fflush(stdin);
	                another = getchar();
	            }
	
	            break;
	
	        case 5:
	            fclose(fp);
	            cout << "\n\n";
	            cout << "\t\t     THANK YOU FOR USING THIS SOFTWARE";
	            cout << "\n\n";
	            exit(0);
	            
	        default : cout << "INVALID INPUT!!\nENTER AGAIN!!";
	        
        }
        cout << "Press Enter to continue ... ";
        getch();
    }

    return 0;
}