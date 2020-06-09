#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

class book                           //Class BOOK
{
 private:
   char bno[6];
   char bname[50];
   char aname[20];
 public:
   void create_book()
   {
    clrscr();
    cout<<"\nNEW BOOK ENTRY...\n";
    cout<<"\nEnter the Book no.:";
    cin>>bno;
    cout<<"\n\nEnter the Name of the Book: ";
    gets(bname);
    cout<<"\n\nEnter the Author's Name: ";
    gets(aname);
    cout<<"\n\nBook Created..";
   }
   void show_book()
   {
    cout<<"\nBook No. : "<<bno;
    cout<<"\nBook Name: "<<bname;
    cout<<"\nAuthor Name: "<<aname;
   }
   void modify_book()
   {
    cout<<"\nBook No. : "<<bno;
    cout<<"\nModify Book Name : ";
    gets(bname);
    cout<<"\nModify Author's Name of the Book : ";
    gets(aname);
   }
   char* retbno()
   {
    return bno;
   }
   void report()
   {
    cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
   }
};

class student                        //Class Student
{
 private:
   char admno[6];
   char name[20];
   char stbno[6];
   int token;
 public:
   void create_student()
   {
    clrscr();
    cout<<"\nNEW STUDENT ENTRY...\n";
    cout<<"\nEnter the Admission No.: ";
    cin>>admno;
    cout<<"\n\nEnter the Name of the Student: ";
    gets(name);
    token=0;
    stbno[0]='/0';
    cout<<"\n\nStudent Record Created..";
   }
   void show_student()
   {
    cout<<"\nAdmission No.: "<<admno;
    cout<<"\nStudent Name: "<<name;
    cout<<"\nNo. of Books Issued: "<<token;
    if(token==1)
     cout<<"\nBook No.: "<<stbno;
   }
   void modify_student()
   {
    cout<<"\nAdmission No.: "<<admno;
    cout<<"\nModify Student Name: ";
    gets(name);
   }
   char* retadmno()
   {
    return admno;
   }
   char* retstbno()
   {
    return stbno;
   }
   int rettoken()
   {
    return token;
   }
   void addtoken()
   {
    token=1;
   }
   void resettoken()
   {
    token=0;
   }
   void getstbno(char t[])
   {
    strcpy(stbno,t);
   }
   void report()
   {
    cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;
   }
};
fstream fp;
fstream fp1;                     //File objects declarations
book bk;
student st;

void write_book()                    //Function to add books' record to file
{
 char ch;
 fp.open("book.dat", ios::out|ios::app);
 do
 {
  clrscr();
  bk.create_book();
  fp.write((char*)&bk, sizeof(book));
  cout<<"\n\nDo you want to add more records...(y/n)?  ";
  cin>>ch;
 }while(ch=='y' || ch=='Y');
 fp.close();
}

void write_student()               //Function to add students' record to file
{
 char ch;
 fp.open("student.dat", ios::out|ios::app);
 do
 {
  st.create_student();
  fp.write((char*)&st, sizeof(student));
  cout<<"\n\nDo yo want to add more records...(y/n)?  ";
  cin>>ch;
 }while(ch=='y'||ch=='Y');
 fp.close();
}

void display_spb(char n[])        //Function to read specific book from file
{
 cout<<"\nBOOK DETAILS\n";
 int flag=0;
 fp.open("book.dat", ios::in);
 while(fp.read((char*)&bk, sizeof(book)))
 {
  if(strcmp(bk.retbno(), n)==0)
  {
   bk.show_book();
   flag=1;
  }
 }
 fp.close();
 if(flag==0)
  cout<<"\n\nBook does not exist.";
 getch();
}

void display_sps(char n[])      //Function to read specific student from file
{
 cout<<"\nSTUDENT DETAILS\n";
 int flag=0;
 fp.open("student.dat", ios::in);
 while(fp.read((char*)&st, sizeof(student)))
 {
  if(strcmp(st.retadmno(), n)==0)
  {
   st.show_student();
   flag=1;
  }
 }
 fp.close();
 if(flag==0)
  cout<<"\n\nStudent does not exist.";
 getch();
}

void modify_book()                //Function to modify book record
{
 char n[6];
 int found=0;
 clrscr();
 cout<<"\n\n\tMODIFY BOOK RECORD...";
 cout<<"\n\n\tEnter the book no. of the book: ";
 cin>>n;
 fp.open("book.dat", ios::in|ios::out);
 while(fp.read((char*)&bk, sizeof(book)) && found==0);
 {
  if(strcmp(bk.retbno(), n)==0)
  {
   bk.show_book();
   cout<<"\nEnter the new details of the book."<<endl;
   bk.modify_book();
   int pos=(-1*sizeof(bk));
   fp.seekp(pos, ios::cur);
   fp.write((char*)&bk, sizeof(book));
   cout<<"\n\n\t Record Updated.";
   found=1;
  }
 }
 fp.close();
 if(found==0)
  cout<<"\n\nRecord Not Found.";
  getch();
}

