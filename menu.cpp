#include "menu.hpp"
#include <filesystem>
#include <iomanip>
#include <iostream>

void Menu::mainMenu() {
    short choice = -1;
    std::string message = "Welcome. Choose an option.";
    std::cout <<  "\n..:: Univeristy DB ::..\n";
    menuPrintAll();
    while (choice != 0) {
        printOutputPanel(message);
        printMainMenu();
        std::cout << "> ";
        std::cin >> choice;
        switch (static_cast<Menu::MenuOption>(choice)) {
            case MenuOption::ReturnToOS: {
                std::cout << "Returned to OS.\n\n";
            }
            break;
            case MenuOption::PrintAll: {
                message = menuPrintAll();
            }
            break;
            case MenuOption::AddPerson: {
                message = menuAddPerson();
            }
            break;
            case MenuOption::RemovePerson: {
                message = menuRemovePerson();
            }
            break;
            case MenuOption::ChangeSalary: {
                message = menuChangeSalary();
            }
            break;
            case MenuOption::SortByLastName: {
                message = menuSortByLastName();                
            }
            break;
            case MenuOption::SortByPesel: {
                message = menuSortByPesel();
            }
            break;
            case MenuOption::SortBySalary: {
                message = menuSortBySalary();
            }
            break;
            case MenuOption::FindLastName: {
                message = menuFindLastName();
            }
            break;
            case MenuOption::FindPesel: {
                message = menuFindPesel();
            }
            break;
            case MenuOption::GenerateData: {
                message = menuGenerateData();
            }
            break;
            case MenuOption::SaveToFile: {
                message = menuSaveToFile();
            }
            break;
            case MenuOption::ReadFromFile: {
                message = menuReadFromFile();                
            }
            break;
            case MenuOption::ClearAll: {
                message = menuClearAll();
            }
            break;
            default: {
                std::cout << "Wrong option.\n\n";
            }
        }
    }
}

std::string Menu::menuPrintAll() {
    if (dataBase_.data().empty()) {
        printHeader();
        std::cout << "\n\n\t\tData base is empty.\n";
        std::cout << "\t\tGenerate data [10] or read a file [12].\n\n";
    } else {
        printGroup(dataBase_.data());
    }
    return "Choose an option.";
}

std::string Menu::menuAddPerson() {
    std::string firstName;
    std::string lastName;
    std::string pesel;
    std::string postalCode;
    std::string city;
    std::string streetAndNumber;
    Sex sex;
    std::cout << "Student or Employee? (s - student, e - employee): ";
    char type;
    std::cin >> type;
    if (!(type == 's' || type == 'e')) {
        return "Wrong input.";
    }
    std::cout << "First name: ";
    std::cin >> firstName;
    std::cout << "Last name: ";
    std::cin >> lastName;
    std::cout << "PESEL: ";
    std::cin >> pesel;
    std::cout << "Postal Code: ";
    std::cin >> postalCode;
    std::cout << "City: ";
    std::cin >> city;
    std::cout << "Street and number: ";
    std::getline(std::cin >> std::ws, streetAndNumber);
    std::cout << "Sex (m - male, f - female, o - other): ";
    char c;
    std::cin >> c;
    if (c == 'm') {
        sex = Sex::Male;
    } else if (c == 'f') {
        sex = Sex::Female;
    } else if (c == 'o') {
        sex = Sex::Other;
    } else {
        return "Wrong input";
    }
    ErrorCode error;
    if (type == 's') {
        size_t indexNumber;
        std::cout << "Index number (1 - " << DataBase::maxIndexNumber << "): ";
        std::cin >> indexNumber;
        error = dataBase_.addStudent(firstName,
                                     lastName,
                                     pesel,
                                     Address(postalCode, city, streetAndNumber),
                                     sex,
                                     indexNumber);
    }
    if (type == 'e') {
        size_t salary;
        std::cout << "Salary: ";
        std::cin >> salary;
        error = dataBase_.addEmployee(firstName,
                                      lastName,
                                      pesel,
                                      Address(postalCode, city, streetAndNumber),
                                      sex,
                                      salary);
    }
    printGroup(dataBase_.data());
    return error == ErrorCode::Ok
           ? "Person added without errors."
           : ("Cannot add a person. Error: " + errors[error]);
}

