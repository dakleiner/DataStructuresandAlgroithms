#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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

    //Default constructor
    Course() : courseId(""), courseName(""), coursePrerequiste1(""), coursePrerequiste2("") {}

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

    //Check if course is empty
    bool isEmpty() const {
        return courseId.empty();
    }

    //Print course info
    void printInfo() const {
        cout << "CourseId: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Prerequisite 1: " << coursePrerequiste1 << endl;
        cout << "Prerequisite 2: " << coursePrerequiste2 << endl;
    }

};

//Array-based Course Manager Class
class CourseArray {
private:
    static const int MAX_COURSES = 100;  // Maximum number of courses
    Course courses[MAX_COURSES];
    int courseCount;  // Track how many courses are actually stored

public:
    //Constructor
    CourseArray() : courseCount(0) {}

    //Insert course into array
    bool insert(const Course& course) {
        if (courseCount >= MAX_COURSES) {
            cerr << "Error: Array is full. Cannot add more courses." << endl;
            return false;
        }
        courses[courseCount] = course;
        courseCount++;
        return true;
    }

    //Display all courses info (for testing)
    void displayInfo() const {
        for (int i = 0; i < courseCount; i++) {
            cout << "CourseId: " << courses[i].getCourseId() << endl;
            cout << "Course Name: " << courses[i].getCourseName() << endl;
            cout << "Prerequisite 1: " << courses[i].getCoursePrequiste1() << endl;
            cout << "Prerequisite 2: " << courses[i].getCoursePrequiste2() << endl;
            cout << endl;
        }
    }

    //Print courses in alphabetical order
    void printCoursesAlphabetical() const {
        //Create a temporary array for sorting
        Course sortedCourses[MAX_COURSES];

        //Copy courses to temporary array
        for (int i = 0; i < courseCount; i++) {
            sortedCourses[i] = courses[i];
        }

        //Sort by course ID using bubble sort or use std::sort
        sort(sortedCourses, sortedCourses + courseCount,
            [](const Course& a, const Course& b) {
                return a.getCourseId() < b.getCourseId();
            });

        //Print sorted courses
        for (int i = 0; i < courseCount; i++) {
            cout << "CourseId: " << sortedCourses[i].getCourseId() << endl;
            cout << "Course Name: " << sortedCourses[i].getCourseName() << endl;
            cout << endl;
        }
    }

    //Search for a course by ID
    Course* findCourse(const string& courseId) {
        for (int i = 0; i < courseCount; i++) {
            if (courses[i].getCourseId() == courseId) {
                return &courses[i];
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
            if (courseCount >= MAX_COURSES) {
                cerr << "Warning: Maximum course limit reached. Some courses not loaded." << endl;
                break;
            }

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
        return courseCount;
    }

    //Check if array is full
    bool isFull() const {
        return courseCount >= MAX_COURSES;
    }
};


int main()
{
    //Main function variables
    CourseArray courseArray;
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
            courseArray.loadCSV("CourseListing.csv");
            cout << "Data loaded successfully. Total courses: " << courseArray.size() << endl;
            break;
        case 2:
            courseArray.printCoursesAlphabetical();
            break;
        case 3:
            cout << "Enter CourseId: ";
            cin >> searchId;
            {
                Course* foundCourse = courseArray.findCourse(searchId);
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