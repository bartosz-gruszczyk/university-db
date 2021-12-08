#pragma once
#include "address.hpp"
#include "person.hpp"
#include <string>

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
    ~Student();

    size_t getIndexNumber() const override;
    size_t getSalary() const override;
    void setSalary(const size_t&) override;

private:
    size_t indexNumber_;

};