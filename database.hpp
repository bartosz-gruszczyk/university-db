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
    static const size_t maxIndexNumber = 999999;   // co const a co constexpr??
    size_t minSalary = 3000;
    size_t maxSalary = 26000;

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
    ErrorCode searchStudentByLastName(const std::string& lastName,
                                      std::vector<std::shared_ptr<Person>>& searchResults);
    ErrorCode searchStudentByPesel(const std::string& pesel,
                                   std::vector<std::shared_ptr<Person>>& searchResults);
    void sortByLastName();
    void sortByPesel();
    void sortBySalary();

    ErrorCode changeSalary(const std::string& pesel, const size_t& newSalary);

    bool isPeselValid(const std::string& pesel); //reference?

    bool saveFile(const std::string& fileName); // const??
    bool openFile(const std::string& fileName);


    static std::string stringToLower(const std::string& str);


    std::vector<std::shared_ptr<Person>>& data();

private:
    bool existsInDataBase(const size_t& indexNumber) const;
    bool existsInDataBase(const std::string& pesel) const;
    bool isValidIndexNumber(const size_t& indexNumber) const;
    void writeStringToFile(const std::string& str, std::ofstream& file);
    void readStringFromFile(std::string& str, std::ifstream& file);

    std::vector<std::shared_ptr<Person>> people_;

};