void modify_student()                 //Function to modify student record
{
 char n[6];
 int found=0;
 clrscr();
 cout<<"\n\n\tMODIFY STUDENT RECORD...";
 cout<<"\n\nEnter the admission no. of the student : ";
 cin>>n;
 fp.open("student.dat", ios::in|ios::out);
 while(fp.read((char*)&st, sizeof(student)) && found==0)
 {
  if(strcmp(st.retadmno(), n)==0)
  {
   st.show_student();
   cout<<"\nEnter the new details of the student: "<<endl;
   st.modify_student();
   int pos=(-1*sizeof(st));
   fp.seekp(pos, ios::cur);
   fp.write((char*)&st, sizeof(student));
   cout<<"\n\n\t Record Updated.";
   found=1;
  }
 }
 fp.close();
 if(found==0)
  cout<<"\n\nRecord Not Found.";
 getch();
}

void delete_student()           //Function to delete record of a student
{
 char n[6];
 int flag=0;
 clrscr();
 cout<<"\n\n\tDELETE STUDENT...";
 cout<<"\n\nEnter the Admission No. of the student you want to delete: ";
 cin>>n;
 fp.open("student.dat", ios::in|ios::out);
 fstream fp2;
 fp2.open("temp.dat",ios::out);
 fp.seekg(0, ios::beg);
 while(fp.read((char*)&st, sizeof(student)))
 {
  if(strcmp(st.retadmno(), n)!=0)
   fp2.write((char*)&st, sizeof(student));
  else
   flag=1;
 }
 fp2.close();
 fp.close();
 remove("student.dat");
 rename("temp.dat", "student.dat");
 if(flag==1)
  cout<<"\n\n\tRecord Deleted.";
 else
  cout<<"\n\n\tRecord Not Found.";
 getch();
}

void delete_book()             //Function to delete book record
{
 char n[6];
 clrscr();
 cout<<"\n\n\n\tDelete Book...";
 cout<<"\n\nEnter the book no. of the book you want to delete: ";
 cin>>n;
 fp.open("book.dat", ios::in|ios::out);
 fstream fp2;
 fp2.open("temp.dat", ios::out);
 fp.seekg(0, ios::beg);
 while(fp.read((char*)&bk, sizeof(book)))
 {
  if(strcmp(bk.retbno(), n)!=0)
   fp2.write((char*)&bk, sizeof(book));
 }
 fp2.close();
 fp.close();
 remove("book.dat");
 rename("temp.dat", "book.dat");
 cout<<"\n\n\tRecord Deleted.";
 getch();
}

void display_alls()         //Function to display all the students
{
 clrscr();
 fp.open("student.dat", ios::in);
 if(!fp)
 {
  cout<<"\nERROR!!! File could not be open.";
  getch();
  return;
 }
 cout<<"\n\n\tSTUDENT LIST\n\n";
 cout<<"==================================================================\n";
 cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
 cout<<"==================================================================\n";
 while(fp.read((char*)&st, sizeof(student)))
 {
  st.report();
 }
 fp.close();
 getch();
}

void display_allb()         //Function to display all the books
{
 clrscr();
 fp.open("book.dat", ios::in);
 if(!fp)
 {
  cout<<"\nERROR!!! File could not be open. ";
  getch();
  return;
 }
 cout<<"\n\n\t\tBOOK LIST\n\n";
 cout<<"==================================================================\n";
 cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
 cout<<"==================================================================\n";
 while(fp.read((char*)&bk, sizeof(book)))
 {
  bk.report();
 }
 fp.close();
 getch();
}

void book_issue()            //Function to issue book
{
  char sn[6], bn[6];
  int found=0, flag=0;
  clrscr();
  cout<<"\n\nBOOK ISSUE...";
  cout<<"\n\n\tEnter the student's admission no.: ";
  cin>>sn;
  fp.open("student.dat", ios::in|ios::out);
  fp1.open("book.dat", ios::in|ios::out);
  while(fp.read((char*)&st, sizeof(student)) && found==0)
  {
   if(strcmp(st.retadmno(), sn)==0)
   {
    found=1;
    if(st.rettoken()==0)
    {
     cout<<"\n\n\tEnter the book no. ";
     cin>>bn;
     while(fp1.read((char*)&bk, sizeof(book)) && flag==0)
     {
      if(strcmp(bk.retbno(), bn)==0)
      {
       bk.show_book();
       flag=1;
       st.addtoken();
       st.getstbno(bk.retbno());
       int pos=(-1*sizeof(st));
       fp.seekp(pos, ios::cur);
       fp.write((char*)&st, sizeof(student));
       cout<<"\n\n\tBook issued successfully.\n\nPlease Note: Write current";
       cout<<" date in backside of book & submit within 15 days.";
       cout<<" Fine Rs 1 for each day after 15 days period.";
      }
     }
     if(flag==0)
      cout<<"\nBook does not exist";
    }
    else
     cout<<"\nYou have not retured the last book.";
   }
  }
  if(found==0)
   cout<<"\nStudent record does not exist.";
  getch();
  fp.close();
  fp1.close();
}