std::string Menu::menuRemovePerson() {
    std::cout << "Remove by PESEL or Index number? (p - PESEL, i - index num): ";
    ErrorCode error;
    char c;
    std::cin >> c;
    if (c == 'p') {
        std::cout << "Enter PESEL: ";
        std::string pesel;
        std::cin >> pesel;
        error = dataBase_.removePerson(pesel);
    } else if (c == 'i') {
        std::cout << "Enter index number: ";
        size_t indexNumber;
        std::cin >> indexNumber;
        error = dataBase_.removeStudent(indexNumber);
    } else {
        return "Wrong option.";
    }
    return error == ErrorCode::Ok
           ? "Person removed without errors."
           : ("Cannot remove a person. Error: " + errors[error]);}

std::string Menu::menuChangeSalary() {
    size_t newSalary = 0;
    std::string pesel;
    std::cout << "Enter employee's PESEL: ";
    std::cin >> pesel;
    std::cout << "Enter new salary: ";
    std::cin >> newSalary;
    ErrorCode error = dataBase_.changeSalary(pesel, newSalary);
    printGroup(dataBase_.data());
    return error == ErrorCode::Ok
           ? "Salary has been changed."
           : ("Cannot change. Error: " + errors[error]);
}

std::string Menu::menuSortByLastName() {
    dataBase_.sortByLastName();
    printGroup(dataBase_.data());
    return "Data base has been sorted by last name.";
}

std::string Menu::menuSortByPesel() {
    dataBase_.sortByPesel();
    printGroup(dataBase_.data());
    return "Data base has been sorted by PESEL.";
}

std::string Menu::menuSortBySalary() {
    dataBase_.sortBySalary();
    printGroup(dataBase_.data());
    return "Data base has been sorted by salary.";
}

std::string Menu::menuFindLastName() {
    std::cout << "Enter last name to find: ";
    std::string lastName;
    std:: cin >> lastName;
    std::vector<std::shared_ptr<Person>> results;
    ErrorCode error = dataBase_.searchStudentByLastName(lastName, results);
    if (error == ErrorCode::Ok) {
        printGroup(results);
        return "Found " + std::to_string(results.size()) + " records.";
    }
    printGroup(dataBase_.data());
    return "Cannot find '" + lastName + "'. Error: " + errors[error];
}

std::string Menu::menuFindPesel() {
    std::cout << "Enter some first digits of PESEL to find: ";
    std::string pesel;
    std:: cin >> pesel;
    std::vector<std::shared_ptr<Person>> results;
    ErrorCode error = dataBase_.searchStudentByPesel(pesel, results);
    if (error == ErrorCode::Ok) {
        printGroup(results);
        return "Found " + std::to_string(results.size()) + " records.";
    }
    printGroup(dataBase_.data());
    return "Cannot find '" + pesel + "'. Error: " + errors[error];
}

std::string Menu::menuGenerateData() {
    std::cout << "Enter number of people to generate: ";
    size_t amountOfPeople;
    std::cin >> amountOfPeople;
    dataBase_.generatePeople(amountOfPeople);
    printGroup(dataBase_.data());
    return std::to_string(amountOfPeople) + " people has been generated.";
}

std::string Menu::menuSaveToFile() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    if (std::filesystem::exists(filename)) {
        std::cout << "File " << filename << " already exist. Do you want to overwrite it? (y/n) :";
        char c;
        std::cin >> c;
        if (c == 'n') {
            return "Saving canceled.";
        } else if (c != 'y') {
            return "Wrong input.";
        }
    }
    ErrorCode error = dataBase_.saveFile(filename);
    printGroup(dataBase_.data());
    return error == ErrorCode::Ok
           ? "File saved without errors."
           : errors[error];
}

std::string Menu::menuReadFromFile() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    if (!std::filesystem::exists(filename)) {
        return "File " + filename + " not found.";
    }
    ErrorCode error = dataBase_.openFile(filename);
    printGroup(dataBase_.data());
    return error == ErrorCode::Ok
           ? "File opened without errors."
           : errors[error];
}

