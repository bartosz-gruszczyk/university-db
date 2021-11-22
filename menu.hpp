#pragma once
#include "database.hpp"

class Menu {
public:
    void run();


    void printMainMenu();

private:
    DataBase& dataBase;

};