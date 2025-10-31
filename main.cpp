#include <iostream>
#include <fstream>     // this is for reading and writing files
#include <string>
#include <sstream>// this helps us split strings and parse CSV data
using namespace std;

class Person {
protected:
    string name;
    int id;
public:
    Person() {
        name = "";
        id = 0;
    }

    Person(string n, int i) {
        name = n;
        id = i;
    }

    // copy constructor - makes a new Person by copying another Person
    Person(const Person& p) {
        name = p.name;    // copy the name from the other person
        id = p.id;        // copy the ID from the other person
    }

    void getPersonalInfo() {  // function to get user input for person details
        cout << "Enter name: ";       // ask user for name
        cin.ignore();                 // this clears the input buffer (important!)
        getline(cin, name);           // read the whole line including spaces
        cout << "Enter ID: ";         // ask user for ID number
        cin >> id;                    // read the ID number
    }

    void displayPersonalInfo() {  // function to show person's basic info
        cout << "Name: " << name << endl;
            cout <<"ID: " << id << endl;  // print name and ID
    }

    ~Person() {       // destructor - runs when Person object is destroyed
        cout << "Person destructor called for " << name << endl;
    }
};

// class to handle time records for attendance
class TimeRecord {
protected:            // child classes can access these
    string inTime;    // when person came in
    string outTime;   // when person left
public:
    TimeRecord() {    // default constructor
        inTime = "00:00";     // default check-in time
        outTime = "00:00";    // default check-out time
    }

    void setInTime(string time) {  // setter function for in-time
        inTime = time;             // store the time that was passed in
    }

    void setOutTime(string time) { // setter function for out-time
        outTime = time;            // store the time that was passed in
    }

    string getInTime() {  // getter function to return in-time
        return inTime;    // give back the stored in-time
    }

    string getOutTime() { // getter function to return out-time
        return outTime;   // give back the stored out-time
    }

    ~TimeRecord() {       // destructor for TimeRecord
        cout << "TimeRecord destructor called" << endl;
    }
};

// this class handles attendance calculations and inherits from TimeRecord
class Attendance : public TimeRecord {
protected:                // child classes can access these variables
    int lateInMinutes;    // how many minutes late person was
    int earlyGoMinutes;   // how many minutes early person left
    int shortHours;       // how many hours short of full workday
    int excessHours;      // how many extra hours worked
public:
    Attendance() {        // default constructor
        lateInMinutes = 0;    // start with 0 late minutes
        earlyGoMinutes = 0;   // start with 0 early minutes
        shortHours = 0;       // start with 0 short hours
        excessHours = 0;      // start with 0 excess hours
    }

    void calculateLateIn() {  // function to calculate if person was late
        // this is a simple check - if came after 9:00 AM then late
        if (inTime > "09:00") {    // string comparison works for HH:MM format
            lateInMinutes = 30;    // just assume 30 minutes late (simplified)
        } else {
            lateInMinutes = 0;     // not late if arrived on time or early
        }
    }

    void calculateEarlyGo() { // function to check if person left early
        // if left before 5:00 PM then they left early
        if (outTime < "17:00") {    // 17:00 is 5 PM in 24-hour format
            earlyGoMinutes = 30;    // assume 30 minutes early (simplified)
        } else {
            earlyGoMinutes = 0;     // not early if left at or after 5 PM
        }
    }

    void calculateShortAndExcessHours() {  // calculate work hour differences
        int totalMinutes = 480;    // 8 hours = 480 minutes (standard workday)
        int workedMinutes = 450;   // simplified - assume they worked 7.5 hours

        if (workedMinutes < totalMinutes) {  // if worked less than 8 hours
            shortHours = (totalMinutes - workedMinutes) / 60;    // convert to hours
            excessHours = 0;    // no excess hours if they worked short
        } else {                // if worked 8 hours or more
            shortHours = 0;     // no short hours
            excessHours = (workedMinutes - totalMinutes) / 60;   // calculate overtime
        }
    }