void book_deposit()      //Function to deposit book
{
 char sn[6], bn[6];
 int found=0, flag=0, day, fine;
 clrscr();
 cout<<"\n\nBOOK DEPOSIT...";
 cout<<"\n\n\tEnter the student's admission no.";
 cin>>sn;
 fp.open("student.dat", ios::in|ios::out);
 fp1.open("book.dat", ios::in|ios::out);
 while(fp.read((char*)&st, sizeof(student)) && found==0)
 {
  if(strcmp(st.retadmno(), sn)==0)
  {
   found=1;
   if(st.rettoken()==1)
   {
    while(fp1.read((char*)&bk, sizeof(book)) && flag==0)
    {
     if(strcmp(bk.retbno(), st.retstbno())==0)
     {
      bk.show_book();
      flag=1;
      cout<<"\n\nBook deposited in no of day: ";
      cin>>day;
      if(day>15)
      {
       fine=(day-15)*1;
       cout<<"\n\nFine has to deposited Rs. "<<fine;
      }
      st.resettoken();
      int pos=(-1*sizeof(st));
      fp.seekp(pos, ios::cur);
      fp.write((char*)&st, sizeof(student));
      cout<<"\n\n\tBook deposited successfully.";
     }
    }
    if(flag==0)
     cout<<"\nBook No. does not exist.";
   }
   else
   cout<<"\nNo book is issued..Please Check!!";
  }
 }
 if(found==0)
  cout<<"\nStudent record does not exist.";
 getch();
 fp.close();
 fp1.close();
}

void intro()           //Introduction Function
{
 clrscr();
 gotoxy(28,11);
 cout<<"LIBRARY MANAGEMENT SYSTEM";
 gotoxy(25, 13);
 cout<<"------------------------------";
 cout<<"\n\n\n\n\n\nMADE BY        : SWAPNIL JOHRI";
 getch();
}

void admin_menu()            //Function for Administrator Menu
{
 clrscr();
 int ch2;
 cout<<"\n\n\n\tAdministrator Menu";
 cout<<"\n\n\t1.Create Student Record";
 cout<<"\n\n\t2.Display All Student Record";
 cout<<"\n\n\t3.Display Specific Student Record";
 cout<<"\n\n\t4.Modify Student Record";
 cout<<"\n\n\t5.Delete Student Record";
 cout<<"\n\n\t6.Create Book";
 cout<<"\n\n\t7.Display All Books";
 cout<<"\n\n\t8.Display Specific Book";
 cout<<"\n\n\t9.Modify Book";
 cout<<"\n\n\t10.Delete Book";
 cout<<"\n\n\t11.Back to Main Menu";
 cout<<"\n\n\tPlease Enter Your Choice(1-11) : ";
 cin>>ch2;
 switch(ch2)
 {
  case 1: clrscr();
	  write_student();break;
  case 2: clrscr();
	  display_alls();
	  break;
  case 3:{
	  char num[6];
	  clrscr();
	  cout<<"\n\n\tPlease Enter the admission Number : ";
	  cin>>num;
	  display_sps(num);
	  break;
	 }
  case 4: modify_student();break;
  case 5: delete_student();break;
  case 6: clrscr();
	  write_book();break;
  case 7: clrscr();
	  display_allb();
	  break;
  case 8:{
	  char num[6];
	  clrscr();
	  cout<<"\n\n\tPlease Enter the Book No. : ";
	  cin>>num;
	  display_spb(num);
	  break;
	   }
  case 9: modify_book();break;
  case 10: delete_book();break;
  case 11: return;
  default: cout<<"\a";
 }
 admin_menu();
}

void main()                    //Main Function
{
 char ch;
 intro();
 do
 {
  clrscr();
  cout<<"\n\n\n\tMAIN MENU";
  cout<<"\n\n\t1.Book Issue";
  cout<<"\n\n\t2.Book Deposit";
  cout<<"\n\n\t3.Administrator Menu";
  cout<<"\n\n\t4.EXIT";
  cout<<"\n\n\tPlease Select Your Option(1-4)";
  cin>>ch;
  switch(ch)
  {
   case '1': clrscr();
	     book_issue();
	     break;
   case '2': book_deposit();
	     break;
   case '3': admin_menu();
	     break;
   case '4': exit(0);
   default : cout<<"\a";
  }
 }while(ch!=4);
}