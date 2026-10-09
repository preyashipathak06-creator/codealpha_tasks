
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Course {
public:
    string name;
    double grade;
    int credits;

    void input() {
        cout << "Enter course name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter grade point (0-10): ";
        cin >> grade;

        cout << "Enter credit hours: ";
        cin >> credits;
    }

    double getGradePoints() {
        return grade * credits;
    }

    void display() {
        cout << left << setw(25) << name
             << setw(15) << grade
             << setw(15) << credits
             << getGradePoints() << endl;
    }
};

int main() {
    int n;
    double totalCredits = 0;
    double totalGradePoints = 0;

    cout << "====================================\n";
    cout << "       CGPA CALCULATOR\n";
    cout << "====================================\n";

    cout << "Enter number of courses: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of courses.\n";
        return 1;
    }

    Course courses[100];

    if (n > 100) {
        cout << "Maximum 100 courses allowed.\n";
        return 1;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details of Course " << i + 1 << ":\n";
        courses[i].input();

        if (courses[i].grade < 0 || courses[i].grade > 10 ||
            courses[i].credits <= 0) {
            cout << "Invalid grade or credit hours.\n";
            return 1;
        }

        totalCredits += courses[i].credits;
        totalGradePoints += courses[i].getGradePoints();
    }

    double cgpa = totalGradePoints / totalCredits;

    cout << "\n========== COURSE REPORT ==========\n";
    cout << left << setw(25) << "Course"
         << setw(15) << "Grade"
         << setw(15) << "Credits"
         << "Grade Points\n";

    for (int i = 0; i < n; i++) {
        courses[i].display();
    }

    cout << fixed << setprecision(2);
    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << "\nFinal CGPA: " << cgpa << endl;

    cout << "\nThank you for using CGPA Calculator!\n";

    return 0;
}