#include <iostream>
#include "address.hpp"
#include "database.hpp"
#include "student.hpp"

int main() {

    DataBase testDB;
    // testDB.addStudent("Bartek", "Gruszczyk", 1, "12345634126", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male);
    // testDB.addStudent("Stefan", "Grubson", 2, "09283902323", Address("44-200", "Rybnik", "Gliwicka 667"), Sex::Male);
    // testDB.addStudent("Ania", "Zalewska", 3, "11122233449", Address("03-943", "Warszawa", "Paryska 668"), Sex::Female);
    // testDB.addStudent("Ameba", "Pierwotniak", 4, "00990099009", Address("01-666", "Radom", "Morza radomskiego 9"), Sex::Other);
    // testDB.addStudent("Jan", "Kowalski", 5, "78785285248", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male);
    // testDB.addStudent("Janoslaw", "Kowalczyk", 6, "78787878788", Address("99-112", "Krakow", "Stawowa 700"), Sex::Male);
    // testDB.printAll();
    // testDB.removeStudent(3);
    // std::cout << "removing student...\n\n";
    // testDB.printAll();
    // std::cout << "find student by name...\n\n";
    // testDB.searchStudentByLastName("kowa");

    // std::cout << "find student by PESEL...\n\n";
    // testDB.searchStudentByPESEL("7878");

    // std::cout << "sorting by lastName...\n\n";
    // testDB.sortByLastName();
    // testDB.printAll();
    // std::cout << "sorting by PESEL...\n\n";
    // testDB.sortByPESEL();
    // testDB.printAll();

    // std::cout << "\nTesting pesel validation: \n";
    // std::string pesel1 = "87070907879";
    // std::cout << std::boolalpha << pesel1 << ": " << testDB.validatePESEL(pesel1) << '\n'; 
    // std::string pesel2 = "55030101193";
    // std::cout << std::boolalpha << pesel2 << ": " << testDB.validatePESEL(pesel2) << '\n'; 
    // std::string pesel3 = "55030101230";
    // std::cout << std::boolalpha << pesel3 << ": " << testDB.validatePESEL(pesel3) << '\n'; 
    // std::string pesel4 = "20272904006";
    // std::cout << std::boolalpha << pesel4 << ": " << testDB.validatePESEL(pesel4) << '\n'; 

    // std::cout << "saving db to file: " << testDB.saveFile("savedDB.dat") << '\n';
    std::cout << "opening db to file: " << testDB.openFile("savedDB.dat") << '\n';

    testDB.printAll();
    
    
    return 0;
}