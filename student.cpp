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

void Student::print() { // to juz niepotrzebne
    // std::cout.width(16);
    int columnWidth = 12; // porzadek z wymiarem kolumn
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
// maybe there is better solution for address
std::string Student::getPostalCode() const {
    return address_.getPostalCode();
}

std::string Student::getCity() const {
    return address_.getCity();
}

std::string Student::getStreetAndNumber() const {
    return address_.getStreetAndNumber();
}


// void StudentData::packData(const Student& student) {
//     // std::strncpy(name_, name.data(), 10);
//     std::strncpy(firstName_, student.getFirstName().data(), 16);
//     std::strncpy(lastName_, student.getLastName().data(), 16);
//     indexNumber_ = student.getIndexNumber();
//     std::strncpy(pesel_, student.getPesel().data(), 12);
//     std::strncpy(postalCode_, (student.getPostalCode()).data(), 7);
//     std::strncpy(city_, student.getCity().data(), 16);
//     std::strncpy(streetAndNumber_, student.getStreetAndNumber().data(), 32);
//     sex_ = student.getSex();
//     // std::cout << "---  " << postalCode_ << '_' << pesel_ << " ---\n";
// }

// Student StudentData::unpackData() const {
//     return Student(firstName_, lastName_, indexNumber_, pesel_, Address(postalCode_, city_, streetAndNumber_), sex_);
// }