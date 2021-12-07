#pragma once
#include "database.hpp"
#include "errors.hpp"
#include <map>
#include <functional>

class Menu {
public:
    Menu(DataBase& dataBase) : dataBase_{dataBase} {
        // std::function<void()> func1 = &Menu::menuAddStudent;
        // menuItems.insert(std::pair{'2', &Menu::menuAddStudent});
    }
    
    void run();


    void mainMenu();
    // void printMainMenu();

    void menuAddPerson();
    void menuRemovePerson();
    void menuSortByLastName();
    void menuSortByPesel();
    void menuSortBySalary();
    void menuFindLastName();
    void menuFindPesel();
    void menuSaveToFile();
    void menuReadFromFile();

private:
    // std::map<char, std::function<void()>> menuItems; 
    DataBase& dataBase_;

    std::map<ErrorCode, std::string> errors {
        {ErrorCode::Ok, "Ok"},
        {ErrorCode::InvalidPesel, "Invalid PESEL"},
        {ErrorCode::PeselAlreadyExists, "PESEL already exists"},
        {ErrorCode::PeselNotFound, "PESEL not found"},
        {ErrorCode::IndexNumberAlreadyExists, "Index number already exists"},
        {ErrorCode::IndexNumberNotFound, "Index number not found"},
        {ErrorCode::WrongIndexNumber, "Wrong index number"},
        {ErrorCode::PersonNotFound, "Person not found"}
    };
};