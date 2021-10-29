#include "database.hpp"
#include <iostream>
#include <iomanip>
#include <memory>

void DataBase::printHeader(){
    std::cout.setf(std::ios::left);
    std::cout << std::setw(columnWidth) << "first name:"
              << std::setw(columnWidth) << "last name:"
              << std::setw(columnWidth) << "index number:"
              << std::setw(32) << "address:"
              << std::setw(columnWidth) << "sex:"
              << '\n';
}

void DataBase::printAll() {
    printHeader();
    for (auto it = students_.cbegin(); it != students_.cend(); ++it) {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(columnWidth) << (**it).getFirstName()  // zrobic constexpr
                  << std::setw(columnWidth) << (**it).getLastName()
                  << std::setw(columnWidth) << (**it).getIndexNumber()
                  << std::setw(32) << (**it).getAddress()
                  << std::setw(columnWidth) << (**it).getPesel()
                  << '\n';
    }

}

void DataBase::addStudent(std::string firstName,
                          std::string lastName,
                          size_t indexNumber,
                          std::string pesel,
                          Address address,
                          Sex sex) {
    students_.push_back(std::make_unique<Student>(Student(firstName, lastName, indexNumber, pesel, address, sex)));
}

