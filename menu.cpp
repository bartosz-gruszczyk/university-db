#include "menu.hpp"
#include <iostream>
#include <iomanip>

void Menu::run() {

    mainMenu();
    
}

void Menu::mainMenu() {
    short choice = -1;
    while (choice != 0) {
        std::cout << "\n\t..:: Univeristy DB ::..\n";
        // std::cout << "\t 1. Print DB\n"
        //           << "\t 2. Add Person\n"
        //           << "\t 3. Remove Person\n"
        //           << "\t 4. Change salary\n"
        //           << "\t 5. Sort by last name\n"
        //           << "\t 6. Sort by PESEL\n"
        //           << "\t 7. Sort by salary\n"
        //           << "\t 8. Find last name\n"
        //           << "\t 9. Find PESEL\n"
        //           << "\t10. Generate data\n"
        //           << "\t11. Save to file\n"
        //           << "\t12. Read from file\n"
        //           << "\t0. Exit\n"
        //           << "\t: ";
        printMainMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: {
                menuPrintAll();
            }
            break;
            case 2: {
                menuAddPerson();
            }
            break;
            case 3: {
                menuRemovePerson();
            }
            break;
            case 4: {
                menuChangeSalary();
            }
            break;
            case 5: {
                menuSortByLastName();                
            }
            break;
            case 6: {
                menuSortByPesel();
            }
            break;
            case 7: {
                menuSortBySalary();
            }
            break;
            case 8: {
                menuFindLastName();
            }
            break;
            case 9: {
                menuFindPesel();
            }
            break;
            case 10: {
                menuGenerateData();
            }
            break;
            case 11: {
                menuSaveToFile();
            }
            break;
            case 12: {
                menuReadFromFile();                
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

void Menu::menuPrintAll() {
    printGroup(dataBase_.data());
}

void Menu::menuAddPerson() {
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
        std::cout << "Wrong input\n";
        return;
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
        std::cout << "Wrong input\n";
        return;
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
    std::cout << "Operation result: " << errors[error] << '\n';
}

void Menu::menuRemovePerson() {
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
        std::cout << "Wrong input\n";
        return;
    }
    std::cout << "Operation result: " << errors[error] << '\n';
}

void Menu::menuChangeSalary() {
    size_t newSalary = 0;
    std::string pesel;
    std::cout << "Enter employee's PESEL: ";
    std::cin >> pesel;
    std::cout << "Enter new salary: ";
    std::cin >> newSalary;
    ErrorCode error = dataBase_.changeSalary(pesel, newSalary);
    std::cout << "Operation result: " << errors[error] << '\n';
}

void Menu::menuSortByLastName() {
    dataBase_.sortByLastName();
    std::cout << "Data base has been sorted by last name.\n\n";
}

void Menu::menuSortByPesel() {
    dataBase_.sortByPesel();
    std::cout << "Data base has been sorted by PESEL.\n\n";
}

void Menu::menuSortBySalary() {
    dataBase_.sortBySalary();
    std::cout << "Data base has been sorted by salary.\n\n";
}

void Menu::menuFindLastName() {
    std::cout << "Enter last name to find: ";
    std::string lastName;
    std:: cin >> lastName;
    std::vector<std::shared_ptr<Person>> results; // moze jakies reserve czy cos?
    ErrorCode error = dataBase_.searchStudentByLastName(lastName, results);
    std::cout << "Operation result: " << errors[error] << '\n';
    if (error == ErrorCode::Ok) {
        printGroup(results);
    }
}

void Menu::menuFindPesel() {
    std::cout << "Enter some first digits of PESEL to find: ";
    std::string pesel;
    std:: cin >> pesel;
    std::vector<std::shared_ptr<Person>> results;
    ErrorCode error = dataBase_.searchStudentByPesel(pesel, results);
    std::cout << "Operation result: " << errors[error] << '\n';
    if (error == ErrorCode::Ok) {
        printGroup(results);
    }
}

void Menu::menuGenerateData() {
    std::cout << "Enter number of people to generate: ";
    size_t amountOfPeople;
    std::cin >> amountOfPeople;
    dataBase_.generatePeople(amountOfPeople);
}

void Menu::menuSaveToFile() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    dataBase_.saveFile(filename);
}

void Menu::menuReadFromFile() {
    std::cout << "Enter filename: ";
    std::string filename;
    std::cin >> filename;
    dataBase_.openFile(filename);
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
              << std::setw(columnWidth) << "first name:"
              << std::setw(columnWidth) << "last name:"
              << std::setw(addressColumnWidth) << "address:"
              << std::setw(peselColumnWidth) << "PESEL:"
              << std::setw(sexColumnWidth) << "sex:"
              << std::setw(columnWidth) << "index number:"
              << std::setw(columnWidth) << "salary:"
              << '\n';
}

void Menu::printPerson(const std::shared_ptr<Person>& person) {
        // std::cout.setf(std::ios::left);
        std::cout << std::left;
        std::cout << std::setw(typeColumnWidth) << encodeType(person->getType())
                  << std::setw(columnWidth) << person->getFirstName()  // zrobic constexpr
                  << std::setw(columnWidth) << person->getLastName()
                  << std::setw(addressColumnWidth) << person->getAddress()   // zrobic const wartosc kolumny address
                  << std::setw(peselColumnWidth) << person->getPesel()
                  << std::setw(sexColumnWidth) << encodeSex(person->getSex());
        if (person->getType() == Person::PersonType::Student) {
            std::cout << std::setw(columnWidth) << person->getIndexNumber()
                      << std::setw(sexColumnWidth) << std::right << "---";
        } else {
            std::cout << std::setw(columnWidth) << "---"
                      << std::setw(sexColumnWidth) << std::right << person->getSalary();
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
    char block = 26;
    std::cout << std::left;
    std::cout << block << std::setw(16) << " 1. Print DB"
              << block << std::setw(16) << " 2. Add Person"
              << block << std::setw(16) << " 3. Remove Person"
              << block << std::setw(16) << " 4. Change salary"
              << block << std::setw(18) << " 5. Sort by last name"
              << block << std::setw(18) << " 6. Sort by PESEL"
              << block << std::setw(16) << " 7. Sort by salary\n"
              << block << std::setw(16) << " 8. Find last name"
              << block << std::setw(16) << " 9. Find PESEL"
              << block << std::setw(16) << " 10. Generate data"
              << block << std::setw(16) << " 11. Save to file"
              << block << std::setw(16) << " 12. Read from file"
              << block << std::setw(16) << " 0. Quit";
}