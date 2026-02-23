#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

static string toUpper(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
              [](unsigned char c) { return toupper(c); });
    return upperStr;
}

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

//Tree Node structure
struct TreeNode {
    Course course;
    TreeNode* left;
    TreeNode* right;

    //TreeNode constructor
    TreeNode(const Course& c) : course(c), left(nullptr), right(nullptr) {}
};

//Binary Search Tree Class
class BinarySearchTree {
private:
    TreeNode* root;

    //Helper function to insert recursively
    TreeNode* insertHelper(TreeNode* node, const Course& course) {
        if (node == nullptr) {
            return new TreeNode(course);
        }

        if (course.getCourseId() < node->course.getCourseId()) {
            node->left = insertHelper(node->left, course);
        }
        else if (course.getCourseId() > node->course.getCourseId()) {
            node->right = insertHelper(node->right, course);
        }
        // If equal, don't insert (no duplicates)

        return node;
    }

    //Helper function to search recursively
    TreeNode* searchHelper(TreeNode* node, const string& courseId) {
        if (node == nullptr || node->course.getCourseId() == courseId) {
            return node;
        }

        if (courseId < node->course.getCourseId()) {
            return searchHelper(node->left, courseId);
        }
        else {
            return searchHelper(node->right, courseId);
        }
    }

    //Helper function for in-order traversal (prints in alphabetical order)
    void inOrderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << "CourseId: " << node->course.getCourseId() << endl;
            cout << "Course Name: " << node->course.getCourseName() << endl;
            cout << endl;
            inOrderTraversal(node->right);
        }
    }

    //Helper function to display all course info
    void displayAllHelper(TreeNode* node) const {
        if (node != nullptr) {
            displayAllHelper(node->left);
            cout << "CourseId: " << node->course.getCourseId() << endl;
            cout << "Course Name: " << node->course.getCourseName() << endl;
            cout << "Prerequisite 1: " << node->course.getCoursePrequiste1() << endl;
            cout << "Prerequisite 2: " << node->course.getCoursePrequiste2() << endl;
            cout << endl;
            displayAllHelper(node->right);
        }
    }

    //Helper function to delete tree recursively
    void deleteTree(TreeNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    //Constructor
    BinarySearchTree() : root(nullptr) {}

    //Destructor to free memory
    ~BinarySearchTree() {
        deleteTree(root);
    }

    //Insert course into tree
    void insert(const Course& course) {
        root = insertHelper(root, course);
    }

    //Display all courses info (for testing)
    void displayInfo() const {
        displayAllHelper(root);
    }

    //Print courses in alphabetical order (in-order traversal)
    void printCoursesAlphabetical() const {
        if (root == nullptr) {
            cout << "No courses loaded." << endl;
            return;
        }
        inOrderTraversal(root);
    }

    //Search for a course by ID
    Course* findCourse(const string& courseId) {
        TreeNode* node = searchHelper(root, courseId);
        if (node != nullptr) {
            return &(node->course);
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
};


int main()
{
    //Main function variables
    BinarySearchTree courseTree;
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
            courseTree.loadCSV("CourseListings.csv");
            cout << "Data loaded successfully." << endl;
            break;
        case 2:
            courseTree.printCoursesAlphabetical();
            break;
        case 3:
            cout << "Enter CourseId: ";
            cin >> searchId;
			searchId = toUpper(searchId);
            {
                Course* foundCourse = courseTree.findCourse(searchId);
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
