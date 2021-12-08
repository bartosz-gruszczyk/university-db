#pragma once
#include "address.hpp"
#include <iostream> // or string

enum class Sex {
    Female, Male, Other
};

class Person {
public:
    enum class PersonType {
        Student, Employee
    };

    Person(PersonType type, std::string firstName, std::string lastName, std::string pesel, Address address, Sex sex); 
    
    virtual ~Person();

    PersonType getType() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPesel() const;
    std::string getAddress() const;
    // maybe there is a better solution for addres...
    std::string getPostalCode() const;
    std::string getCity() const;
    std::string getStreetAndNumber() const;
    Sex getSex() const;

    virtual size_t getIndexNumber() const = 0;
    virtual size_t getSalary() const = 0;
    virtual void setSalary(const size_t& newSalary) = 0;
    // virtual size_t getIndexNumber() const;
    // virtual size_t getSalary() const;

private:
    PersonType type_;
    std::string firstName_;
    std::string lastName_;
    std::string pesel_;
    Address address_;
    Sex sex_;
};