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
              << std::setw(42) << "address:"
              << std::setw(columnWidth) << "PESEL:"
              << std::setw(columnWidth) << "sex:"
              << '\n';
}

void DataBase::printStudent(const std::unique_ptr<Student>& student) {
        std::cout.setf(std::ios::left);
        std::cout << std::setw(columnWidth) << student->getFirstName()  // zrobic constexpr
                  << std::setw(columnWidth) << student->getLastName()
                  << std::setw(columnWidth) << student->getIndexNumber()
                  << std::setw(42) << student->getAddress()   // zrobic const wartosc kolumny address
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

void DataBase::searchStudentByLastName(const std::string& lastName) {
    // --- first version ---
    // auto it = students_.begin();
    // while (it != students_.end()) {
    //     it = std::find_if(it, students_.end(), [lastName](const std::unique_ptr<Student>& ptr){
    //         return ptr->getLastName().find(lastName) != std::string::npos;
    //     });
    //     // **it;
    //     if (it != students_.end()) {
    //         // std::cout << (*it)->getLastName() << "  \n";
    //         printStudent(*it);
    //         ++it;
    //     }
    // }

    auto findLastName = [lastName](const std::unique_ptr<Student>& ptr){
            std::string lastNameToSearch = DataBase::stringToLower(lastName);
            std::string currentLastName = DataBase::stringToLower(ptr->getLastName());
            // return ptr->getLastName().find(lastName) != std::string::npos;
            return currentLastName.find(lastNameToSearch) != std::string::npos;
    };
    auto it = std::find_if(students_.cbegin(), students_.cend(), findLastName);
    while (it != students_.end()) {
        printStudent(*it++);
        // ++it;
        it = std::find_if(it, students_.cend(), findLastName);
    }
} 

void DataBase::searchStudentByPESEL(const std::string& pesel) {
    auto findPESEL = [pesel](const std::unique_ptr<Student>& student) {  // name of ptr??
        return student->getPesel().starts_with(pesel);
    };
    auto it = std::find_if(students_.cbegin(), students_.cend(), findPESEL);
    while (it != students_.end()) {
        printStudent(*it++);
        it = std::find_if(it, students_.cend(), findPESEL);
    }

}


std::string DataBase::stringToLower(const std::string& str) { // moze wywalic do innego cpp ?
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });
    return lower;
}

void DataBase::sortByLastName() { // reference to string?
    std::sort(students_.begin(), students_.end(), [](std::unique_ptr<Student>& a, std::unique_ptr<Student>& b){
        // std::string first = a->getLastName();
        // std::string second = b->getLastName();
        // std::tolower(first);
        // std::tolower(second);
        // return (first <=> second) < 0;
        return (a->getLastName() <=> b->getLastName()) < 0;
    });
}

void DataBase::sortByPESEL() {
    std::sort(students_.begin(), students_.end(), [](std::unique_ptr<Student>& a, std::unique_ptr<Student>& b){
        return (a->getPesel() <=> b->getPesel()) < 0;
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