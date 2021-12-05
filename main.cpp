#include <iostream>
#include "address.hpp"
#include "database.hpp"
#include "menu.hpp"
#include "student.hpp"

#include <functional>

int main() {

    DataBase testDB;
    testDB.addStudent("Bartek", "Gruszczyk", "12345634126", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
    testDB.addStudent("Stefan", "Grubson", "09283902323", Address("44-200", "Rybnik", "Gliwicka 667"), Sex::Male, 2);
    testDB.addStudent("Ania", "Zalewska", "11122233449", Address("03-943", "Warszawa", "Paryska 668"), Sex::Female, 3);
    testDB.addEmployee("Witold", "Konieczny", "73647382712", Address("77-777", "Otwock", "Bystra 669"), Sex::Male, 4020);
    testDB.addStudent("Ameba", "Pierwotniak", "00990099009", Address("01-666", "Radom", "Morza radomskiego 9"), Sex::Other, 4);
    testDB.addEmployee("Monika", "Lubicz", "938475603232", Address("09-622", "Wolniki", "Skrzetuskiego 9"), Sex::Female, 4300);
    testDB.addEmployee("Krystian", "Zaremba", "34343434343", Address("44-200", "Rybnik", "Janasa 3"), Sex::Male, 3040);
    testDB.addStudent("Jan", "Kowalski", "78785285248", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male, 5);
    testDB.addStudent("Janoslaw", "Kowalczyk", "78787878788", Address("99-112", "Krakow", "Stawowa 700"), Sex::Male, 6);

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
    // std::cout << "opening db to file: " << testDB.openFile("savedDB.dat") << '\n';

    // testDB.printAll();

    // std::cout << std::boolalpha << "exist by iD: " << testDB.existsInDataBase(99) << '\n';
    // std::cout << std::boolalpha << "exist by pesel: " << testDB.existsInDataBase("7878") << '\n';
    
    testDB.changeSalary("938475603232");

    Menu menu(testDB);
    menu.run();

    // std::function<void()> func1 = &Menu::menuAddStudent;

    return 0;
}