    void displayAttendanceReport() {  // function to show attendance summary
        cout << "\n--- Attendance Report ---" << endl;    // nice header
        cout << "In Time: " << inTime << endl;            // show check-in time
        cout << "Out Time: " << outTime << endl;          // show check-out time
        cout << "Late In Minutes: " << lateInMinutes << endl;      // show late minutes
        cout << "Early Go Minutes: " << earlyGoMinutes << endl;    // show early departure
        cout << "Short Hours: " << shortHours << endl;            // show short hours
        cout << "Excess Hours: " << excessHours << endl;          // show overtime
    }

    // getter functions so other classes can access private data
    int getLateInMinutes() { return lateInMinutes; }     // return late minutes
    int getEarlyGoMinutes() { return earlyGoMinutes; }   // return early minutes
    int getShortHours() { return shortHours; }           // return short hours
    int getExcessHours() { return excessHours; }         // return excess hours

    ~Attendance() {       // destructor
        cout << "Attendance destructor called" << endl;
    }
};

// Teacher class inherits from both Person and Attendance (multiple inheritance)
class Teacher : public Person, public Attendance {
private:              // only this class can access these
    string subject;   // what subject teacher teaches
    string department; // which department teacher belongs to
public:
    Teacher() {       // default constructor
        subject = "";     // empty subject initially
        department = "";  // empty department initially
    }

    Teacher(string n, int i, string sub, string dept) : Person(n, i) {
        subject = sub;    // set subject
        department = dept; // set department
    }
    // copy constructor
    Teacher(const Teacher& t) : Person(t) {  // call Person copy constructor
        subject = t.subject;       // copy subject
        department = t.department; // copy department
    }

    void getTeacherDetails() {    // function to get all teacher info from user
        getPersonalInfo();        // call inherited function to get name and ID
        cout << "Enter subject: ";    // ask for subject
        cin.ignore();                 // clear input buffer
        getline(cin, subject);        // read subject (may have spaces)
        cout << "Enter department: "; // ask for department
        getline(cin, department);     // read department (may have spaces)

        string time;                  // temporary variable for time input
        cout << "Enter in-time (HH:MM): ";  // ask for check-in time
        cin >> time;                  // read time
        setInTime(time);             // call inherited function to store in-time
        cout << "Enter out-time (HH:MM): "; // ask for check-out time
        cin >> time;                  // read time
        setOutTime(time);            // call inherited function to store out-time

        // now calculate all the attendance stuff
        calculateLateIn();           // figure out if they were late
        calculateEarlyGo();          // figure out if they left early
        calculateShortAndExcessHours();  // calculate hour differences
    }

    void displayTeacherInfo() {   // function to show all teacher information
        cout << "\n--- Teacher Information ---" << endl;  // nice header
        displayPersonalInfo();       // call inherited function to show name/ID
        cout << "Subject: " << subject << endl;          // show subject
        cout << "Department: " << department << endl;    // show department
        displayAttendanceReport();   // call inherited function to show attendance
    }

    void saveToFile() {           // function to save teacher data to file
        ofstream file("teachers.txt", ios::app);    // open file in append mode
        if (file.is_open()) {     // check if file opened successfully
            // write all data in CSV format (comma separated values)
            file << name << "," << id << "," << subject << "," << department << ","
                 << inTime << "," << outTime << "," << lateInMinutes << ","
                 << earlyGoMinutes << "," << shortHours << "," << excessHours << endl;
            file.close();         // close the file
            cout << "Teacher data saved to file successfully!" << endl;    // success message
        } else {
            cout << "Error: Could not open file for writing!" << endl;    // error message
        }
    }

