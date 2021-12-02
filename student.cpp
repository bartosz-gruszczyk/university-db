#include "student.hpp"
#include <iomanip>
#include <iostream>

// Student();
Student::Student(std::string firstName,
                 std::string lastName,
                 size_t indexNumber,
                 std::string pesel,
                 Address address,
                 Sex sex) 
    : Person(PersonType::Student, firstName, lastName, pesel, address, sex)
    , indexNumber_{indexNumber}
    {}


size_t Student::getIndexNumber() const {
    return indexNumber_;
}

size_t Student::getSalary() const {
    return 0;
}