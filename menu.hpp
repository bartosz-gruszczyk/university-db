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

private:
    DataBase& dataBase_;

};