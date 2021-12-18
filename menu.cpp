#include "menu.hpp"
#include <iostream>
#include <iomanip>

void Menu::run() {

    mainMenu();
    
}

void Menu::mainMenu() {
    short choice = -1;
    std::string message = "Welcome. Choose an option.";
    while (choice != 0) {
        std::cout << std::internal << "\n\t..:: Univeristy DB ::..\n";
        menuPrintAll();
        printSeparator();
        std::cout << "\033[33m" << "Output: " << message << "\033[0m" << '\n';
        printMainMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: {
                message = menuPrintAll();
            }
            break;
            case 2: {
                message = menuAddPerson();
            }
            break;
            case 3: {
                message = menuRemovePerson();
            }
            break;
            case 4: {
                message = menuChangeSalary();
            }
            break;
            case 5: {
                message = menuSortByLastName();                
            }
            break;
            case 6: {
                message = menuSortByPesel();
            }
            break;
            case 7: {
                message = menuSortBySalary();
            }
            break;
            case 8: {
                message = menuFindLastName();
            }
            break;
            case 9: {
                message = menuFindPesel();
            }
            break;
            case 10: {
                message = menuGenerateData();
            }
            break;
            case 11: {
                message = menuSaveToFile();
            }
            break;
            case 12: {
                message = menuReadFromFile();                
            }
            break;
            case 13: {
                message = menuClearAll();
            }
            break;
            case 0: {
                std::cout << "Returned to OS.\n\n";
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
        std::cout << "\n\n\n\t\t\tData base is empty...\n\n\n";
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
    std::string streetAndNumber;   // a może by tak ze string streamem?
    Sex sex;
    std::cout << "Student or Employee? (s - student, e - employee): ";
    char type;
    std::cin >> type;
    if (!(type == 's' || type == 'e')) {
        // std::cout << "Wrong input\n";
        return "Wrong type input.";
    }
    std::cout << "First name: ";
    std::cin >> firstName;
    std::cout << "Last name: ";
    std::cin >> lastName;
    std::cout << "PESEL: ";
    std::cin >> pesel; // tez sprawdzac na przyszlosc
    std::cout << "Postal Code: ";
    std::cin >> postalCode;
    std::cout << "City: ";
    std::cin >> city; /// cost tu jest nie tak std::ws
    std::cout << "Street and number: ";
    std::getline(std::cin >> std::ws, streetAndNumber);
    // std::getline(std::cin, streetAndNumber);
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
        // std::cout << "Wrong input\n";
        return "Wrong sex input";  // zamienic na error code?
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
        // std::cout << "Wrong input\n";
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
    return error == ErrorCode::Ok
           ? "Salary has been changed."
           : ("Cannot change. Error: " + errors[error]);
}

std::string Menu::menuSortByLastName() {
    dataBase_.sortByLastName();
    return "Data base has been sorted by last name.";
}

std::string Menu::menuSortByPesel() {
    dataBase_.sortByPesel();
    return "Data base has been sorted by PESEL.";
}

std::string Menu::menuSortBySalary() {
    dataBase_.sortBySalary();
    return "Data base has been sorted by salary.";
}

std::string Menu::menuFindLastName() {
    std::cout << "Enter last name to find: ";
    std::string lastName;
    std:: cin >> lastName;
    std::vector<std::shared_ptr<Person>> results; // moze jakies reserve czy cos?
    ErrorCode error = dataBase_.searchStudentByLastName(lastName, results);
    if (error == ErrorCode::Ok) {
        printGroup(results);
        return "Found " + std::to_string(results.size()) + " records.";
    }
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
    return "Cannot find '" + pesel + "'. Error: " + errors[error];
}

std::string Menu::menuGenerateData() {
    std::cout << "Enter number of people to generate: ";
    size_t amountOfPeople;
    std::cin >> amountOfPeople;
    dataBase_.generatePeople(amountOfPeople);
    return std::to_string(amountOfPeople) + "people has been generated.";
}

std::string Menu::menuSaveToFile() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    dataBase_.saveFile(filename);
    return "...";
}

std::string Menu::menuReadFromFile() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    dataBase_.openFile(filename);
    return "...";
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
    // std::cout << "vector size: " << people_.size() << '\n'; // raczej do wywalenia
    std::cout << std::left;
    std::cout << std::setw(typeColumnWidth) << "type:"
              << std::setw(firstNameColumnWidth) << "first name:"
              << std::setw(lastNameColumnWidth) << "last name:"
              << std::setw(addressColumnWidth) << "address:"
              << std::setw(peselColumnWidth) << "PESEL:"
              << std::setw(sexColumnWidth) << "sex:"
              << std::setw(indexNumberColumnWidth) << "index num.:"
              << std::setw(sexColumnWidth) << "salary:"     // zmienic na 
              << '\n';
    printSeparator();
}

void Menu::printPerson(const std::shared_ptr<Person>& person) {
        // std::cout.setf(std::ios::left);
        std::cout << std::left << std::setfill(' ');
        std::cout << std::setw(typeColumnWidth) << encodeType(person->getType())
                  << std::setw(firstNameColumnWidth) << person->getFirstName()  // zrobic constexpr
                  << std::setw(lastNameColumnWidth) << person->getLastName()
                  << std::setw(addressColumnWidth) << person->getAddress()   // zrobic const wartosc kolumny address
                  << std::setw(peselColumnWidth) << person->getPesel()
                  << std::setw(sexColumnWidth) << encodeSex(person->getSex());
        if (person->getType() == Person::PersonType::Student) {
            std::cout << std::setw(indexNumberColumnWidth) << person->getIndexNumber() //  << std::right
                      << std::setw(salaryColumnWidth) << "---";
        } else {
            std::cout << std::setw(indexNumberColumnWidth) << "---"    // << std::right
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

//  std::cout << "\n\t..:: Univeristy DB ::..\n";
//                   << "\t 7. Sort by salary\n"
//                   << "\t 8. Find last name\n"
//                   << "\t 9. Find PESEL\n"
//                   << "\t10. Generate data\n"
//                   << "\t11. Save to file\n"
//                   << "\t12. Read from file\n"
//                   << "\t0. Exit\n"
//                   << "\t: ";

void Menu::printMainMenu() const {
    // char block = 26;
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
    std::cout << std::right <<std ::setfill('-') << std::setw(typeColumnWidth
                                                              + firstNameColumnWidth
                                                              + lastNameColumnWidth
                                                              + peselColumnWidth
                                                              + addressColumnWidth
                                                              + sexColumnWidth
                                                              + indexNumberColumnWidth
                                                              + salaryColumnWidth) << '\n';

}