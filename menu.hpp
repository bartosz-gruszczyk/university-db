#pragma once
#include <map>
#include "database.hpp"
#include "errors.hpp"

class Menu {
private:
    enum class MenuOption {
        ReturnToOS = 0,
        PrintAll,
        AddPerson,
        RemovePerson,
        ChangeSalary,
        SortByLastName,
        SortByPesel,
        SortBySalary,
        FindLastName,
        FindPesel,
        GenerateData,
        SaveToFile,
        ReadFromFile,
        ClearAll
    };

public:
    constexpr const static uint8_t typeColumnWidth = 10;
    constexpr const static uint8_t firstNameColumnWidth = 16;   
    constexpr const static uint8_t lastNameColumnWidth = 16;   
    constexpr const static uint8_t peselColumnWidth = 14;
    constexpr const static uint8_t addressColumnWidth = 42;
    constexpr const static uint8_t sexColumnWidth = 8;
    constexpr const static uint8_t indexNumberColumnWidth = 12;
    constexpr const static uint8_t salaryColumnWidth = 10;

    Menu(DataBase& dataBase) : dataBase_{dataBase} {}
    
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
    void printOutputPanel(const std::string& outputMessage);
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
        {ErrorCode::NotEmployee, "Person is not an employee"},
        {ErrorCode::CantSaveFile, "Cannot save to file"},
        {ErrorCode::CantOpenFile, "Cannot open file"}
    };
};