    void readFromFile(int searchId) {  // function to find and load teacher from file
        ifstream file("teachers.txt");    // open file for reading
        string line;                      // variable to store each line
        bool found = false;               // flag to track if we found the teacher

        if (file.is_open()) {     // check if file opened
            while (getline(file, line)) {    // read each line from file
                stringstream ss(line);       // create stringstream to parse CSV
                string item;                 // temporary variable for each field

                // parse the CSV line - extract each field
                getline(ss, name, ',');      // get name (first field)
                getline(ss, item, ',');      // get ID as string
                id = stoi(item);             // convert string to integer

                if (id == searchId) {        // if this is the teacher we want
                    // extract all the remaining fields
                    getline(ss, subject, ',');       // get subject
                    getline(ss, department, ',');    // get department
                    getline(ss, inTime, ',');        // get in-time
                    getline(ss, outTime, ',');       // get out-time
                    getline(ss, item, ',');          // get late minutes as string
                    lateInMinutes = stoi(item);      // convert to integer
                    getline(ss, item, ',');          // get early minutes
                    earlyGoMinutes = stoi(item);     // convert to integer
                    getline(ss, item, ',');          // get short hours
                    shortHours = stoi(item);         // convert to integer
                    getline(ss, item);               // get excess hours (last field)
                    excessHours = stoi(item);        // convert to integer

                    found = true;    // mark that we found the teacher
                    break;           // exit the while loop
                }
            }
            file.close();    // close the file

            if (found) {     // if we found the teacher
                cout << "Teacher data loaded successfully!" << endl;    // success message
                displayTeacherInfo();    // show the teacher information
            } else {
                cout << "Teacher with ID " << searchId << " not found!" << endl;    // not found
            }
        } else {
            cout << "Error: Could not open file for reading!" << endl;    // file error
        }
    }

    void updateInFile(int searchId) { // function to update teacher data in file
        ifstream file("teachers.txt");    // open original file for reading
        ofstream tempFile("temp.txt");    // create temporary file for writing
        string line;                      // variable for each line
        bool found = false;               // flag to track if teacher found

        if (file.is_open() && tempFile.is_open()) {    // check both files opened
            while (getline(file, line)) {    // read each line from original
                stringstream ss(line);       // parse the line
                string item;                 // temporary variable
                getline(ss, item, ',');      // get name
                string tempName = item;      // store name
                getline(ss, item, ',');      // get ID
                int tempId = stoi(item);     // convert to integer

                if (tempId == searchId) {    // if this is the teacher to update
                    cout << "Updating teacher with ID " << searchId << endl;
                    getTeacherDetails();     // get new details from user
                    // write updated data to temp file
                    tempFile << name << "," << id << "," << subject << "," << department << ","
                             << inTime << "," << outTime << "," << lateInMinutes << ","
                             << earlyGoMinutes << "," << shortHours << "," << excessHours << endl;
                    found = true;    // mark as found and updated
                } else {
                    tempFile << line << endl;    // copy unchanged line to temp file
                }
            }
            file.close();      // close original file
            tempFile.close();  // close temp file

            // replace original file with updated temp file
            remove("teachers.txt");              // delete original file
            rename("temp.txt", "teachers.txt");  // rename temp to original name

            if (found) {
                cout << "Teacher data updated successfully!" << endl;
            } else {
                cout << "Teacher with ID " << searchId << " not found!" << endl;
            }
        } else {
            cout << "Error: Could not open files for updating!" << endl;
        }
    }

    void deleteFromFile(int searchId) {  // function to delete teacher from file
        ifstream file("teachers.txt");    // open original file
        ofstream tempFile("temp.txt");    // create temp file
        string line;                      // variable for each line
        bool found = false;               // flag to track if found

        if (file.is_open() && tempFile.is_open()) {    // check both files opened
            while (getline(file, line)) {    // read each line
                stringstream ss(line);       // parse the line
                string item;                 // temp variable
                getline(ss, item, ',');      // skip name
                getline(ss, item, ',');      // get ID
                int tempId = stoi(item);     // convert to integer

                if (tempId != searchId) {    // if this is NOT the teacher to delete
                    tempFile << line << endl;    // copy line to temp file (keep it)
                } else {
                    found = true;    // mark that we found and skipped (deleted) it
                }
            }
            file.close();      // close original
            tempFile.close();  // close temp

            // replace original with temp (without deleted teacher)
            remove("teachers.txt");              // delete original
            rename("temp.txt", "teachers.txt");  // rename temp to original

            if (found) {
                cout << "Teacher data deleted successfully!" << endl;
            } else {
                cout << "Teacher with ID " << searchId << " not found!" << endl;
            }
        } else {
            cout << "Error: Could not open files for deletion!" << endl;
        }
    }

