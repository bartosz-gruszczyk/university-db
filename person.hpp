#pragma once
#include <string>
#include "address.hpp"

enum class Sex {
    Female, Male, Other
};

class Person {
public:
    enum class PersonType {
        Student, Employee
    };

    Person(PersonType type,
           std::string firstName,
           std::string lastName,
           std::string pesel,
           Address address,
           Sex sex);
    
    virtual ~Person();

    PersonType getType() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPesel() const;
    std::string getAddress() const;
    std::string getPostalCode() const;
    std::string getCity() const;
    std::string getStreetAndNumber() const;
    Sex getSex() const;
    virtual size_t getIndexNumber() const = 0;
    virtual size_t getSalary() const = 0;
    virtual void setSalary(const size_t& newSalary) = 0;
    const Address& address();

private:
    PersonType type_;
    std::string firstName_;
    std::string lastName_;
    std::string pesel_;
    Address address_;
    Sex sex_;
};
