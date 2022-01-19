#include "student.hpp"

Student::Student(std::string firstName,
                 std::string lastName,
                 std::string pesel,
                 Address address,
                 Sex sex,
                 size_t indexNumber) 
    : Person(PersonType::Student, firstName, lastName, pesel, address, sex)
    , indexNumber_{indexNumber}
    {}

Student::~Student() {}

size_t Student::getIndexNumber() const {
    return indexNumber_;
}

size_t Student::getSalary() const {
    return 0;
}

void Student::setSalary(const size_t&) {
    // do nothing... null object pattern
}