#pragma once
#include <string>
#include "address.hpp"

enum class Sex {
    Female, Male, Other
};


class Student {
public:
    // Student();
    Student(std::string, std::string, size_t, std::string, Address, Sex);
    // co z destruktorem zwalniającym address_ ???

    void print();

    std::string getFirstName() const;
    std::string getLastName() const;
    size_t getIndexNumber() const;
    std::string getPesel() const;
    std::string getAddress() const;
    Sex getSex() const;

private:
    std::string firstName_;
    std::string lastName_;
    size_t indexNumber_;
    std::string pesel_;
    Address address_;
    Sex sex_;
    
};