std::string Menu::menuClearAll() {
    std::cout << "Do you really want to clear all data base? (y - yes, n - no): ";
    char c;
    std::cin >> c;
    if (c == 'y') {
        dataBase_.clearAll();
        return "Data base has been cleared.";
    }
    return "Clear aborted.";
}

std::string Menu::encodeSex(const Sex& sex) const {
    return sex == Sex::Male ? "Male" : sex == Sex::Female ? "Female" : "Other";
}

std::string Menu::encodeType(const Person::PersonType& type) const {
    return type == Person::PersonType::Student ? "student" : "employee";
}

void Menu::printHeader(){
    printSeparator();
    std::cout << std::left;
    std::cout << std::setw(typeColumnWidth) << "type:"
              << std::setw(firstNameColumnWidth) << "first name:"
              << std::setw(lastNameColumnWidth) << "last name:"
              << std::setw(addressColumnWidth) << "address:"
              << std::setw(peselColumnWidth) << "PESEL:"
              << std::setw(sexColumnWidth) << "sex:"
              << std::setw(indexNumberColumnWidth) << "index num.:"
              << std::setw(sexColumnWidth) << "salary:"
              << '\n';
    printSeparator();
}

void Menu::printOutputPanel(const std::string& outputMessage) {
    printSeparator();
    std::cout << "DB size: " << dataBase_.data().size() << " | Output: " << outputMessage << '\n';
    printSeparator();
}

void Menu::printPerson(const std::shared_ptr<Person>& person) {
        std::cout << std::left << std::setfill(' ');
        std::cout << std::setw(typeColumnWidth) << encodeType(person->getType())
                  << std::setw(firstNameColumnWidth) << person->getFirstName()
                  << std::setw(lastNameColumnWidth) << person->getLastName()
                  << std::setw(addressColumnWidth) << person->getAddress()
                  << std::setw(peselColumnWidth) << person->getPesel()
                  << std::setw(sexColumnWidth) << encodeSex(person->getSex());
        if (person->getType() == Person::PersonType::Student) {
            std::cout << std::setw(indexNumberColumnWidth) << person->getIndexNumber()
                      << std::setw(salaryColumnWidth) << "---";
        } else {
            std::cout << std::setw(indexNumberColumnWidth) << "---"
                      << std::setw(salaryColumnWidth) << person->getSalary();
        }
        std::cout << '\n';
}

void Menu::printGroup(const std::vector<std::shared_ptr<Person>>& group) {
    printHeader();
    for (auto it = group.cbegin(); it != group.cend(); ++it) {
        printPerson(*it);
    }
}

void Menu::printMainMenu() const {
    uint8_t itemSize = 23;
    std::cout << std::left << std::setfill(' ');
    std::cout << std::setw(itemSize) << "[ 1] Print DB"
              << std::setw(itemSize) << "[ 4] Change salary"
              << std::setw(itemSize) << "[ 7] Sort by salary"
              << std::setw(itemSize) << "[10] Generate data"
              << std::setw(itemSize) << "[13] Clear all" << '\n'
              << std::setw(itemSize) << "[ 2] Add Person"
              << std::setw(itemSize) << "[ 5] Sort by last name"
              << std::setw(itemSize) << "[ 8] Find last name"
              << std::setw(itemSize) << "[11] Save to file"
              << std::setw(itemSize) << "[ 0] Quit" << '\n'
              << std::setw(itemSize) << "[ 3] Remove Person"
              << std::setw(itemSize) << "[ 6] Sort by PESEL"
              << std::setw(itemSize) << "[ 9] Find PESEL"
              << std::setw(itemSize) << "[12] Read from file" << '\n';
}

void Menu::printSeparator() {
    std::cout << std::right << std ::setfill('-') << std::setw(typeColumnWidth
                                                              + firstNameColumnWidth
                                                              + lastNameColumnWidth
                                                              + peselColumnWidth
                                                              + addressColumnWidth
                                                              + sexColumnWidth
                                                              + indexNumberColumnWidth
                                                              + salaryColumnWidth) << '\n';
    std::cout << std ::setfill(' ');
}
