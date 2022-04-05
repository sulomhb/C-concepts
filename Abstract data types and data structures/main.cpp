#include <iostream>
#include <string>
#include <vector>

// ---------------------- CLASSES ------------------------------------
class Student {
public:
    int id{};
    std::string name;
    std::string email;

    void printStudentInformation() const {
        std::cout << "student id = " << this->id << ", name = " << this->name << ", email = " << this->email
                  << std::endl;
    }
};

class Test {
public:
    int id{};
    std::string courseName;
    std::string testName;
    std::string dateTime;

    void printTestInformation() const {
        std::cout << "test id = " << this->id << ", course name = " << this->courseName << ", test name = "
                  << this->testName << ", date = " << this->dateTime << std::endl;
    }
};

class TestResult {
public:
    Student student;
    Test test;
    int grade{};

    void printTestResult() const {
        std::cout << "student id = " << this->student.id << ", course name = " << this->test.courseName
                  << ", test id = " << this->test.id << ", test name = " << this->test.testName << ", grade = "
                  << this->grade << std::endl;
    }
};

// ----------------------------------------- FUNCTIONS---------------------------------------------------

/*
 * @param { allStudents[] } : Array of all students registered.
 * @param { counter } : Counter - Total amount of students registered.
 */
void printAllStudents(std::vector<Student> allStudents) {
    for (auto &student : allStudents) {
        student.printStudentInformation();
    }
};

/*
 * @param { allTests[] } : Array of all tests registered.
 * @param { counter } : Counter - Total amount of tests registered.
 */

void printAllTests(std::vector<Test> allTests[]) {
    for (auto &test : *allTests) {
        test.printTestInformation();
    }
}

/*
 * @param { allTestResults[] } : Array of all test results registered.
 * @param { counter } : Counter - Total amount of test results registered.
 */
void printAllTestResults(std::vector<TestResult> allTestResults[]) {
    for (auto &testResult : *allTestResults) {
        testResult.printTestResult();
    }
}

/*
 * @param { student } : New student which is passed in every time a student is being added.
 * @param { allStudents[] } : Array of all students registered.
 * @param { autoIncrementID } : Counter - Total amount of students registered & ID's given chronologically.
 */

void addStudent(Student student, std::vector<Student> allStudents[], int autoIncrementID) {
    student.id = autoIncrementID;
    while (student.name.length() == 0) {
        std::getline(std::cin, student.name);
    }
    std::getline(std::cin, student.email);
    allStudents->push_back(student);
}

/*
 * @param { allStudents[] } : Array of all students registered.
 * @return { program() } : Main function to
 */
void editStudent(std::vector<Student> allStudents[]) {
    int studentOfChoice;
    std::cout << allStudents->size() + 1 << "." << "Back to menu" << std::endl;
    std::cin >> studentOfChoice;
    if (studentOfChoice == allStudents->size() + 1) {
        return;
    }
    std::string newStudentName;
    std::string newStudentEmail;
    while (newStudentName.length() == 0) {
        std::getline(std::cin, newStudentName);
    }
    while (newStudentEmail.length() == 0) {
        std::getline(std::cin, newStudentEmail);
    }
    //std::cin >> newStudentName;
    //std::cin >> newStudentEmail;

    allStudents->at(studentOfChoice - 1).name = newStudentName;
    allStudents->at(studentOfChoice - 1).email = newStudentEmail;
    //allStudents->at(studentOfChoice - 1).printStudentInformation();
}

/*
 * @param {allStudents} : Array with all registered students.
 */
void removeStudent(std::vector<Student> allStudents[]) {
    int studentOfChoice;
    std::cin >> studentOfChoice;
    allStudents->erase(allStudents->begin() + (studentOfChoice - 1));
}

/*
 * @param { test } : New Test for every time user chooses to add a test in the menu.
 * @param { allTests[] } : Array of all tests registered.
 * @param { autoIncrementID } : Counter - Total amount of tests registered & ID's given chronologically.
 */

void addTest(Test test, std::vector<Test> allTests[], int autoIncrementID) {
    test.id = autoIncrementID;
    std::cout << "Course Name \n";
    while (test.courseName.length() == 0) {
        std::getline(std::cin, test.courseName);
    }
    std::cout << "Test Name \n";
    while (test.testName.length() == 0) {
        std::getline(std::cin, test.testName);
    }
    while (test.dateTime.length() == 0) {
        std::cout << "Test Date \n";
        std::getline(std::cin, test.dateTime);
    }
    allTests->push_back(test);
}

/*
* @param { allTests[] } : Array of all tests registered.
*/
void editTest(std::vector<Test> allTests[]) {
    std::cout << "Running Edit Test now\n";
    int testOfChoice;
    std::cin >> testOfChoice;
    std::string newTestName;
    std::string newCourseName;
    std::string newDate;

    // Get new values
    while (newCourseName.length() == 0) {
        std::getline(std::cin, newCourseName);
    }
    if (newCourseName == "11") { exit(0); };

    while (newTestName.length() == 0) {
        std::getline(std::cin, newTestName);
    }
    //while (newDate.length() == 0) {
    std::getline(std::cin, newDate);
    //}
    //std::getline(std::cin, newDate);

    // Insert new values
    allTests->at(testOfChoice - 1).testName = newTestName;
    allTests->at(testOfChoice - 1).courseName = newCourseName;
    allTests->at(testOfChoice - 1).dateTime = newDate;
    //allTests->at(testOfChoice - 1).printTestInformation();
}

/*
 * @param {allStudents} : Array with all registered students.
 */
void removeTest(std::vector<Test> allTests[]) {
    int testOfChoice;
    std::cin >> testOfChoice;
    allTests->erase(allTests->begin() + (testOfChoice - 1));
}

