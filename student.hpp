#pragma once
#include <string>
#include "address.hpp"
#include <cstring>

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

class StudentData {
public:
    void packData(const Student& student) {
        // std::strncpy(name_, name.data(), 10);
    }
    
    Student unpackData() const {

    }

private:
    char firstName_[16];
    char lastName_[16];
    size_t indexNumber_;
    char pesel_[11];
    char postalCode_[6];
    char city_[16];
    char streetAndNumber[32];
    Sex sex_;
    
};