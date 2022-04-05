#include "vcpkg/installed/x86-windows/include/rapidjson/document.h"
#include "vcpkg/installed/x86-windows/include/rapidjson/istreamwrapper.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include "student.h"
#include "vector"
using namespace rapidjson;


void printYoungest(std::vector<Student> allStudents) {
    std::string youngestStudentName;
    std::vector<int> allStudentsAge;

    for(const auto &student : allStudents) {
        allStudentsAge.push_back(student.age);
    }
    std::sort(allStudentsAge.begin(), allStudentsAge.end());

    for(const auto &student : allStudents) {
        if(student.age == allStudentsAge[0]) {
            std::cout << "Youngest: " << student.name << std::endl;
        }
    }
}

void printOldest(std::vector<Student> allStudents) {
    std::string youngestStudentName;
    std::vector<int> allStudentsAge;

    for(const auto &student : allStudents) {
        allStudentsAge.push_back(student.age);
    }
    std::sort(allStudentsAge.begin(), allStudentsAge.end());

    for(const auto &student : allStudents) {
        if(student.age == allStudentsAge[allStudentsAge.size() - 1]) {
            std::cout << "Oldest: " << student.name << std::endl;
        }
    }
}

void printBadStudent(std::vector<Student> allStudents) {
    std::string youngestStudentName;

    for(const auto &student : allStudents) {
        if(student.attendance < 30) {
            std::cout << "Bad student: " << student.name << std::endl;
        }
    }
}

void printAverageAge(std::vector<Student> allStudents) {
    std::string youngestStudentName;
    std::vector<int> allStudentsAge;

    int sumOfAges = 0;
    for(const auto &student : allStudents) {
        sumOfAges += student.age;
    }
    int average = (sumOfAges / allStudents.size());
    std::cout << "Average age: " << average << std::endl;


}
int main() {
    std::ifstream ifs("students.json");

    if(!ifs.is_open()) {
        std::cout << "Error: Failed to open file" << std::endl;
        return 1;
    }

    // InputStream
    rapidjson::IStreamWrapper isw(ifs);

    // Representing the data
    rapidjson::Document document;

    //Read stream
    document.ParseStream(isw);

    // Students array
    std::vector<Student> allStudents;
    std::list<Student*> test;
    Student* teststudent = new Student();

    auto objectsArray = document.GetArray();

    for(const auto &object : objectsArray) {
        // Get object fields
        int id = object["id"].GetInt();
        std::string name = object["name"].GetString();
        int age = object["age"].GetInt();
        int attendance = object["attendance"].GetInt();
        // Check output
        std::cout << "ID: " << id << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "age: " << age << std::endl;
        std::cout << "attendance: " << attendance << std::endl;
        //Create student
        Student student;
        student.id = id;
        student.name = name;
        student.age = age;
        student.attendance = attendance;
        allStudents.push_back(student);
    }

    printYoungest(allStudents);
    printOldest(allStudents);
    printAverageAge(allStudents);
    printBadStudent(allStudents);
    return 0;
}