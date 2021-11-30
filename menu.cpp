#include "menu.hpp"
#include <iostream>

void Menu::run() {

    mainMenu();
    
}

void Menu::menuAddStudent() {
    std::string firstName;
    std::string lastName;
    size_t indexNumber;
    std::string pesel;
    std::string postalCode;
    std::string city;
    std::string streetAndNumber;   // a może by tak ze string streamem?
    Sex sex;
    std::cout << "Enter student data:\n";
    std::cout << "First name: ";
    std::cin >> firstName;
    std::cout << "Last name: ";
    std::cin >> lastName;
    std::cout << "Index number: ";  // operator= dla studenta ??
    std::cin >> indexNumber;  // sprawdzic czy istnieje
    std::cout << "PESEL: ";
    std::cin >> pesel; // tez sprawdzac na przyszlosc
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
        std::cout << "Wrong input";
        return;
    }
    dataBase_.addStudent(firstName,
                         lastName,
                         indexNumber,
                         pesel,
                         Address(postalCode, city, streetAndNumber),
                         sex);                
}

void Menu::menuRemoveStudent() {
    std::cout << "Enter student's index number: ";
    size_t indexNumber;
    std::cin >> indexNumber;
    if (dataBase_.existsInDataBase(indexNumber)) {
        dataBase_.removeStudent(indexNumber);
    } else { // zmienic na kody bledow??
        std::cout << "Student with index no. " << indexNumber << " doesn't exist in data base.\n";
    }
}

void Menu::menuSortByLastName() {
    dataBase_.sortByLastName();
    std::cout << "Data base sorted by last name.\n\n";
}

void Menu::menuSortByPesel() {
    dataBase_.sortByPesel();
    std::cout << "Data base sorted by PESEL.\n\n";
}

void Menu::menuFindLastName() {
    std::cout << "Enter last name to find: ";
    std::string lastName;
    std:: cin >> lastName;
    dataBase_.searchStudentByLastName(lastName);
}

void Menu::menuFindPesel() {
    std::cout << "Enter some first digits of PESEL to find: ";
    std::string pesel;
    std:: cin >> pesel;
    dataBase_.searchStudentByPesel(pesel);
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

void Menu::mainMenu() {
    char choice = 0;
    while (choice != '0') {
        std::cout << "\t..:: Univeristy DB ::..\n";
        std::cout << "\t1. Print DB\n"
                  << "\t2. Add student\n"
                  << "\t3. Remove student\n"
                  << "\t4. Sort by last name\n"
                  << "\t5. Sort by PESEL\n"
                  << "\t6. Find last name\n"
                  << "\t7. Find PESEL\n"
                  << "\t8. Save to file\n"
                  << "\t9. Read from file\n"
                  << "\t0. Exit\n"
                  << "\t: ";
        std::cin >> choice;
        switch (choice) {
            case '1': {
                dataBase_.printAll();
            }
            break;
            case '2': {
                menuAddStudent();
            }
            break;
            case '3': {
                menuRemoveStudent();
            }
            break;
            case '4': {
                menuSortByLastName();                
            }
            break;
            case '5': {
                menuSortByPesel();
            }
            break;
            case '6': {
                menuFindLastName();
            }
            break;
            case '7': {
                menuFindPesel();
            }
            break;
            case '8': {
                menuSaveToFile();
            }
            break;
            case '9': {
                menuReadFromFile();                
            }
            break;
            case '0': {
                std::cout << "Returned to OS.\n\n";
            }
            break;
            default: {
                std::cout << "Wrong option.\n\n";
            }
        }

        // if (choice == '1') {
        //     dataBase_.printAll();
        // }
        // if (choice == '4') {
        //     dataBase_.sortByLastName();
        //     std::cout << "Data base sorted by last name.\n";
        // }
        // if (choice == '5') {
        //     dataBase_.sortByPESEL();
        //     std::cout << "Data base sorted by PESEL.\n";
        // }
    }

            // std::string lastName;
            // std::cout << "Enter last name to sorty by: ";
            // std::cin >> lastName;
    
    
}