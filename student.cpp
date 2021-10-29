#include "student.hpp"
#include <iomanip>
#include <iostream>

// Student();
Student::Student(std::string firstName, std::string lastName, size_t indexNumber, std::string pesel, Address address, Sex sex) 
    : firstName_{firstName}
    , lastName_{lastName}
    , indexNumber_{indexNumber}
    , pesel_{pesel}
    , address_{address}
    , sex_{sex}
    {}

void Student::print() {
    // std::cout.width(16);
    int columnWidth = 12;
    std::cout.setf(std::ios::left);
    std::cout << std::setw(columnWidth) << firstName_  // zrobic constexpr
              << std::setw(columnWidth) << lastName_ 
              << std::setw(32) << address_.getAddress()
              << indexNumber_ << ' '
              << pesel_ << '\n';
}

std::string Student::getFirstName() const {
    return firstName_;
}

std::string Student::getLastName() const {
    return lastName_;
}

size_t Student::getIndexNumber() const {
    return indexNumber_;
}

std::string Student::getPesel() const {
    return pesel_;
}

std::string Student::getAddress() const {
    return address_.getAddress(); // hmmmm
}

Sex Student::getSex() const {
    return sex_;
}
