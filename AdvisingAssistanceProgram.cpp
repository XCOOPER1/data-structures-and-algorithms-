#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

//Reginald Cooper CS300
// Define a Course structure to hold course information
struct Course {
    std::string courseNumber;
    std::string name;
    std::vector<std::string> prerequisites;
};

// Function to load courses from file into a map
std::map<std::string, Course> loadCourses(const std::string& filename) {
    std::map<std::string, Course> courses;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string courseNumber, name, prereq;
        std::getline(ss, courseNumber, ',');
        std::getline(ss, name, ',');
        Course course;
        course.courseNumber = courseNumber;
        course.name = name;

        while (std::getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[courseNumber] = course;
    }

    file.close();
    return courses;
}

// Function to print the course list
void printCourseList(const std::map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    std::sort(courseNumbers.begin(), courseNumbers.end());

    for (const auto& courseNumber : courseNumbers) {
        std::cout << courseNumber << ", " << courses.at(courseNumber).name << std::endl;
    }
}

// Function to print course information
void printCourseInfo(const std::map<std::string, Course>& courses, const std::string& courseNumber) {
    if (courses.find(courseNumber) != courses.end()) {
        const Course& course = courses.at(courseNumber);
        std::cout << course.courseNumber << ", " << course.name << std::endl;
        std::cout << "Prerequisites: ";
        for (const auto& prereq : course.prerequisites) {
            std::cout << prereq << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Course not found!" << std::endl;
    }
}

// Main function to run the program
int main() {
    std::map<std::string, Course> courses;
    int choice;
    std::string filename;

    while (true) {
        std::cout << "Welcome to the course planner." << std::endl;
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit." << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter the file name: ";
            std::cin >> filename;
            courses = loadCourses(filename);
        }
        else if (choice == 2) {
            printCourseList(courses);
        }
        else if (choice == 3) {
            std::string courseNumber;
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            printCourseInfo(courses, courseNumber);
        }
        else if (choice == 9) {
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        }
        else {
            std::cout << choice << " is not a valid option." << std::endl;
        }
    }

    return 0;
}
