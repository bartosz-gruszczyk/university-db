#pragma once
#include "address.hpp"
#include "person.hpp"
#include <cstring> // wywalic??
#include <string>

// enum class Sex {
//     Female, Male, Other
// };

class Student : public Person {
public:
    // Student();
    Student(std::string firstName,
            std::string lastName,
            std::string pesel,
            Address address,
            Sex sex,
            size_t indexNumber);

    // co z destruktorem zwalniającym address_ ???

    size_t getIndexNumber() const override;
    size_t getSalary() const override;

    // std::string getFirstName() const;
    // std::string getLastName() const;
    // std::string getPesel() const;
    // std::string getAddress() const;
    // // maybe there is a better solution for addres...
    // std::string getPostalCode() const;
    // std::string getCity() const;
    // std::string getStreetAndNumber() const;
    // Sex getSex() const;

private:
    // std::string firstName_;
    // std::string lastName_;
    size_t indexNumber_;
    // std::string pesel_;
    // Address address_;
    // Sex sex_;
    
};