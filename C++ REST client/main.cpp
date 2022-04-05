// ---------------------------------------------------------------- INCLUDES ---------------------------------------------------------
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;



// ----------------------------------------------------------------- FUNCTIONS ----------------------------------------------------------

void menu() {
    std::cout <<
              "1.Read all students\n"
              "2.Get student by id\n"
              "3.Add student\n"
              "4.Edit student\n"
              "5.Remove student\n"
              "6.Exit"
              << std::endl;
}


void readAllStudents() {
    // Make GET request
    auto requestJson = http_client(U("http://localhost:5000/")).request(methods::GET,uri_builder(U("students")).to_string())

                    // Get the response.
            .then([=](const http_response& response) {
                // Check the status code.
                if (response.status_code() != 200 && response.status_code() != 404) {
                    throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                }

                // Convert the response body to JSON object.
                return response.extract_json();
            })
                // Parse the user details.
            .then([=](json::value jsonObject) {
                for (auto &student: jsonObject.as_array()) {
                    ucout
                            << "id: " << student[U("id")].as_integer()
                            << ", name: " << student[U("name")].as_string()
                            << ", email: " << student[U("email")].as_string()
                            << ", year: " << student[U("year")].as_integer() << std::endl;
                }

            });

// ------------------------------------------------------------- WAIT FOR REQUEST - EXCEPTION HANDLING -----------------------------------------------
    try {
        requestJson.wait();
    } catch (const std::exception &e) {
        printf("Error exception:%s\n", e.what());
    }
}

void getStudentById() {
    utility::string_t studentId;
    ucin >> studentId;
    // Make GET request
    auto requestJson = http_client(U("http://localhost:5000/"))
            .request(methods::GET,uri_builder(U("students/"))
            .append_path(studentId).to_string())

            // Get the response.
            .then([=](const http_response& response) {
                // Check the status code.
                if (response.status_code() != 200 && response.status_code() != 404) {
                    throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                }

                // Convert the response body to JSON object.
                return response.extract_json();
            })
                    // Parse the user details.
            .then([=](json::value jsonObject) {
                ucout
                        << "id: " << jsonObject[U("id")].as_integer()
                        << ", name: " << jsonObject[U("name")].as_string()
                        << ", email: " << jsonObject[U("email")].as_string()
                        << ", year: " << jsonObject[U("year")].as_integer() << std::endl;
            });

// ------------------------------------------------------------- WAIT FOR REQUEST - EXCEPTION HANDLING -----------------------------------------------
    try {
        requestJson.wait();
    } catch (const std::exception &e) {
        ucout << "\nStudent not found\n";
    }
}

void addStudent() {
    utility::string_t nameOfStudent = {};
    utility::string_t emailOfStudent = {};
    utility::string_t yearOfStudent = {};
    ucin.ignore();
    // Get inputs
    std::cout << "Enter name of student:" << std::endl;
    std::getline(ucin, nameOfStudent);
    std::cout << "Enter email of student:" << std::endl;
    ucin >> emailOfStudent;
    std::cout << "Enter year of student:" << std::endl;
    ucin >> yearOfStudent;


    // Make POST request
    auto postJson = pplx::create_task([nameOfStudent, emailOfStudent, yearOfStudent]() {
        json::value jsonObject;
        jsonObject[U("name")] = json::value::string(nameOfStudent);
        jsonObject[U("email")] = json::value::string(emailOfStudent);
        jsonObject[U("year")] = json::value::number(std::stoi(yearOfStudent));

        ucout << "Variables initialised\n"
            << "name: " << jsonObject[U("name")].as_string()
            << ", email: " << jsonObject[U("email")].as_string()
            << ", year: " << jsonObject[U("year")].as_integer()
            << std::endl;

         return http_client(U("http://localhost:5000/"))
                .request(methods::POST,
                         uri_builder().append_path(U("students/")).to_string(),
                            jsonObject.serialize(), U("application/json"));
    })

            // Get the response.
            .then([](const http_response response) {
                // Check the status code.
                if (response.status_code() != 201) {
                    throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                }

                // Convert the response body to JSON object.
                return response.extract_json();
            })

            .then([](json::value jsonObject) {

                ucout
                        << "Added student: "
                        << "id: " << jsonObject[U("id")].as_integer()
                        << ", name: " << jsonObject[U("name")].as_string()
                        << ", email: " << jsonObject[U("email")].as_string()
                        << ", year: " << jsonObject[U("year")].as_integer()
                        << std::endl;
            });

// ------------------------------------------------------------- WAIT FOR REQUEST - EXCEPTION HANDLING -----------------------------------------------
    try {
        postJson.wait();
    } catch (const std::exception &e) {
        printf("Error exception:%s\n", e.what());    }
}

