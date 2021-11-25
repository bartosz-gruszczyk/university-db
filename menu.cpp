#include "menu.hpp"
#include <iostream>

void Menu::run() {

    printMainMenu();
    
}

void Menu::printMainMenu() {
    char choice = 0;
    while (choice != '8') {
        std::cout << "\t..:: Univeristy DB ::..\n";
        std::cout << "\t1. Print DB\n"
                  << "\t2. Add student\n"
                  << "\t3. Remove student\n"
                  << "\t4. Sort by last name\n"
                  << "\t5. Sort by PESEL\n"
                  << "\t6. Find last name\n"
                  << "\t7. Find PESEL\n"
                  << "\t8. Exit\n"
                  << "\t: ";
        std::cin >> choice;
        switch (choice) {
            case '1': {
                dataBase_.printAll();
            }
            break;
            case '2': {
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

            
            }
            break;

            case '4': {
                dataBase_.sortByLastName();
                std::cout << "Data base sorted by last name.\n\n";
            }
            break;
            case '5': {
                dataBase_.sortByPESEL();
                std::cout << "Data base sorted by PESEL.\n\n";
            }
            break;
            case '6': {
                std::cout << "Enter last name to find: ";
                std::string lastName;
                std:: cin >> lastName;
                dataBase_.searchStudentByLastName(lastName);
            }
            break;
            case '7': {
                std::cout << "Enter some first digits of PESEL to find: ";
                std::string pesel;
                std:: cin >> pesel;
                dataBase_.searchStudentByPESEL(pesel);
            }
            break;
            case '8': {
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