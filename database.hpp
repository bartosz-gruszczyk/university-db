#pragma once
#include <memory>
#include <vector>
#include "data_generator.hpp"
#include "employee.hpp"
#include "errors.hpp"
#include "person.hpp"
#include "student.hpp"

class DataBase {
public:
    constexpr static const size_t minIndexNumber = 1;
    constexpr static const size_t maxIndexNumber = 999999;
    const size_t minSalary = 3000;
    const size_t maxSalary = 26000;

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
    void generatePeople(const size_t& amount); // :)
    int calculatePeselControlDigit(const std::string& pesel) const;
    bool isPeselValid(const std::string& pesel);
    ErrorCode saveFile(const std::string& fileName);
    ErrorCode openFile(const std::string& fileName);
    void clearAll();
    static std::string stringToLower(const std::string& str);
    std::vector<std::shared_ptr<Person>>& data();

private:
    bool existsInDataBase(const size_t& indexNumber) const;
    bool existsInDataBase(const std::string& pesel) const;
    bool isValidIndexNumber(const size_t& indexNumber) const;
    void writeStringToFile(const std::string& str, std::ofstream& file);
    void readStringFromFile(std::string& str, std::ifstream& file);
    std::vector<std::shared_ptr<Person>> people_;
    DataGenerator dataGen_;

};
