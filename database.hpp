    // Przechowywanie rekordów studentów o strukturze: Imię,,
    //  nazwisko, adres, nr indeksu, PESEL, płeć
    // Dodawanie nowych studentów
    // Wyświetlanie całej bazy danych
    // Wyszukiwanie po nazwisku
    // Wyszukiwanie po numerze PESEL
    // Sortowanie po numerze PESEL
    // Sortowanie po nazwisku
    // Usuwanie po numerze indeksu

#pragma once
#include <memory>
#include <vector>
#include "student.hpp"

class DataBase {
public:

    void addStudent(std::string firstName, std::string lastName, size_t indexNumber, std::string pesel, Address address, Sex sex);
    void removeStudent(const size_t& indexNumber);
    void printStudent(const std::unique_ptr<Student>& student);
    void printAll();

    int columnWidth = 16;   //zrobic const......!!!
private:
    void printHeader();
    std::string encodeSex(const Sex& sex) const;

    std::vector<std::unique_ptr<Student>> students_;

};