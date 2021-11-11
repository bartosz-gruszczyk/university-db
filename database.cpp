#include "database.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <memory>
#include <numeric>

void DataBase::printHeader(){
    std::cout << "vector size: " << students_.size() << '\n';
    std::cout.setf(std::ios::left);
    std::cout << std::setw(columnWidth) << "first name:"
              << std::setw(columnWidth) << "last name:"
              << std::setw(columnWidth) << "index number:"
              << std::setw(48) << "address:"
              << std::setw(columnWidth) << "PESEL:"
              << std::setw(columnWidth) << "sex:"
              << '\n';
}

void DataBase::printStudent(const std::unique_ptr<Student>& student) {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(columnWidth) << student->getFirstName()  // zrobic constexpr
                  << std::setw(columnWidth) << student->getLastName()
                  << std::setw(columnWidth) << student->getIndexNumber()
                  << std::setw(48) << student->getAddress()   // zrobic const wartosc kolumny address
                  << std::setw(columnWidth) << student->getPesel()
                  << std::setw(columnWidth) << encodeSex(student->getSex())
                  << '\n';    
}

void DataBase::printAll() {
    printHeader();
    for (auto it = students_.cbegin(); it != students_.cend(); ++it) {
        printStudent(*it);
    }
}

std::string DataBase::encodeSex(const Sex& sex) const {
    return sex == Sex::Male ? "Male" : sex == Sex::Female ? "Female" : "Other";
}

void DataBase::addStudent(std::string firstName,
                          std::string lastName,
                          size_t indexNumber,
                          std::string pesel,
                          Address address,
                          Sex sex) {
    students_.push_back(std::make_unique<Student>(Student(firstName, lastName, indexNumber, pesel, address, sex)));
}

void DataBase::removeStudent(const size_t& indexNumber) {
    // sprawdzic czy nie ma wyciekow
    // czy warto robic remove/erase?
    // error - invalid index??
    std::erase_if(students_, [indexNumber](const std::unique_ptr<Student>& ptr){
        return ptr->getIndexNumber() == indexNumber;
    });
}

void DataBase::searchStudentByLastName(const std::string lastName) {

    auto it = students_.begin();
    while (it != students_.end()) {
        it = std::find_if(it, students_.end(), [lastName](const std::unique_ptr<Student>& ptr){
            return ptr->getLastName().find(lastName) != std::string::npos;
        });
        // **it;
        if (it != students_.end()) {
            // std::cout << (*it)->getLastName() << "  \n";
            printStudent(*it);
            ++it;
        }
    }
} 

void DataBase::sortByLastName() { // reference to string?

    std::sort(students_.begin(), students_.end(), [](std::unique_ptr<Student>& a, std::unique_ptr<Student>& b){
        std::string first = a->getLastName();
        std::string second = b->getLastName();
        // std::tolower(first);
        // std::tolower(second);
        return (first <=> second) < 0;
    });

}

bool DataBase::validatePESEL(const std::string pesel) {
    // const short peselLenght = 11;
    // const std::string weight = "1379137913"
    std::array<char, 10> weights {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
    if (pesel.size() == 11) {
        std::transform(weights.begin(),
                       weights.end(),
                       pesel.begin(),
                       weights.begin(),
                       [](const char& weight, const char& digit){
                           return weight * (digit - '0');
                       });
        int modulo = std::reduce(weights.cbegin(), weights.cend(), 0) % 10;
        if (modulo == 0) {
            return pesel.ends_with('0');
        }
        return pesel.ends_with(10 - modulo + '0');
    }
    return false;
}