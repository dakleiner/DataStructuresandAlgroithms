#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Course Class Declaration
class Course {

    //private variable for course
private:
    string courseId;
    string courseName;
    string coursePrerequiste1;
    string coursePrerequiste2;

public:

    //Course constructor
    Course(string courseId, string courseName, string coursePrerequiste1, string coursePrerequiste2)
        : courseId(courseId), courseName(courseName), coursePrerequiste1(coursePrerequiste1), coursePrerequiste2(coursePrerequiste2) {
    }

    //Getter functions
    string getCourseId() const {
        return courseId;
    }
    string getCourseName() const {
        return courseName;
    }
    string getCoursePrequiste1() const {
        return coursePrerequiste1;
    }
    string getCoursePrequiste2() const {
        return coursePrerequiste2;
    }

    //Print course info
    void printInfo() const {
        cout << "CourseId: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Prerequisite 1: " << coursePrerequiste1 << endl;
        cout << "Prerequisite 2: " << coursePrerequiste2 << endl;
    }

};

//Vector-based Course Manager Class
class CourseVector {
private:
    vector<Course> courses;

public:
    //Constructor
    CourseVector() {}

    //Insert course into vector
    void insert(const Course& course) {
        courses.push_back(course);
    }

    //Display all courses info (for testing)
    void displayInfo() const {
        for (const auto& course : courses) {
            cout << "CourseId: " << course.getCourseId() << endl;
            cout << "Course Name: " << course.getCourseName() << endl;
            cout << "Prerequisite 1: " << course.getCoursePrequiste1() << endl;
            cout << "Prerequisite 2: " << course.getCoursePrequiste2() << endl;
            cout << endl;
        }
    }

    //Print courses in alphabetical order
    void printCoursesAlphabetical() const {
        //Create a copy of the vector for sorting
        vector<Course> sortedCourses = courses;

        //Sort by course ID
        sort(sortedCourses.begin(), sortedCourses.end(),
            [](const Course& a, const Course& b) {
                return a.getCourseId() < b.getCourseId();
            });

        //Print sorted courses
        for (const auto& course : sortedCourses) {
            cout << "CourseId: " << course.getCourseId() << endl;
            cout << "Course Name: " << course.getCourseName() << endl;
            cout << endl;
        }
    }

    //Search for a course by ID
    Course* findCourse(const string& courseId) {
        for (auto& course : courses) {
            if (course.getCourseId() == courseId) {
                return &course;
            }
        }
        return nullptr;
    }

    //Load courses from CSV file
    void loadCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string courseId, courseName, coursePrerequiste1, coursePrerequiste2;
            getline(ss, courseId, ',');
            getline(ss, courseName, ',');
            getline(ss, coursePrerequiste1, ',');
            getline(ss, coursePrerequiste2, ',');
            Course course(courseId, courseName, coursePrerequiste1, coursePrerequiste2);
            insert(course);
        }
        file.close();
    }

    //Get the number of courses
    int size() const {
        return courses.size();
    }
};


int main()
{
    //Main function variables
    CourseVector courseVector;
    int userSelection = 0;
    string searchId;

    cout << "Welcome to the course planner." << endl;

    //Menu Loop                
    while (userSelection != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do?: ";
        cin >> userSelection;

        switch (userSelection) {
        case 1:
            courseVector.loadCSV("C:/Users/dklei/Downloads/CS 300 ABCU_Advising_Program_Input.csv");
            cout << "Data loaded successfully." << endl;
            break;
        case 2:
            courseVector.printCoursesAlphabetical();
            break;
        case 3:
            cout << "Enter CourseId: ";
            cin >> searchId;
            {
                Course* foundCourse = courseVector.findCourse(searchId);
                if (foundCourse) {
                    foundCourse->printInfo();
                }
                else {
                    cout << "Course not found." << endl;
                }
            }
            break;
        case 9:
            cout << "Goodbye" << endl;
            break;

        default:
            cout << "Please make a valid selection." << endl;
            break;
        }
    }

    return 0;
}
