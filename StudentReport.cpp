#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

// The class that stores data
class Student {
    int rollNo;
    char name[50];
    int numSubjects; // New variable to store the number of subjects
    int* marks;      // Dynamic array to store marks for each subject
    double average;
    char grade;

public:
    void getData();
    void showData() const;
    void calculate();
    int getRollNo() const;
    void updateData();
    void calculateGrade();
    void displayDetails() const;
    double getAverage() const;
    char getGrade() const; // Function to retrieve the grade
};

char Student::getGrade() const {
    return grade;
}


double Student::getAverage() const {
    return average;
}

void displayHighestAverage(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records available." << std::endl;
        return;
    }

    double highestAverage = students[0].getAverage();
    for (const auto& student : students) {
        if (student.getAverage() > highestAverage) {
            highestAverage = student.getAverage();
        }
    }

    std::cout << "Highest Average Score: " << highestAverage << std::endl;
}

void displayLowestAverage(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records available." << std::endl;
        return;
    }

    double lowestAverage = students[0].getAverage();
    for (const auto& student : students) {
        if (student.getAverage() < lowestAverage) {
            lowestAverage = student.getAverage();
        }
    }

    std::cout << "Lowest Average Score: " << lowestAverage << std::endl;
}

void Student::calculate() {
    int totalMarks = 0;
    for (int i = 0; i < numSubjects; i++) {
        totalMarks += marks[i];
    }
    average = static_cast<double>(totalMarks) / numSubjects;
    calculateGrade();
}

void Student::getData() {
    std::cout << "\nEnter student details:" << std::endl;
    std::cout << "Roll number: ";
    std::cin >> rollNo;
    std::cin.ignore();

    std::cout << "Name: ";
    std::cin.getline(name, 50);

    numSubjects = 4; // Update the number of subjects to 4

    marks = new int[numSubjects];

    std::cout << "Enter marks for Math: ";
    std::cin >> marks[0];

    std::cout << "Enter marks for Science: ";
    std::cin >> marks[1];

    std::cout << "Enter marks for Physics: ";
    std::cin >> marks[2];

    std::cout << "Enter marks for Chemistry: ";
    std::cin >> marks[3];

    calculate();
}

void Student::showData() const {
    std::cout << "\nRoll number: " << rollNo << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Number of subjects: " << numSubjects << std::endl;
    std::cout << "Marks for each subject:";
    for (int i = 0; i < numSubjects; i++) {
        std::cout << " " << marks[i];
    }
    std::cout << std::endl;
    std::cout << "Average marks: " << average << std::endl;
    std::cout << "Grade: " << grade << std::endl;
}

int Student::getRollNo() const {
    return rollNo;
}

void Student::updateData() {
    std::cout << "\nEnter updated student details:" << std::endl;
    std::cout << "Name: ";
    std::cin.ignore();
    std::cin.getline(name, 50);

    numSubjects = 4; // Update the number of subjects to 4

    delete[] marks; // Free the memory of the previous marks array
    marks = new int[numSubjects];

    std::cout << "Enter marks for Math: ";
    std::cin >> marks[0];

    std::cout << "Enter marks for Science: ";
    std::cin >> marks[1];

    std::cout << "Enter marks for Physics: ";
    std::cin >> marks[2];

    std::cout << "Enter marks for Chemistry: ";
    std::cin >> marks[3];

    calculate();
}

void Student::calculateGrade() {
    if (average >= 90)
        grade = 'A';
    else if (average >= 80)
        grade = 'B';
    else if (average >= 70)
        grade = 'C';
    else if (average >= 60)
        grade = 'D';
    else
        grade = 'F';
}

void Student::displayDetails() const {
    std::cout << std::setw(10) << rollNo;
    std::cout << std::setw(20) << name;
    for (int i = 0; i < numSubjects; i++) {
        std::cout << std::setw(10) << marks[i];
    }
    std::cout << std::setw(10) << average;
    std::cout << std::setw(10) << grade << std::endl;
}

// Function to create a new student record
void createStudent() {
    Student stud;
    std::ofstream outFile("student.dat", std::ios::binary | std::ios::app);
    stud.getData();
    outFile.write(reinterpret_cast<const char*>(&stud), sizeof(Student));
    outFile.close();
    std::cout << "\n\nStudent record has been created";
    std::cin.ignore();
    std::cin.get();
}

// Function to display a specific student record
void displayStudent(int n) {
    Student stud;
    std::ifstream inFile("student.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be opened... Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNo() == n) {
            stud.showData();
            found = true;
        }
    }
    inFile.close();
    if (!found)
        std::cout << "\n\nRecord does not exist";
    std::cin.ignore();
    std::cin.get();
}

