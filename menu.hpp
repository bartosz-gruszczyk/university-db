#pragma once
#include "database.hpp"
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

    void menuAddStudent();
    void menuRemoveStudent();
    void menuSortByLastName();
    void menuSortByPesel();
    void menuFindLastName();
    void menuFindPesel();
    void menuSaveToFile();
    void menuReadFromFile();

private:
    std::map<char, std::function<void()>> menuItems; 
    // {
        // {'2', &Menu::menuAddStudent} 
    // };

    DataBase& dataBase_;
};