    // getter functions so other classes can access private data
    string getName() { return name; }           // return teacher name
    int getId() { return id; }                  // return teacher ID
    string getSubject() { return subject; }     // return subject taught
    string getDepartment() { return department; } // return department

    ~Teacher() {      // destructor
        cout << "Teacher destructor called" << endl;
    }
};

// Admin class - for administrators who manage the system
class Admin : public Person {  // inherits from Person
private:
    string role;      // admin's role/position
public:
    Admin() {         // default constructor
        role = "";    // empty role initially
    }

    // constructor with parameters
    Admin(string n, int i, string r) : Person(n, i) {  // call Person constructor
        role = r;     // set the role
    }

    void manageTeachers() {   // function for managing teachers
        cout << "Managing teacher records..." << endl;  // just a placeholder message
    }

    void viewReports() {      // function to view all teacher reports
        cout << "\n--- All Teachers Report ---" << endl;    // header
        ifstream file("teachers.txt");    // open teachers file
        string line;                      // variable for each line

        if (file.is_open()) {     // if file opened successfully
            // print header row for CSV data
            cout << "Name;   ID;   Subject;   Department;   InTime;   OutTime;   LateMinutes;   EarlyMinutes;   ShortHours;   ExcessHours" << endl;
            while (getline(file, line)) {    // read and print each line
                cout << line << endl;        // print the teacher data
            }
            file.close();    // close file
        } else {
            cout << "No teacher records found!" << endl;    // error message
        }
    }

    ~Admin() {        // destructor
        cout << "Admin destructor called" << endl;  // debug message
    }
};

// Department class - represents a department in the university
class Department : protected Teacher {  // protected inheritance from Teacher
private:
    string departmentName;    // name of the department
    int numberOfTeachers;     // how many teachers in this department
public:
    Department() {            // default constructor
        departmentName = "";  // empty name initially
        numberOfTeachers = 0; // zero teachers initially
    }

    void setDepartmentInfo(string name, int count) {  // function to set department info
        departmentName = name;      // set department name
        numberOfTeachers = count;   // set teacher count
    }

    void displayDepartmentInfo() {  // function to show department info
        cout << "\n--- Department Information ---" << endl;
        cout << "Department Name: " << departmentName << endl;
        cout << "Number of Teachers: " << numberOfTeachers << endl;
    }

    ~Department() {           // destructor
        cout << "Department destructor called" << endl;
    }
};

// ReportGenerator class - generates various reports from teacher data
class ReportGenerator {
private:
    string reportDate;        // date for the report
public:
    ReportGenerator() {       // default constructor
        reportDate = "2024-01-01";  // set default report date
    }

    void generateDailyReport() {  // function to generate daily attendance report
        cout << "\n=== DAILY ATTENDANCE REPORT ===" << endl;
        cout << "Report Date: " << reportDate << endl;

        ifstream file("teachers.txt");    // open teachers file
        string line;                      // variable for each line
        int teacherCount = 0;             // counter for teachers

        if (!file.is_open()) {            // if file didn't open
            cout << "No teacher records found! Please add some teachers first." << endl;
            return;                       // exit function early
        }

        cout << "\n--- Today's Attendance Summary ---" << endl;

        while (getline(file, line)) {     // read each line from file
            teacherCount++;               // increment counter
            stringstream ss(line);        // create stringstream to parse CSV
            string item;                  // temp variable

            // parse all the CSV fields
            getline(ss, item, ',');  string name = item;        // get name
            getline(ss, item, ',');  string id = item;          // get ID
            getline(ss, item, ',');  string subject = item;     // get subject
            getline(ss, item, ',');  string department = item;  // get department
            getline(ss, item, ',');  string inTime = item;      // get in-time
            getline(ss, item, ',');  string outTime = item;     // get out-time
            getline(ss, item, ',');  string lateMinutes = item; // get late minutes
            getline(ss, item, ',');  string earlyMinutes = item;// get early minutes
            getline(ss, item, ',');  string shortHours = item;  // get short hours
            getline(ss, item);       string excessHours = item; // get excess hours

            // display all the info for this teacher
            cout << "\nTeacher " << teacherCount << ":" << endl;
            cout << "Name: " << name << ", ID: " << id << endl;
            cout << "Subject: " << subject << ", Department: " << department << endl;
            cout << "In Time: " << inTime << ", Out Time: " << outTime << endl;
            cout << "Late Minutes: " << lateMinutes << ", Early Go Minutes: " << earlyMinutes << endl;
            cout << "Short Hours: " << shortHours << ", Excess Hours: " << excessHours << endl;
            cout << "----------------------------------------" << endl;
        }

        file.close();         // close the file
        cout << "\nTotal Teachers in System: " << teacherCount << endl;
    }

