#include <iostream>
#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"

void readStudents() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
    SQLite::Statement query(db, "SELECT * FROM students");
    while(query.tryExecuteStep() == SQLITE_ROW) {
        int id = query.getColumn("id").getInt();
        std::string name = query.getColumn("name").getString();
        std::string email = query.getColumn("email").getString();
        int year = query.getColumn("year").getInt();

        std::cout << "id: " << id;
        std::cout << ", name: " << name;
        std::cout << ", email: " << email;
        std::cout << ", year: " << year << std::endl;
    };
        if(query.getErrorCode()) {
            std::cout << "No students found" << std::endl;
        }
}

void getStudentById() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
    SQLite::Statement query(db, "SELECT * FROM students WHERE id=?");
    int id;
    std::cin >> id;
    query.bind(1,id);
    while(query.tryExecuteStep() == SQLITE_ROW) {
        std::string name = query.getColumn("name").getString();
        std::string email = query.getColumn("email").getString();
        int year = query.getColumn("year").getInt();

        std::cout << "id: " << id;
        std::cout << ", name: " << name;
        std::cout << ", email: " << email;
        std::cout << ", year: " << year << std::endl;
        return;
    };
    std::cout << "No students found" << std::endl;
}

int getStudentId(std::string name) {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
    SQLite::Statement query(db, "SELECT * FROM students WHERE name=?");
    query.bind(1,name);
    while(query.tryExecuteStep() == SQLITE_ROW) {
        int id = query.getColumn("id").getInt();
        return id;
    };
}

void addStudent() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
    SQLite::Statement query(db, "INSERT INTO students (name, email, year) values (?, ?, ?)");
    std::string name;
    std::string email;
    int year;

    while (name.length() == 0) {
        std::getline(std::cin, name);
    }
    while (email.length() == 0) {
        std::getline(std::cin, email);
    }
    std::cin >> year;
    query.bind(1, name);
    query.bind(2, email);
    query.bind(3, year);

    if(query.exec() != 0) {
        std::cout << "Added student: id: " << getStudentId(name) << ", name: " << name << ", email: "
                  << email << ", year: " << year << std::endl;
    }
}

void editStudent() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
    SQLite::Statement query(db, "UPDATE students SET name = ?,email = ?, year = ? WHERE id =?;");
    // Inputs
    int id;
    std::string name;
    std::string email;
    int year;

    // Insert inputs
    std::cout << "Which student do you want to edit?" << std::endl;
    std::cin >> id;

    std::cout << "Name?" << std::endl;
    while (name.length() == 0) {
        std::getline(std::cin, name);
    }
    if(name == "7") {
        std::cout << "Student not found\n";
        exit(0);
    }
    std::cout << "Email?" << std::endl;
    while (email.length() == 0) {
        std::getline(std::cin, email);
    }
    std::cout << "Year?" << std::endl;
    std::cin >> year;

    // Binding values to query
    query.bind(1,name);
    query.bind(2,email);
    query.bind(3,year);
    query.bind(4,id);

    if(query.exec() != 0) std::cout << "Student was edited successfully\n";
    else std::cout << "Student not found\n";
}

void removeStudent() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
    SQLite::Statement query(db, "DELETE FROM students WHERE id=?;");

    int id;
    std::cout << "Which student should I remove?:" << std::endl;
    std::cin >> id;
    query.bind(1, id);
    if(query.exec() != 0)  std::cout << "Student was removed successfully\n";
    else std::cout << "Student not found\n";
}


void searchStudent() {
        SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE);
        std::string name;
        while (name.length() == 0) {
        std::getline(std::cin, name);
        }
    SQLite::Statement query(db, "SELECT * FROM students WHERE name LIKE ?");
    query.bind(1,name);
        while(query.tryExecuteStep() == SQLITE_ROW) {
            int id = query.getColumn("id").getInt();
            std::string name = query.getColumn("name").getString();
            std::string email = query.getColumn("email").getString();
            int year = query.getColumn("year").getInt();

            std::cout << "id: " << id;
            std::cout << ", name: " << name;
            std::cout << ", email: " << email;
            std::cout << ", year: " << year << std::endl;
        };
        std::cout << "No students found" << std::endl;
}

void menu() {
    std::cout <<
    "1.Read all students\n"
    "2.Get student by id\n"
    "3.Add student\n"
    "4.Edit student\n"
    "5.Remove student\n"
    "6.Search\n"
    "7.Exit" << std::endl;
};

int main() {
    int userInput;
    while(userInput != 7) {
        menu();
        std::cin >> userInput;

        switch(userInput) {

            case 1:
                readStudents();
                break;
            case 2:
                getStudentById();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                editStudent();
                break;
            case 5:
                removeStudent();
                break;
            case 6:
                searchStudent();
                break;
        }
    }
    return 0;
}
