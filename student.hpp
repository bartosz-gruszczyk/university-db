#pragma once
#include "address.hpp"
#include <cstring>
#include <string>

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
    // maybe there is a better solution for addres...
    std::string getPostalCode() const;
    std::string getCity() const;
    std::string getStreetAndNumber() const;
    Sex getSex() const;

private:
    std::string firstName_;
    std::string lastName_;
    size_t indexNumber_;
    std::string pesel_;
    Address address_;
    Sex sex_;
    
};

// class StudentData { 
// public:
//     void packData(const Student& student);
    
//     Student unpackData() const;

//     char firstName_[16];
//     char lastName_[16];
//     size_t indexNumber_;
//     char pesel_[12]; // uwaga na znak konca wyrazu
//     char postalCode_[7];
//     char city_[16];
//     char streetAndNumber_[32];
//     Sex sex_;
// private:
    
// };