/*
 * @param { testResult } : New Test Result for every time user chooses to add a test result in the menu.
 * @param { student, test } : student(Object) and test(Object) registered along with grade(Int).
 * @param { allTestResults[] } : Array of all test results registered.
 */
void addTestResult(TestResult testResult, std::vector<TestResult> allTestResults[], std::vector<Student> allStudents[],
                   std::vector<Test> allTests[]) {
    int studentOfChoice;
    int testOfChoice;
    int grade;
    int alreadyRegisteredTestResult;
    // Print all students and Tests
    printAllStudents(*allStudents);
    printAllTests(allTests);

    // Insert values
    std::cout << "Which student do you choose?";
    std::cin >> studentOfChoice;
    std::cout << "Which test do you choose?";
    std::cin >> testOfChoice;
    std::cout << "Which grade do you want to give?";
    std::cin >> grade;

    testResult.student = allStudents->at(studentOfChoice - 1);
    testResult.test = allTests->at(testOfChoice - 1);
    testResult.grade = grade;

    // Add test to array
    allTestResults->push_back(testResult);

}

void editTestResult(std::vector<TestResult> allTestResults[], std::vector<Student> allStudents[],
                    std::vector<Test> allTests[]) {
    std::cout << "Running Edit Test Result now\n";
    int newStudentID;
    int newTestID;
    int newGrade;
    std::cout << allStudents->size() << std::endl;
    // Get new values
    std::cin >> newStudentID;
    if (allStudents->size() < newStudentID) return;
    std::cin >> newTestID;
    if (allTests->size() < newTestID) return;
    std::cin >> newGrade;

    // Find and edit test result
    for (auto &testResult : *allTestResults) {
        if (testResult.student.id == newStudentID && testResult.test.id == newTestID) {
            testResult.grade = newGrade;
        }
    }
}

/*
 * @param {allStudents} : Array with all registered students.
 */
void removeTestResult(std::vector<TestResult> allTestResults[]) {
    int studentOfChoice;
    int testOfChoice;
    int index = 0;
    std::cin >> studentOfChoice;
    std::cin >> testOfChoice;
    for (auto &testResult : *allTestResults) {
        if (testResult.student.id == studentOfChoice && testResult.test.id == testOfChoice) {
            allTestResults->erase(allTestResults->begin() + index);
        }
        index++;
    }
    return;
}


/*
 * @return : Print overview of choices that user can take.
 */
void menu() {
    std::cout << "Please choose:\n"
                 "\n"
                 "1. Add student\n"
                 "2. Edit student\n"
                 "3. Remove student\n"
                 "\n"
                 "4. Add test\n"
                 "5. Edit test\n"
                 "6. Remove test\n"
                 "\n"
                 "7. Add test result\n"
                 "8. Edit test result\n"
                 "9. Remove test result\n"
                 "\n"
                 "10. Show all info\n"
                 "11. Exit\n";
}


/*
 * @param { student } : New student which is passed in every time a student is being added.
 * @param { allStudents[] } : Array of all students registered.
 * @param { autoIncrementID } : Counter - Total amount of students registered & ID's given chronologically.
 * @param { test } : New Test for every time user chooses to add a test in the menu.
 * @param { allTests[] } : Array of all tests registered.
 * @param { testResult } : New Test Result for every time user chooses to add a test result in the menu.
 * @param { allTestResults[] } : Array of all test results registered.
 * @param { userInput } : User input for choice on menu, integer value.
 */

void program(std::vector<Student> allStudents[], std::vector<Test> allTests[], std::vector<TestResult> allTestResults[],
             const Student &student, const Test &test, const TestResult &testResult, int userInput,
             int autoIncrementStudentID, int autoIncrementTestID) {
    while (userInput != 11) {
        menu();
        std::cin >> userInput;

        switch (userInput) {
            // Add student
            case 1:
                addStudent(student, allStudents, autoIncrementStudentID);
                autoIncrementStudentID++;
                break;

                //Edit Student
            case 2:
                //printAllStudents(*allStudents);
                editStudent(allStudents);
                break;

                //Remove student **************************************
            case 3:
                //printAllStudents(*allStudents);
                removeStudent(allStudents);
                break;

                // Add test
            case 4:
                addTest(test, allTests, autoIncrementTestID);
                autoIncrementTestID++;
                break;

                // Edit test
            case 5:
                //printAllTests(allTests);
                editTest(allTests);
                break;

                // Remove test
            case 6:
                //printAllTests(allTests);
                removeTest(allTests);
                break;

                // Add test result
            case 7:
                addTestResult(testResult, allTestResults, allStudents, allTests);
                break;

                // Edit test result
            case 8:
                //printAllTestResults(allTestResults);
                editTestResult(allTestResults, allStudents, allTests);
                break;

                // Remove test result
            case 9:
                removeTestResult(allTestResults);
                break;

            case 10:
                printAllStudents(*allStudents);
                printAllTests(allTests);
                printAllTestResults(allTestResults);
                break;

            case 11:
                break;
        }
    }
}

// ------------------------------------------ MAIN -------------------------------------------------------
int main() {
    // Create objects
    Student student;
    Test test;
    TestResult testResult;

    // Storage for each student, test and test result.
    std::vector<Student> allStudents;
    std::vector<Test> allTests;
    std::vector<TestResult> allTestResults;


    int userInput;
    int autoIncrementStudentID = 1; // Id-setter and student counter.
    int autoIncrementTestID = 1; // Id-setter and test counter.

    program(&allStudents, &allTests, &allTestResults, student, test, testResult, userInput, autoIncrementStudentID,
            autoIncrementTestID);
    return 0;
}