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
#include "student.hpp"

class DataBase {
public:

    void addStudent(std::string firstName, std::string lastName, size_t indexNumber, std::string pesel, Address address, Sex sex);
    void removeStudent(const size_t& indexNumber);
    void printStudent(const std::unique_ptr<Student>& student);
    void printAll();

    void searchStudentByLastName(const std::string& lastName);  // zrobic referencje?
    // dorobic dla malych liter??
    void searchStudentByPesel(const std::string& pesel);

    void sortByLastName();
    void sortByPesel();

    bool validatePesel(const std::string pesel); //reference?

    bool saveFile(const std::string& fileName); // const??
    bool openFile(const std::string& fileName);

    int columnWidth = 16;   //zrobic const......!!!
    static std::string stringToLower(const std::string& str);

    bool existsInDataBase(const size_t& indexNumber);
    bool existsInDataBase(const std::string& pesel);

private:
    void printHeader();
    std::string encodeSex(const Sex& sex) const;
    void writeStringToFile(const std::string& str, std::ofstream& file);
    void readStringFromFile(std::string& str, std::ifstream& file);

    std::vector<std::unique_ptr<Student>> students_;

};