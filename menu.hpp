#pragma once
#include "database.hpp"

class Menu {
public:
    Menu(DataBase& dataBase) : dataBase_{dataBase} {}
    
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
    DataBase& dataBase_;

};