    // Przechowywanie rekordów studentów o strukturze: Imię,,
    //  nazwisko, adres, nr indeksu, PESEL, płeć
    // Dodawanie nowych studentów
    // Wyświetlanie całej bazy danych
    // Wyszukiwanie po nazwisku
    // Wyszukiwanie po numerze PESEL
    // Sortowanie po numerze PESEL
    // Sortowanie po nazwisku
    // Usuwanie po numerze indeksu

    // Przechowywanie rekordów pracowników uczelni o strukturze: imię, nazwisko, PESEL, płeć, adres, zarobki
    // Wszystkie osoby niezależnie czy będą to pracownicy, czy studenci mają być trzymani w jednym kontenerze
    // Wypełnianie bazy danych sztucznymi danymi (generowanie danych)
    // Modyfikacja zarobków wyszukując osobę po numerze PESEL (problematyczne)
    // Sortowanie po zarobkach (problematyczne)

#pragma once
#include <memory>
#include <vector>
#include "person.hpp"
#include "student.hpp"
#include "employee.hpp"
#include "errors.hpp"

class DataBase {
public:
    uint8_t typeColumnWidth = 10;
    uint8_t columnWidth = 16;   //zrobic const......!!!
    uint8_t addressColumnWidth = 42;
    uint8_t sexColumnWidth = 10;
    uint8_t peselColumnWidth = 14;
    
    ErrorCode addStudent(const std::string& firstName,
                         const std::string& lastName,
                         const std::string& pesel,
                         const Address& address,
                         const Sex& sex,
                         const size_t& indexNumber);
    ErrorCode addEmployee(const std::string& firstName,
                          const std::string& lastName,
                          const std::string& pesel,
                          const Address& address,
                          const Sex& sex,
                          const size_t& salary);
    ErrorCode removeStudent(const size_t& indexNumber);
    ErrorCode removePerson(const std::string& pesel);

    void printPerson(const std::unique_ptr<Person>& person);
    void printAll();

    void searchStudentByLastName(const std::string& lastName);  // zrobic referencje?
    // dorobic dla malych liter??
    void searchStudentByPesel(const std::string& pesel);

    void sortByLastName();
    void sortByPesel();
    void sortBySalary();

    void changeSalary(const std::string& pesel);

    bool isPeselValid(const std::string& pesel); //reference?

    bool saveFile(const std::string& fileName); // const??
    bool openFile(const std::string& fileName);


    static std::string stringToLower(const std::string& str);

    bool existsInDataBase(const size_t& indexNumber);
    bool existsInDataBase(const std::string& pesel);

private:
    void printHeader();
    std::string encodeSex(const Sex& sex) const;
    std::string encodeType(const Person::PersonType& type) const;
    void writeStringToFile(const std::string& str, std::ofstream& file);
    void readStringFromFile(std::string& str, std::ifstream& file);

    std::vector<std::unique_ptr<Person>> people_;

};
