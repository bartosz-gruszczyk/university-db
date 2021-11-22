#include "menu.hpp"
#include <iostream>

void Menu::run() {

}

void Menu::printMainMenu() {
    std::cout << "..:: Univeristy DB ::..\n";
    std::cout << "1. Print DB\n"
              << "2. Add student\n"
              << "3. Remove student\n"
              << "4. Sort by last name\n"
              << "5. Sort by PESEL\n"
              << "6. Find last name\n"
              << "7. Find PESEL\n"
              << ": ";
}