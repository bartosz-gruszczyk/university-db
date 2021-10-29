#include <iostream>
#include "address.hpp"
#include "database.hpp"
#include "student.hpp"

int main() {

    // Student testStudent("Bartek", "Gruszczyk", 1, "12345634126", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male);
    // testStudent.print();

    DataBase testDB;
    testDB.addStudent("Bartek", "Gruszczyk", 1, "12345634126", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male);
    testDB.printAll();
    return 0;
}