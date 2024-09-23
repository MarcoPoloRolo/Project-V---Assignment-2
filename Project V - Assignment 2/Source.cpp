#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//Define the STUDENT_DATA struct
struct STUDENT_DATA {
    string firstName;
    string lastName;
    string email;
};

int main() {
    //Create a vector to store student data
    vector<STUDENT_DATA> students;

    //Open the StudentData.txt file
    ifstream inputFile("StudentData.txt");

    //Check if the file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    //Read the file line by line
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string firstName, lastName;

        //Parse the line to extract first and last name
        if (getline(ss, firstName, ',') && getline(ss, lastName)) {
            STUDENT_DATA student;
            student.firstName = firstName;
            student.lastName = lastName;
            //Push the student object into the vector
            students.push_back(student);
        }
    }

    inputFile.close();

    #ifdef _DEBUG
    cout << "Debug Mode: Printing student data..." << endl;
    //Display the students' data to verify it's stored correctly
    for (const auto& student : students) {
        cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName << endl;
    }
    #endif

    // Check for Pre-Release mode
    #ifdef PRE_RELEASE
    cout << "Pre-Release Mode: Loading student emails..." << endl;

    // Open the StudentData_Emails.txt file
    ifstream emailFile("StudentData_Emails.txt");

    if (!emailFile.is_open()) {
        cerr << "Error opening email file" << endl;
        return 1;
    }

    //Read the email file and update the student vector with emails
    int index = 0;
    while (getline(emailFile, line)) {
        stringstream ss(line);
        string firstName, lastName, email;

        if (getline(ss, firstName, ',') && getline(ss, lastName, ',') && getline(ss, email)) {
            if (index < students.size() && students[index].firstName == firstName && students[index].lastName == lastName) {
                students[index].email = email; // Add the email to the student
            }
            index++;
        }
    }

    emailFile.close();

    //Display students with emails
    for (const auto& student : students) {
        cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName << ", Email: " << student.email << endl;
    }

    #else
    cout << "Standard Mode: No emails loaded." << endl;
    #endif

    return 0;
}