    void generateMonthlySummary() {   // function to generate monthly summary
        cout << "\n=== MONTHLY SUMMARY REPORT ===" << endl;

        ifstream file("teachers.txt");    // open file
        string line;                      // variable for lines

        if (!file.is_open()) {            // if file didn't open
            cout << "No teacher records found! Please add some teachers first." << endl;
            return;                       // exit early
        }

        // variables to accumulate totals
        int totalTeachers = 0;            // total number of teachers
        int totalLateInstances = 0;       // how many teachers were late
        int totalEarlyDepartures = 0;     // how many left early
        int totalShortHours = 0;          // total short hours across all
        int totalExcessHours = 0;         // total excess hours across all

        // read through file and calculate totals
        while (getline(file, line)) {
            totalTeachers++;              // count this teacher
            stringstream ss(line);        // parse the line
            string item;                  // temp variable

            // skip to the attendance data (skip first 6 fields)
            for (int i = 0; i < 6; i++) {
                getline(ss, item, ',');   // skip name, id, subject, dept, inTime, outTime
            }

            // get the attendance numbers
            getline(ss, item, ',');  int lateMinutes = stoi(item);   // late minutes
            getline(ss, item, ',');  int earlyMinutes = stoi(item);  // early minutes
            getline(ss, item, ',');  int shortHours = stoi(item);    // short hours
            getline(ss, item);       int excessHours = stoi(item);   // excess hours

            // accumulate the totals
            totalLateInstances += (lateMinutes > 0) ? 1 : 0;     // count if late
            totalEarlyDepartures += (earlyMinutes > 0) ? 1 : 0;  // count if early
            totalShortHours += shortHours;                       // add short hours
            totalExcessHours += excessHours;                     // add excess hours
        }

        file.close();                     // close file

        // display the summary statistics
        cout << "Total Teachers: " << totalTeachers << endl;
        cout << "Teachers with Late Arrivals: " << totalLateInstances << endl;
        cout << "Teachers with Early Departures: " << totalEarlyDepartures << endl;
        cout << "Total Short Hours Across All Teachers: " << totalShortHours << endl;
        cout << "Total Excess Hours Across All Teachers: " << totalExcessHours << endl;

        // calculate and display percentages
        if (totalTeachers > 0) {          // avoid division by zero
            double latePercentage = (double)totalLateInstances / totalTeachers * 100;
            double earlyPercentage = (double)totalEarlyDepartures / totalTeachers * 100;

            cout << "\n--- Performance Statistics ---" << endl;
            cout << "Late Arrival Rate: " << latePercentage << "%" << endl;
            cout << "Early Departure Rate: " << earlyPercentage << "%" << endl;
            cout << "On-time Arrival Rate: " << (100 - latePercentage) << "%" << endl;
        }
    }

