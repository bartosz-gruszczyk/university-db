#pragma once
#include "database.hpp"
#include "errors.hpp"
#include <map>
#include <functional>

class Menu {
public:
    uint8_t typeColumnWidth = 10;
    uint8_t firstNameColumnWidth = 16;   
    uint8_t lastNameColumnWidth = 16;   
    uint8_t peselColumnWidth = 14;
    uint8_t addressColumnWidth = 42;
    uint8_t sexColumnWidth = 8;
    uint8_t indexNumberColumnWidth = 12;
    uint8_t salaryColumnWidth = 10;

    
    Menu(DataBase& dataBase) : dataBase_{dataBase} {
        // std::function<void()> func1 = &Menu::menuAddStudent;
        // menuItems.insert(std::pair{'2', &Menu::menuAddStudent});
    }
    
    void run();
    void mainMenu();

    std::string menuPrintAll();
    std::string menuAddPerson();
    std::string menuRemovePerson();
    std::string menuChangeSalary();
    std::string menuSortByLastName();
    std::string menuSortByPesel();
    std::string menuSortBySalary();
    std::string menuFindLastName();
    std::string menuFindPesel();
    std::string menuGenerateData();
    std::string menuSaveToFile();
    std::string menuReadFromFile();
    std::string menuClearAll();

    std::string encodeSex(const Sex& sex) const;
    std::string encodeType(const Person::PersonType& type) const;

private:
    void printMainMenu() const;
    void printHeader();
    void printSeparator();
    void printPerson(const std::shared_ptr<Person>& person);
    void printGroup(const std::vector<std::shared_ptr<Person>>& group);

    
    DataBase& dataBase_;

    std::map<ErrorCode, std::string> errors {
        {ErrorCode::Ok, "Ok"},
        {ErrorCode::InvalidPesel, "Invalid PESEL"},
        {ErrorCode::PeselAlreadyExists, "PESEL already exists"},
        {ErrorCode::PeselNotFound, "PESEL not found"},
        {ErrorCode::InvalidIndexNumber, "Invalid index number"},
        {ErrorCode::IndexNumberAlreadyExists, "Index number already exists"},
        {ErrorCode::IndexNumberNotFound, "Index number not found"},
        {ErrorCode::InvalidSalary, "Ivalid salary value"},
        {ErrorCode::LastNameNotFound, "Last name not found"},
        {ErrorCode::NotEmployee, "Person is not an employee"}
        // {ErrorCode::PersonNotFound, "Person not found"}
    };
};