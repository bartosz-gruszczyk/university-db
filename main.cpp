#include "database.hpp"
#include "menu.hpp"

int main() {
    // testDB.addStudent("Bartek", "Gruszczyk", "12345634129", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
    // testDB.addStudent("Stefan", "Grubson", "19283902329", Address("44-200", "Rybnik", "Gliwicka 667"), Sex::Male, 2);
    // testDB.addStudent("Ania", "Zalewska", "11122233449", Address("03-943", "Warszawa", "Paryska 668"), Sex::Female, 3);
    // testDB.addEmployee("Witold", "Konieczny", "73647382716", Address("77-777", "Otwock", "Bystra 669"), Sex::Male, 4020);
    // testDB.addStudent("Ameba", "Pierwotniak", "00990099002", Address("01-666", "Radom", "Morza radomskiego 9"), Sex::Other, 4);
    // testDB.addEmployee("Monika", "Lubicz", "93847560327", Address("09-622", "Wolniki", "Skrzetuskiego 9"), Sex::Female, 4300);
    // testDB.addEmployee("Krystian", "Zaremba", "34343434341", Address("44-200", "Rybnik", "Janasa 3"), Sex::Male, 3040);
    // testDB.addStudent("Jan", "Kowalski", "78785285242", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male, 5);
    // testDB.addStudent("Janoslaw", "Kowalczyk", "78787878785", Address("99-112", "Krakow", "Stawowa 700"), Sex::Male, 6);

    DataBase dataBase;
    Menu menu(dataBase);
    menu.mainMenu();

    return 0;
}