// Function to display all student records
void displayAllStudents() {
    Student stud;
    std::ifstream inFile("student.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be opened! Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        stud.showData();
        std::cout << "\n\n====================================\n";
    }
    inFile.close();
    std::cin.ignore();
    std::cin.get();
}

// Function to update a specific student record
void updateStudent(int n) {
    bool found = false;
    Student stud;
    std::fstream file("student.dat", std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cout << "File could not be opened. Press any key to exit...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    while (!file.eof() && !found) {
        file.read(reinterpret_cast<char*>(&stud), sizeof(Student));
        if (stud.getRollNo() == n) {
            stud.showData();
            std::cout << "\nEnter new student details:" << std::endl;
            stud.updateData();
            int pos = (-1) * static_cast<int>(sizeof(stud));
            file.seekp(pos, std::ios::cur);
            file.write(reinterpret_cast<const char*>(&stud), sizeof(Student));
            std::cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    file.close();
    if (!found)
        std::cout << "\n\nRecord Not Found";
    std::cin.ignore();
    std::cin.get();
}

// Function to delete a specific student record
void deleteStudent(int n) {
    Student stud;
    std::ifstream inFile("student.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be opened... Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::ofstream outFile("Temp.dat", std::ios::binary);
    inFile.seekg(0, std::ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNo() != n) {
            outFile.write(reinterpret_cast<const char*>(&stud), sizeof(Student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    std::cout << "\n\n\tRecord Deleted...";
    std::cin.ignore();
    std::cin.get();
}

// Function to generate a student report
void generateReport() {
    Student stud;
    std::ifstream inFile("student.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be opened... Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::cout << "\n\n\t\t\tSTUDENT REPORT\n\n";
    std::cout << "=============================================================\n";
    std::cout << std::setw(10) << "Roll No.";
    std::cout << std::setw(20) << "Name";
    std::cout << std::setw(10) << "Math";
    std::cout << std::setw(10) << "Science";
    std::cout << std::setw(10) << "Physics";
    std::cout << std::setw(10) << "Chemistry";
    std::cout << std::setw(10) << "Average";
    std::cout << std::setw(10) << "Grade";
    std::cout << "\n=============================================================\n";

    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        stud.displayDetails();
    }
    inFile.close();
    std::cin.ignore();
    std::cin.get();
}


#include <iostream>
#include <fstream>
#include <vector>

void plotGradeData(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No student records available." << std::endl;
        return;
    }

    // Prepare the data for plotting
    std::vector<double> averages;
    std::vector<char> grades;
    for (const auto& student : students) {
        averages.push_back(student.getAverage());
        grades.push_back(student.getGrade());
    }

    // Plotting code using Python
    std::ofstream plotFile("plot.py");
    plotFile << "import matplotlib.pyplot as plt\n";
    plotFile << "averages = [";
    for (const auto& average : averages) {
        plotFile << average << ", ";
    }
    plotFile << "]\n";

    plotFile << "grades = [";
    for (const auto& grade : grades) {
        plotFile << "'" << grade << "', ";
    }
    plotFile << "]\n";

    plotFile << "plt.bar(grades, averages)\n";
    plotFile << "plt.xlabel('Grade')\n";
    plotFile << "plt.ylabel('Average')\n";
    plotFile << "plt.title('Grade Distribution')\n";
    plotFile << "plt.show()\n";
    plotFile.close();

    // Execute the Python script
    system("python plot.py");

    std::cout << "Grade distribution plotted successfully." << std::endl;
}


int main() {
    std::vector<Student> students; // Store student objects in a vector

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
            case 1: {
                Student newStudent;
                newStudent.getData();
                students.push_back(newStudent);
                break;
            }
            case 2: {
                if (students.empty()) {
                    std::cout << "No student records available." << std::endl;
                } else {
                    std::cout << std::setw(10) << "Roll No";
                    std::cout << std::setw(20) << "Name";
                    std::cout << std::setw(10) << "Math";
                    std::cout << std::setw(10) << "Science";
                    std::cout << std::setw(10) << "Physics";
                    std::cout << std::setw(10) << "Chemistry";
                    std::cout << std::setw(10) << "Average";
                    std::cout << std::setw(10) << "Grade" << std::endl;
                    for (const auto& student : students) {
                        student.displayDetails();
                    }
                }
                break;
            }
            case 3:
                displayHighestAverage(students);
                break;
             case 4:
                displayLowestAverage(students);
                break;
            case 5: {
                int rollNo;
                std::cout << "Enter the roll number of the student to update: ";
                std::cin >> rollNo;
                bool found = false;
                for (auto& student : students) {
                    if (student.getRollNo() == rollNo) {
                        student.updateData();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Student with roll number " << rollNo << " not found." << std::endl;
                }
                break;
            }
            case 6:
                plotGradeData(students);
                break;
            case 7: {
                std::cout << "Exiting the program..." << std::endl;
                return 0;
            }
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
        }
    }
}
