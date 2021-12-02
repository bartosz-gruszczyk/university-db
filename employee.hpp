#pragma once
#include "address.hpp"
#include "person.hpp"

class Employee : public Person {
public:
    Employee(std::string firstName,
            std::string lastName,
            std::string pesel,
            Address address,
            Sex sex,
            size_t salary);

    size_t getIndexNumber() const override;
    size_t getSalary() const override;
    
private:
    size_t salary_;

};