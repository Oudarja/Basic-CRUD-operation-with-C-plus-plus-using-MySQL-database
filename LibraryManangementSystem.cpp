#include<bits/stdc++.h>
#include<windows.h>
#include<mysql.h>

using namespace std;

const char* HOST="localhost";

const char* USER ="root";

const char* DB ="Library_Management_System";


class Student
{
private:
    string Id;

public:

    void setId(string id)
    {
        Id=id;
    }

    string getId()
    {
        return Id;
    }
};

class Library
{

private:
    string Name;
    int Quantity;

public:
    void setName(string name)
    {

        Name=name;
    }

    void setQuantity(int quantity)
    {
        Quantity=quantity;
    }

    int getQuantity()
    {

        return Quantity;
    }

    string getName()
    {
        return Name;
    }
};

void admin(MYSQL* conn,Library l,Student s)
{

    bool closed = false;

    while(!closed)
    {
        int choice;

        cout<<"\t\t\t\t                      \n";
        cout<<"\t\t\t\t|  1) Add Book       |\n";
        cout<<"\t\t\t\t|                    |\n";
        cout<<"\t\t\t\t|  2) Add Student    |\n";
        cout<<"\t\t\t\t|                    |\n";
        cout<<"\t\t\t\t|  0) Exit           |\n";
        cout<<"\t\t\t\t|                    |\n";
        cout<<"\t\t\t\t Please select:";

        cin>>choice;

        if(choice==1)
        {
            system("cls");

            string name;

            int quantity;

            cout<<"Book Name: ";

            //cin>>name;
            cin.ignore();
            getline(cin,name);

            l.setName(name);

            cout<<"Enter Quantity: ";

            cin>>quantity;

            l.setQuantity(quantity);

            int num=l.getQuantity();

            ///converting number to string
            stringstream st;
            string str;
            st<<num;
            st>>str;



            string book="Insert into library (Name,quantity) values('"+l.getName()+"','"+str+"')";

            if(mysql_query(conn,book.c_str()))
            {
                cout<<"Error: "<<mysql_error(conn)<<endl;
            }
            else
            {
                cout<<"Book Inserted Successfully";
            }
        }
        else if(choice==2)
        {
            system("cls");

            string  id;

            cout<<"Enter Srudent Id: ";

            cin>>id;

            s.setId(id);

            string st="Insert into student (Id) values ('"+s.getId()+"')";

            if(mysql_query(conn,st.c_str()))
            {
                cout<<"Error: "<<mysql_error(conn)<<endl;
            }
            else
            {
                cout<<"Student Inserted Successfully"<<endl;
            }
        }
        else
        {
            system("cls");
            closed=true;
            cout<<"Admin system is closing";
            system("cls");
        }
    }

}

///display

void display(MYSQL* conn)
{
    system("cls");

    ///display all books that are available
    cout<<"\t\t\t\tAvailable Books"<<endl;

    cout<<"\t\t\t\t________________"<<endl;

    string disp="Select * from library";

    if(mysql_query(conn,disp.c_str()))
    {
        cout<<"Errror: "<<mysql_error(conn)<<endl;
    }
    else
    {
        MYSQL_RES* res;

        res=mysql_store_result(conn);

        if(res)
        {
            int num=mysql_num_fields(res);

            MYSQL_ROW row;

            while(row=mysql_fetch_row(res))
            {
                for(int i=0; i<num; i++)
                {
                    cout<<row[i]<<' ';
                }
                cout<<endl;
            }
            mysql_free_result(res);
        }
    }
}


///Book function

int book(MYSQL* conn,string Bname)
{
    string exist="Select Name, Quantity from library where Name='"+Bname+"'";

    if(mysql_query(conn,exist.c_str()))
    {
        cout<<"Error: "<<mysql_error(conn)<<endl;

    }
    else
    {
        MYSQL_RES* res;

        res=mysql_store_result(conn);

        if(res)
        {
            ///No of columns
            int num=mysql_num_fields(res);

            MYSQL_ROW row;

            while(row=mysql_fetch_row(res))
            {
                if(Bname==row[0])
                {
                    ///converting string to number
                    stringstream st;
                    int num;
                    st<<row[1];
                    st>>num;
                    return num;
                }
            }

            cout<<"Book Not Found"<<endl;
        }

        ///As a c++ dveloper it is our duity to free the result also
        ///as it contains the whole result.
        mysql_free_result(res);

    }

    return 0;

}





///user function


void user(MYSQL* conn,Library l,Student s)
{

    system("cls");

    display(conn);

    string student_id;

    cout<<"Enter Your ID: ";

    cin>>student_id;

    string query="select * from student where id='"+student_id+"'";


    if(mysql_query(conn,query.c_str()))
    {
        cout<<"Error: "<<mysql_error(conn)<<endl;
    }
    else
    {
        MYSQL_RES* res;

        res=mysql_store_result(conn);
        if(res)
        {
            ///mysql_num_rows returns how many number of rows are in result
            int num=mysql_num_rows(res);

            if(num==1)
            {
                ///if there is one such rows
                /// then the student is valid for the library

                cout<<"Student ID Found"<<endl;
                ///The book that Student wants to find
                string Bname;
                cout<<"Enter Book Name: ";
                 cin.ignore();
                 getline(cin,Bname);

                if(book(conn,Bname)>0)
                {
                    int BookQuantity=book(conn,Bname)-1;
                    stringstream st;
                    string str;
                    st<<BookQuantity;
                    st>>str;

                    string upd="update library set quantity='"+str+"' where Name='"+Bname+"'";

                     if(mysql_query(conn,upd.c_str()))
                     {
                         cout<<"Error: "<<mysql_error(conn)<<endl;
                     }
                     else
                      {
                          cout<<"Book is available. Borrowing book"<<endl;
                     }
                }
                else
                {
                    cout<<"Book is not Available";
                }
            }
            else if(num==0)
            {
                cout<<"This Student is not Registered"<<endl;
            }
        }
    }

}


int main()
{

    Student s;

    Library l;


    MYSQL* conn;


    conn=mysql_init(0);

    if(!mysql_real_connect(conn,"localhost","root","","library_management_system",0,NULL,0))
    {

        cout<<"Error:"<<mysql_error(conn)<<endl;
    }
    else
    {
        cout<<"\t\t\t\t\t\t\tLOgged IN!"<<endl;
    }


    Sleep(3000);

    bool exit=false;

    while(!exit)
    {

        system("cls");
        int val;

        cout<<"\t\t\t\t________________________________\n";
        cout<<"\t\t\t\t________________________________\n";
        cout<<"\t\t\t\t   Welcome To Library Management System\n";
        cout<<"\t\t\t\t________________________________\n";
        cout<<"\t\t\t\t________________________________\n";
        cout<<"\t\t\t\t                                \n";
        cout<<"\t\t\t\t|  1) Administrator  |\n";
        cout<<"\t\t\t\t|                    |\n";
        cout<<"\t\t\t\t|  2) Buyer          |\n";
        cout<<"\t\t\t\t|                    |\n";
        cout<<"\t\t\t\t|  0) Exit           |\n";
        cout<<"\t\t\t\t|                    |\n";
        cout<<"\t\t\t\t Please select:";

        cin>>val;

        if(val==1)
        {
            admin(conn,l,s);
        }
        else if(val==2)
        {
            user(conn,l,s);
            //display(conn);
            Sleep(2000);
        }
        else
        {
            cout<<"\t\t\t\tLibrary Management System is closing";
            Sleep(3000);
            exit=true;
            system("cls");
        }

        Sleep(3000);

    }


    mysql_close(conn);


    return 0;
}
