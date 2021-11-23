#pragma once
#include "database.hpp"

class Menu {
public:
    Menu(DataBase& dataBase) : dataBase_{dataBase} {}
    
    void run();


    void printMainMenu();

private:
    DataBase& dataBase_;

};