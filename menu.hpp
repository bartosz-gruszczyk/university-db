#pragma once
#include "database.hpp"
#include "errors.hpp"
#include <map>
#include <functional>

class Menu {
public:
    uint8_t typeColumnWidth = 10;
    uint8_t columnWidth = 16;   //zrobic const......!!!
    uint8_t addressColumnWidth = 42;
    uint8_t sexColumnWidth = 10;
    uint8_t peselColumnWidth = 14;

    Menu(DataBase& dataBase) : dataBase_{dataBase} {
        // std::function<void()> func1 = &Menu::menuAddStudent;
        // menuItems.insert(std::pair{'2', &Menu::menuAddStudent});
    }
    
    void run();
    void mainMenu();

    void menuPrintAll();
    void menuAddPerson();
    void menuRemovePerson();
    void menuSortByLastName();
    void menuSortByPesel();
    void menuSortBySalary();
    void menuFindLastName();
    void menuFindPesel();
    void menuSaveToFile();
    void menuReadFromFile();

    std::string encodeSex(const Sex& sex) const;
    std::string encodeType(const Person::PersonType& type) const;

private:
    void printHeader();
    void printPerson(const std::shared_ptr<Person>& person);
    void printGroup(const std::vector<std::shared_ptr<Person>>& group);

    
    DataBase& dataBase_;

    std::map<ErrorCode, std::string> errors {
        {ErrorCode::Ok, "Ok"},
        {ErrorCode::InvalidPesel, "Invalid PESEL"},
        {ErrorCode::PeselAlreadyExists, "PESEL already exists"},
        {ErrorCode::PeselNotFound, "PESEL not found"},
        {ErrorCode::IndexNumberAlreadyExists, "Index number already exists"},
        {ErrorCode::IndexNumberNotFound, "Index number not found"},
        {ErrorCode::WrongIndexNumber, "Wrong index number"},
        {ErrorCode::LastNameNotFound, "Last name not found"},
        {ErrorCode::NotEmployee, "Person is not an employee"},
        {ErrorCode::PersonNotFound, "Person not found"}
    };
};