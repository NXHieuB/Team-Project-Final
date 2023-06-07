#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

class Student {
    int rollNo;
    char name[50];
    int numSubjects; // New variable to store the number of subjects
    int* marks;      // Dynamic array to store marks for each subject
    double average;
    char grade;
    int* credits;
    double GPA;
    std::string convertGPA;

public:
    void getData();
    void showData() const;
    void calculate(int credits[4]);
    int getRollNo() const;
    void updateData();
    void calculateGrade();
    void displayDetails() const;
    double getAverage() const;
    char getGrade() const; // Function to retrieve the grade
};

//Function to get grade
char Student::getGrade() const {
    return grade;
}

//Function to create Dat file

//Function to get Average
double Student::getAverage() const {
    return average;
}

//Function for case 1

void Student::getData() {
    std::cout << "\nEnter student details:" << std::endl;
    std::cout << "Roll number: ";
    std::cin >> rollNo;
    std::cin.ignore();

    std::cout << "Name: ";
    std::cin.getline(name, 50);

    numSubjects = 4; // Update the number of subjects to 4

    marks = new int[numSubjects];

    std::cout << "Enter marks for Linear Algebra: ";
    std::cin >> marks[0];


    std::cout << "Enter marks for Computer System Programing: ";
    std::cin >> marks[1];


    std::cout << "Enter marks for Physics: ";
    std::cin >> marks[2];


    std::cout << "Enter marks for Chemistry: ";
    std::cin >> marks[3];
}

//Function to calculate GPA

void Student::calculate(int credits[4])
{
    double totalMarks = 0;
    int totalCredits = 0;
    for (int i = 0; i < numSubjects; i++)
    {
        if (marks[i] >= 89.5){
            totalMarks += 4.0 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 84.5){
            totalMarks += 3.7 * credits[i];
            totalCredits += credits[i];
        }
            
        else if (marks[i] >= 79.5){
            totalMarks += 3.3 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 74.5){
            totalMarks += 3.0 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 69.5){
            totalMarks += 2.7 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 64.5){
            totalMarks += 2.3 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 59.5){
            totalMarks += 2.0 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 54.5){
            totalMarks += 1.7 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 49.5){
            totalMarks += 1.3 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 44.5){
            totalMarks += 1.0 * credits[i];
            totalCredits += credits[i];
        }
        else if (marks[i] >= 40){
            totalMarks += 0.7 * credits[i];
            totalCredits += credits[i];
        }
        else{
            totalMarks += 0.0 * credits[i];
            totalCredits += credits[i];
        }
            
    }
    std::cout << totalMarks << std::endl;
    std::cout << totalCredits << std::endl;
    GPA = static_cast<double>(totalMarks) / totalCredits;
}

void Student::displayDetails() const
{
    std::cout << std::setw(10) << rollNo;
    std::cout << std::setw(20) << name;
    for (int i = 0; i < numSubjects; i++)
    {
        std::string convertGPA;
        if (marks[i] >=89.5)
            convertGPA = "A";
        else if (marks[i] >= 84.5)
            convertGPA = "A-";
        else if (marks[i] >= 79.5)
            convertGPA = "B+";
        else if (marks[i] >= 74.5)
            convertGPA = "B";
        else if (marks[i] >= 69.5)
            convertGPA = "B-";
        else if (marks[i] >= 64.5)
            convertGPA = "C+";
        else if (marks[i] >= 59.5)
            convertGPA = "C";
        else if (marks[i] >= 54.5)
            convertGPA = "C-";
        else if (marks[i] >= 49.5)
            convertGPA = "D+";
        else if (marks[i] >= 44.5)
            convertGPA = "D";
        else if (marks[i] >= 40)
            convertGPA = "D-";
        else 
            convertGPA = "F";


        std::cout << std::setw(10) << convertGPA;
    }
    std::cout << std::setw(10) << GPA << std::endl;
}

int main() {
    std::vector<Student> students;
    std::cout << "Welcome to SPRING 2023 course of Vinuni" << std::endl;
    std::cout << "This semester including 4 course:" << std::endl;
    std::cout << "1. Linear Algebra:" << std::endl;
    std::cout << "2. Computer System Program" << std::endl;
    std::cout << "3. Physics" << std::endl;
    std::cout << "4. Chemistry" << std::endl;
    std::cout << " \n Please provide the credits number for each course" << std::endl;
    
    int* credits;
    credits = new int[4];

    std::cout << "Enter credits for Linear Algebra: ";
    std::cin >> credits[0];

    std::cout << "Enter credits for Computer System Programing: ";
    std::cin >> credits[1];

    std::cout << "Enter credits for Physics: ";
    std::cin >> credits[2];

    std::cout << "Enter credits for Chemistry: ";
    std::cin >> credits[3];

    int choice;
    while (true) {
        std::cout << "\n***** MENU *****" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Display All Students" << std::endl;
        std::cout << "3. Display Highest Average Score" << std::endl;
        std::cout << "4. Display Lowest Average Score" << std::endl;
        std::cout << "5. Update Student Details" << std::endl;
        std::cout << "6. Plot the data of all students" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice (1-7): ";
        std::cin >> choice;

        switch (choice) {
            case 1:{
                Student newStudent;
                newStudent.getData();
                newStudent.calculate(credits);
                students.push_back(newStudent);
                break;
            }
            
            case 2:{
                if (students.empty()){
                    std::cout << "No student records available." << std::endl;
                }
                else {
                    std::cout << std::setw(10) << "Roll No";
                    std::cout << std::setw(20) << "Name";
                    std::cout << std::setw(10) << "Math";
                    std::cout << std::setw(10) << "Science";
                    std::cout << std::setw(10) << "Physics";
                    std::cout << std::setw(10) << "Chemistry";
                    std::cout << std::setw(10) << "GPA" << std::endl; 
                for (const auto& student : students) {
                        student.displayDetails();
                    }
                break;
            }
        }
    }
}
}
   
