# Attendance-Management-System-For-Teachers-
The University Attendance Tracking System is an object-oriented C++ application that helps manage teacher attendance data efficiently. It uses OOP concepts (inheritance, encapsulation, polymorphism, constructors/destructors) and file handling to simulate a real-world system for tracking teachers’ attendance, managing records, and generating reports

This program allows:

Adding, viewing, updating, and deleting teacher records.

Storing data in a file (teachers.txt) using CSV format.

Generating daily and monthly attendance reports.

Displaying department information.

Admin access to view all teacher records.

🧩 Key Features

✅ Add New Teacher — Enter teacher’s details, attendance times, and automatically calculate lateness, short hours, and overtime.
✅ View Teacher — Retrieve and display details for any teacher by their ID.
✅ Update Teacher — Modify an existing teacher’s details using their ID.
✅ Delete Teacher — Remove a teacher’s record permanently from the file.
✅ Admin Reports — Admins can view all stored teacher records at once.
✅ Daily & Monthly Reports — Generate summaries and performance statistics for all teachers.
✅ Department Information — View basic department details (e.g., name, number of teachers).
✅ File Persistence — All data is saved in teachers.txt for future retrieval.

⚙️ Technologies Used

Language: C++

Concepts: OOP (Classes, Inheritance, Encapsulation, Constructors, Destructors, Copy Constructors)

File Handling: fstream, ifstream, ofstream

Data Management: CSV (Comma-Separated Values)

🗂️ File Handling

All teacher data is stored in a text file named teachers.txt in CSV (comma-separated) format.
Each line represents one teacher record with the following structure:

Name,ID,Subject,Department,InTime,OutTime,LateMinutes,EarlyMinutes,ShortHours,ExcessHours


Example:

John Doe,101,Mathematics,Science,09:10,16:50,30,30,1,0


The system supports:

Appending new records.

Reading existing records.

Updating a specific record by ID.

Deleting a record safely.

🚀 How to Run

Clone or Copy the project files into your local machine.

Compile the code using any C++ compiler (e.g., g++, Dev C++, Code::Blocks, VS Code).

g++ main.cpp -o attendance


Run the program:

./attendance


You’ll see the Main Menu with options like:

1. Add Teacher
2. View Teacher
3. Update Teacher
4. Delete Teacher
5. View All Teachers (Admin)
6. Generate Daily Report
7. Generate Monthly Summary
8. Department Info
9. Exit


Follow the on-screen instructions to perform actions.
