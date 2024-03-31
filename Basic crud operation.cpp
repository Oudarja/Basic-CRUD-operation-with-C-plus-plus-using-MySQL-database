///Basic CRUD operation using mysql in c++
///C---> Creating
///R---> Read
///U---> Update
///D---> Delete
#include<iostream>
#include<Windows.h>
#include<mysql.h>
#include<iomanip>
#include<stdlib.h>
#include<sstream>
#include<stdio.h>
using namespace std;

int main()
{

    MYSQL* conn;
    MYSQL_RES *res;

    int qstate;

    conn=mysql_init(0);

    /// Creating connection with Database
    conn=mysql_real_connect(conn,"localhost","root","","tutorial",0,NULL,0);

    if(conn)
    {
        cout<<"\t\t\t\tConnection to database is successful!!!\n\n";
    }
    else
    {
        cout<<"Error data is not inserted ...\n";
        cout << "Error: " << mysql_error(conn);
    }

    bool exit=false;


    if(conn)
    {
        Sleep(3000);
        bool allok=true;
        while(!exit)
        {
            if(allok)
                system("cls");
            int val;
            cout<<"\t\t Welcome To MySQL Database"<<endl;
            cout<<"\t\t *************************"<<endl;
            cout<<"\t\t 1. Insert Data."<<endl;
            cout<<"\t\t 2. Delete Data."<<endl;
            cout<<"\t\t 3. Update Data."<<endl;
            cout<<"\t\t 4. Get/Read Data."<<endl;
            cout<<"\t\t 5. Exit. \n\n\n";
            cout<<"\t\t..................... Enter Choice:...................... "<<endl;
            cout<<"\t\t";
            cin>>val;

            if(val==1)
            {
                system("cls");
                string f_name,l_name,username,password;
                cout<<"\t\t 1) Enter your first name"<<'\n';
                cout<<"\t\t ";
                cin>>f_name;
                cout<<"\t\t 2) Enter your last name"<<'\n';
                cout<<"\t\t ";
                cin>>l_name;
                cout<<"\t\t 3) Enter your user-name"<<'\n';
                cout<<"\t\t ";
                cin>>username;
                cout<<"\t\t 4) Enter your password"<<'\n';
                cout<<"\t\t ";
                cin>>password;

                stringstream ss;

                ///If there is space in column name then there should be used backticks to enclose them other wise error will be generated
                ss<<"INSERT INTO registration (`First name`,`Last name`,`User name`,Password) values ('"+f_name+"','"+l_name+"','"+username+"','"+password+"')";

                ///So query is a string representing the query which is known as query string
                string query=ss.str();
                /// this line of code is converting the query string (which contains the SQL query)
                /// into a C-style string (null-terminated character array) and obtaining a pointer
                ///to it. This pointer can then be used in functions or APIs that expect C-style
                /// strings, such as the mysql_query function used to execute the SQL query on the
                ///MySQL database connection.
                const char *q=query.c_str();
                qstate=mysql_query(conn,q);

                if(qstate==0)
                {
                    cout<<"\t\t.....................Record inserted successfully.....................";
                    Sleep(3000);
                }
                else
                {
                    allok=false;
                    cout<<"Error data is not inserted ...\n";
                    cout << "Error: " << mysql_error(conn);
                }
            }
            else if(val==2)
            {
                system("cls");
                int id;
                cout<<"\t\t Enter ID to delete"<<'\n';
                cout<<"\t\t ";
                cin>>id;
                string del="Delete from registration where Id='"+to_string(id)+"'";

                if(mysql_query(conn,del.c_str()))
                {

                    allok=false;
                    cout<<"Error data is not Deleted ...\n";
                    cout << "Error: " << mysql_error(conn);
                }
                else
                {

                    cout<<"\t\t.....................Record deleted successfully.....................";
                    Sleep(3000);
                }
            }
            else if(val==3)
            {
                system("cls");
                string id,password;

                cout<<"\t\t Enter Id to update: ";
                cin>>id;
                cout<<"\t\t Enter new password";
                cin>>password;

                string upd="Update registration set Password='"+password+"' where Id='"+id+"'";
                           if(mysql_query(conn,upd.c_str()))
                {

                    allok=false;
                    cout<<"Error update failure ...\n";
                    cout << "Error: " << mysql_error(conn);
                }
                else
                {

                    cout<<"\t\t.....................Record updated successfully.....................";
                    Sleep(3000);
                }
            }
            else if(val==4)
            {
                system("cls");
                string get="Select * from registration";
                if(mysql_query(conn,get.c_str()))
                {

                    allok=false;
                    cout<<"Error data reading is not done ...\n";
                    cout << "Error: " << mysql_error(conn);
                }
                else
                {
                    ///It is a api function to get data from database

                    MYSQL_RES* result=mysql_store_result(conn);

                    ///If there is any results
                    if(result)
                    {
                        ///counting number of column or field in db
                        int num=mysql_num_fields(result);

                        MYSQL_ROW row;
                        cout<<endl<<endl;

                        while(row=mysql_fetch_row(result))
                        {
                            for(int i=0;i<num;i++)
                            {
                                cout<<row[i]<<'\n';
                            }
                        }
                        mysql_free_result(result);
                    }

                    cout<<"\t\t.....................Record retrieved successfully.....................";
                    Sleep(10000);
                }
            }
            else
            {
                system("cls");
                exit=true;
                cout<<endl<<endl<<endl;
                cout<<"\t\t BYE!"<<endl;
                Sleep(3000);
            }
        }
    }

    mysql_close(conn);

    return 0;

}
