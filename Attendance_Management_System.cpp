#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Attendance
{
    string name;
    int roll;
    int present;
    int leave;
    int half_day;
    int paid_leave;
    int overtime;
    float attendance;
};
// invalid input
void inputInt(string message, int &value)
{
    while(true)
    {
        cout << message;
        cin >> value;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid Input! Please enter numbers only.\n";
        }
        else
        {
            break;
        }
    }
}
int main()
{
    int n;
    int month, year;
    int total_days;
    int working_days;

    ofstream txt("Attendance_Report.txt");
    ofstream excel("Attendance_Report.csv");

    cout << "==============================\n";
    cout << " ATTENDANCE MANAGEMENT SYSTEM\n";
    cout << "==============================\n\n";

    inputInt("Enter Year : ", year);

    inputInt("Enter Month (1-12) : ",month);

    if(month==1 || month==3 || month==5 || month==7 ||
       month==8 || month==10 || month==12)
        total_days=31;

    else if(month==4 || month==6 || month==9 || month==11)
        total_days=30;

    else if(month==2)
    {
                if((year%400==0) || (year%4==0 && year%100!=0))
            total_days=29;
        else
            total_days=28;
    }

    else
    {
        cout<<"Invalid Month!";
        return 0;
    }

    cout<<"\nTotal Days in Month : "<<total_days<<endl;

    do
    {
        inputInt("Enter Total Working Days : ", working_days);

        if(working_days<1 || working_days>total_days)
        {
            cout<<"Invalid! Working days must be between 1 and "
                <<total_days<<endl;
        }

    }while(working_days<1 || working_days>total_days);

    inputInt("Enter Number of Students/Employees : ", n);

    Attendance data[20];

    for(int i=0;i<n;i++)
    {
        Attendance person;

        cout<<"\n-----------------------------------------";
        cout<<"\nEmployee "<<i+1;
        cout<<"\n-----------------------------------------";

        cin.ignore(1000,'\n');

        cout<<"\nEnter Name : ";
        getline(cin,person.name);

       inputInt("Roll No : ", person.roll);
        do
        {
            inputInt("Present Days : ", person.present);

            if(person.present<0 || person.present>working_days)
                cout<<"Invalid! Present Days must be between 0 and "
                    <<working_days<<endl;

        }while(person.present<0 || person.present>working_days);

        do
        {
            inputInt("Paid Leave : ", person.paid_leave);

            if(person.paid_leave<0 ||
               person.paid_leave>working_days-person.present)
                cout<<"Invalid Paid Leave!"<<endl;

        }while(person.paid_leave<0 ||
               person.paid_leave>working_days-person.present);

        do
        {
           inputInt("Leave Days : ", person.leave);
            if(person.leave<0 ||
               person.leave>working_days-
                            person.present-
                            person.paid_leave)
                cout<<"Invalid Leave Days!"<<endl;

        }while(person.leave<0 ||
               person.leave>working_days-
                            person.present-
                            person.paid_leave);

        int remaining;

        remaining = working_days -
                    person.present -
                    person.leave -
                    person.paid_leave;
        do
        {
           inputInt("Half Days : ", person.half_day);
            if(person.half_day < 0 || person.half_day > remaining*2)
            {
                cout << "Invalid! Maximum Half Days = "
                     << remaining*2 << endl;
            }

        }while(person.half_day < 0 || person.half_day > remaining*2);

        do
        {
           inputInt("Overtime Hours : ", person.overtime);

            if(person.overtime < 0)
            {
                cout << "Invalid! Overtime cannot be negative." << endl;
            }

        }while(person.overtime < 0);

        person.attendance =
        ((person.present +
          person.paid_leave +
          (person.half_day/2.0))
          / working_days) * 100;

        data[i] = person;
    }

    txt << "================ ATTENDANCE REPORT ================\n";
    txt << "Year : " << year << endl;
    txt << "Month : " << month << endl;
    txt << "Total Days : " << total_days << endl;
    txt << "Working Days : " << working_days << endl;
    txt << "===================================================\n\n";
        cout << "\n\n================ ATTENDANCE REPORT ================\n";
    cout << "Year : " << year << endl;
    cout << "Month : " << month << endl;
    cout << "Total Days : " << total_days << endl;
    cout << "Working Days : " << working_days << endl;

    cout << "--------------------------------------------------------------------------\n";
    cout << left << setw(20) << "Name"
         << setw(8) << "Roll"
         << setw(8) << "Present"
         << setw(8) << "Leave"
         << setw(8) << "Half"
         << setw(8) << "Paid"
         << setw(10) << "OT(Hrs)"
         << setw(10) << "Att(%)" << endl;
    cout << "--------------------------------------------------------------------------\n";

    txt << left << setw(20) << "Name"
        << setw(8) << "Roll"
        << setw(8) << "Present"
        << setw(8) << "Leave"
        << setw(8) << "Half"
        << setw(8) << "Paid"
        << setw(10) << "OT(Hrs)"
        << setw(10) << "Att(%)" << endl;

    txt << "--------------------------------------------------------------------------\n";

    excel << "Name,Roll,Present,Leave,Half Day,Paid Leave,Overtime,Attendance %\n";

    for(int i=0;i<n;i++)
    {
        cout << left << setw(20) << data[i].name
             << setw(8) << data[i].roll
             << setw(8) << data[i].present
             << setw(8) << data[i].leave
             << setw(8) << data[i].half_day
             << setw(8) << data[i].paid_leave
             << setw(10) << data[i].overtime
             << fixed << setprecision(2)
             << setw(10) << data[i].attendance << endl;

        txt << left << setw(20) << data[i].name
            << setw(8) << data[i].roll
            << setw(8) << data[i].present
            << setw(8) << data[i].leave
            << setw(8) << data[i].half_day
            << setw(8) << data[i].paid_leave
            << setw(10) << data[i].overtime
            << fixed << setprecision(2)
            << setw(10) << data[i].attendance << endl;

        excel << data[i].name << ","
              << data[i].roll << ","
              << data[i].present << ","
              << data[i].leave << ","
              << data[i].half_day << ","
              << data[i].paid_leave << ","
              << data[i].overtime << ","
              << fixed << setprecision(2)
              << data[i].attendance << "\n";
    }

    cout << "--------------------------------------------------------------------------\n";
    txt << "--------------------------------------------------------------------------\n";

    txt.close();
    excel.close();

    cout << "\nAttendance Report Saved Successfully!" << endl;
    cout << "1. Attendance_Report.txt" << endl;
    cout << "2. Attendance_Report.csv (Open with Microsoft Excel)" << endl;

    return 0;
}