    void generateUserSelectedDateSummary() { // function for custom date range report
        string startDate, endDate;            // variables for date input
        cout << "Enter start date (YYYY-MM-DD): ";
        cin >> startDate;                     // get start date from user
        cout << "Enter end date (YYYY-MM-DD): ";
        cin >> endDate;                       // get end date from user

        cout << "\n=== DATE RANGE SUMMARY REPORT ===" << endl;
        cout << "From: " << startDate << " To: " << endDate << endl;

        ifstream file("teachers.txt");        // open file

        if (!file.is_open()) {                // if file didn't open
            cout << "No teacher records found for the selected date range!" << endl;
            return;                           // exit early
        }

        // count teachers in file
        string line;
        int teacherCount = 0;
        while (getline(file, line)) {
            teacherCount++;                   // count each line
        }
        file.close();                         // close file

        cout << "Teachers in system during this period: " << teacherCount << endl;
        cout << "Note: This is a simplified implementation. In a real system, " << endl;
        cout << "date filtering would be implemented based on actual attendance dates." << endl;

        // for now just show monthly summary
        generateMonthlySummary();
    }

    ~ReportGenerator() {                      // destructor
        cout << "ReportGenerator destructor called" << endl;  // debug message
    }
};

int main() {                                  // main function - program starts here
    cout << "=== University Attendance Tracking System ===" << endl;  // welcome message
    int choice;                               // variable to store user's menu choice
    Teacher teacher;                          // create Teacher object
    Admin admin("Admin", 1001, "Head");      // create Admin object with data
    Department dept;                          // create Department object
    ReportGenerator reportGen;                // create ReportGenerator object

    do {                                      // start menu loop
        // display the main menu options
        cout << "\n--- MAIN MENU ---" << endl;
        cout << "1. Add Teacher" << endl;
        cout << "2. View Teacher" << endl;
        cout << "3. Update Teacher" << endl;
        cout << "4. Delete Teacher" << endl;
        cout << "5. View All Teachers (Admin)" << endl;
        cout << "6. Generate Daily Report" << endl;
        cout << "7. Generate Monthly Summary" << endl;
        cout << "8. Department Info" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;                        // get user's choice

        switch(choice) {                      // handle different menu choices
            case 1: {                         // Add new teacher
                cout << "\n--- Add New Teacher ---" << endl;
                teacher.getTeacherDetails();  // get teacher info from user
                teacher.saveToFile();         // save to file
                break;                        // exit this case
            }
            case 2: {                         // View existing teacher
                int id;                       // variable for teacher ID
                cout << "Enter Teacher ID to view: ";
                cin >> id;                    // get ID from user
                teacher.readFromFile(id);     // find and display teacher
                break;                        // exit this case
            }
            case 3: {                         // Update teacher
                int id;                       // variable for teacher ID
                cout << "Enter Teacher ID to update: ";
                cin >> id;                    // get ID from user
                teacher.updateInFile(id);     // update teacher in file
                break;                        // exit this case
            }
            case 4: {                         // Delete teacher
                int id;                       // variable for teacher ID
                cout << "Enter Teacher ID to delete: ";
                cin >> id;                    // get ID from user
                teacher.deleteFromFile(id);   // delete teacher from file
                break;                        // exit this case
            }
            case 5: {                         // View all teachers (admin function)
                admin.viewReports();          // call admin's view function
                break;                        // exit this case
            }
            case 6: {                         // Generate daily report
                reportGen.generateDailyReport();     // generate and show daily report
                break;                        // exit this case
            }
            case 7: {                         // Generate monthly summary
                reportGen.generateMonthlySummary();  // generate and show monthly summary
                break;                        // exit this case
            }
            case 8: {                         // Show department info
                dept.setDepartmentInfo("Computer Science", 10);    // set sample data
                dept.displayDepartmentInfo();                      // display dept info
                break;                        // exit this case
            }
            case 9: {                         // Exit program
                cout << "Exiting system... Goodbye!" << endl;
                break;                        // exit this case
            }
            default: {                        // Invalid choice
                cout << "Invalid choice! Please try again." << endl;
            }
        }
    } while(choice != 9);                     // keep looping until user chooses to exit
    return 0;                                 // program ends successfully
}