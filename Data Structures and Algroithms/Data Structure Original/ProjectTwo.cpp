#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


//Course Class Declartion.
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
    string getCourseId() const  {
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

//Hash table declartion 
class HashTable {

private:

    //variables for Hash table
    static const int TABLE_SIZE = 101;
    vector<Course> table[TABLE_SIZE];
    int hashFunction(const string& key) const {
        return key.length() % TABLE_SIZE;
    }

public:
    //Insert into course into table
    void insert(const Course& course) {
        int index = hashFunction(course.getCourseId());
        table[index].push_back(course);
    }



    //Display info for testing
    void displayInfo() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (!table[i].empty()) {

               
                for (const auto& course : table[i]) {
                    cout << "CourseId: " << course.getCourseId() << endl;
                    cout << "Course Name: " << course.getCourseName() << endl;
                    cout << "Prerequiste 1: " << course.getCoursePrequiste1() << endl;
                    cout <<"Prerequiste 2: " << course.getCoursePrequiste2() << endl;
                    cout << endl;
                }
               
            }
        }
    }

    //Function printing in alphabetical order
    void printCoursesAlphabetical() const {

        vector<Course> allCourses;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            allCourses.insert(allCourses.end(), table[i].begin(), table[i].end());
        }


        std::sort(allCourses.begin(), allCourses.end(),
            [](const Course& a, const Course& b) {
                return a.getCourseId() < b.getCourseId();
            });


        for (const auto& course : allCourses) {
            cout << "CourseId: " << course.getCourseId() << endl;
            cout << "Course Name: " << course.getCourseName() << endl; 
            cout << endl;
        }
    }

    //Node for serching 
    Course* findCourse(const string& courseId) {
        int index = hashFunction(courseId);
        for (auto& course : table[index]) {
            if (course.getCourseId() == courseId) {
                return &course;
            }
        }
        return nullptr;
    }

    
//Insert Courses with CSV
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

};
    

int main()
{

    //Main functions variables
    HashTable hashTable;
    int userSelection = 0;
    string searchId;
     Course* foundCourse = hashTable.findCourse(searchId);
   
   
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
            hashTable.loadCSV("C:/Users/dklei/Downloads/CS 300 ABCU_Advising_Program_Input.csv");
            break;

        case 2:
            hashTable.printCoursesAlphabetical();
            break;

        case 3: 
            cout << "Enter CourseId: ";
            cin >> searchId;
            {
            Course* foundCourse = hashTable.findCourse(searchId);
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
            cout << "Please make a vaild selection.";
                break;
        }

    }


    return 0;
    
}

