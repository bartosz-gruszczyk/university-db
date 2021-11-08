#include <iostream>
#include "address.hpp"
#include "database.hpp"
#include "student.hpp"

int main() {

    // Student testStudent("Bartek", "Gruszczyk", 1, "12345634126", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male);
    // testStudent.print();

    DataBase testDB;
    testDB.addStudent("Bartek", "Gruszczyk", 1, "12345634126", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male);
    testDB.addStudent("Stefan", "Nowak", 2, "09283902323", Address("44-200", "Rybnik", "Gliwicka 667"), Sex::Male);
    testDB.addStudent("Ania", "Zalewska", 3, "11122233449", Address("03-943", "Warszawa", "Paryska 668"), Sex::Female);
    testDB.addStudent("Ameba", "Pierwotniak", 4, "00990099009", Address("01-666", "Radom", "Morza radomskiego 9"), Sex::Other);
    testDB.addStudent("Jan", "Kowalski", 5, "74185285248", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male);
    testDB.addStudent("Janoslaw", "Kowalczyk", 6, "78787878788", Address("99-112", "Krakow", "Stawowa 700"), Sex::Male);
    testDB.printAll();
    testDB.removeStudent(3);
    std::cout << "removing student...\n\n";
    testDB.printAll();
    std::cout << "find student...\n\n";
    testDB.searchStudentByLastName("Kowa");
    return 0;
}