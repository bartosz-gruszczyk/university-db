#pragma once
#include "person.hpp"

class Student : public Person {
public:
    Student(std::string firstName,
            std::string lastName,
            std::string pesel,
            Address address,
            Sex sex,
            size_t indexNumber);

    ~Student();

    size_t getIndexNumber() const override;
    size_t getSalary() const override;
    void setSalary(const size_t&) override;

private:
    size_t indexNumber_;

};