void editStudent() {
    utility::string_t studentOfChoice = {};
    utility::string_t nameOfStudent = {};
    utility::string_t emailOfStudent = {};
    utility::string_t yearOfStudent = {};
    utility::string_t idOfStudent = {};
    ucin.ignore();

    // Get inputs
    std::cout << "Enter id of student:" << std::endl;
    while (idOfStudent.length() == 0) {
        std::getline(ucin, idOfStudent);
    }
    std::cout << "Enter name of student:" << std::endl;
    while (nameOfStudent.length() == 0) {
        std::getline(ucin, nameOfStudent);
    }
    std::cout << "Enter email of student:" << std::endl;
    while (emailOfStudent.length() == 0) {
        std::getline(ucin, emailOfStudent);
    }
    std::cout << "Enter year of student:" << std::endl;
    ucin >> yearOfStudent;


    // Make PUT request
    auto putJson = pplx::create_task([nameOfStudent, emailOfStudent, yearOfStudent, idOfStudent]() {
        json::value jsonObject;
        jsonObject[U("id")] = json::value::number(std::stoi(idOfStudent));
        jsonObject[U("name")] = json::value::string(nameOfStudent);
        jsonObject[U("email")] = json::value::string(emailOfStudent);
        jsonObject[U("year")] = json::value::number(std::stoi(yearOfStudent));

        return http_client(U("http://localhost:5000/"))
                .request(methods::PUT,
                         uri_builder().append_path(U("students/")).append_path(U("" + idOfStudent)).to_string(),
                         jsonObject.serialize(),
                         U("application/json"));
    })

            // Get the response.
            .then([](http_response response) {
                if (response.status_code() != 200) {
                    throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                }

                // Convert the response body to JSON object.
                return response.extract_json();
            })

            .then([](json::value jsonObject) {

                ucout << "Student was edited successfully\n";
                /*
                        << "Edited student\n"
                        << "id: " << jsonObject[U("id")].as_integer()
                        << ", name: " << jsonObject[U("name")].as_string()
                        << ", email: " << jsonObject[U("email")].as_string()
                        << ", year: " << jsonObject[U("year")].as_integer()
                        << std::endl;
                        */
            });

// ------------------------------------------------------------- WAIT FOR REQUEST - EXCEPTION HANDLING -----------------------------------------------
    try {
        putJson.wait();
    } catch (const std::exception &e) {
        printf("Student not found\n");
    }
}
void removeStudent() {
    utility::string_t idOfStudent = {};
    std::cout << "Enter id of student:" << std::endl;
    while (idOfStudent.length() == 0) {
        std::getline(ucin, idOfStudent);
    }
    // Make DEL request.
    auto deleteJson = http_client(U("http://localhost:5000/"))
            .request(methods::DEL,
                     uri_builder().append_path(U("students/")).append_path(idOfStudent).to_string())

                    // Get the response.
            .then([](http_response response) {
                if(response.status_code() == 204) {
                    ucout << "Student was removed successfully\n";
                } else {
                    ucout << "Student not found\n";
                }
            });
}



// --------------------------------------------------------------MAIN -----------------------------------------------------------------

int main() {
    int menuChoice = 0;
    while(menuChoice != 6) {
        menu();
        std::cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                readAllStudents();
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
        }
    }
    return 0;
}