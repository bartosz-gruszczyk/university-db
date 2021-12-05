#include "student.hpp"

// Student();
Student::Student(std::string firstName,
                 std::string lastName,
                 std::string pesel,
                 Address address,
                 Sex sex,
                 size_t indexNumber) 
    : Person(PersonType::Student, firstName, lastName, pesel, address, sex)
    , indexNumber_{indexNumber}
    {}

Student::~Student() {

}

size_t Student::getIndexNumber() const {
    return indexNumber_;
}

size_t Student::getSalary() const {
    return 0;
}

void Student::setSalary(size_t newSalary) { // zrobic const!
    // do nothing... null object pattern
}