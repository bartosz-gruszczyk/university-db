#include "database.hpp"
#include "data_generator.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <numeric>

const size_t DataBase::minIndexNumber = 1;
const size_t DataBase::maxIndexNumber = 999999;

ErrorCode DataBase::addStudent(const std::string& firstName,
                               const std::string& lastName,
                               const std::string& pesel,
                               const Address& address,
                               const Sex& sex,
                               const size_t& indexNumber) {
    if (!isPeselValid(pesel)) {
        return ErrorCode::InvalidPesel;
    }
    if (existsInDataBase(pesel)) {
        return ErrorCode::PeselAlreadyExists;
    }
    if (!isValidIndexNumber(indexNumber)) {
        return ErrorCode::InvalidIndexNumber;
    }
    if (existsInDataBase(indexNumber)) {
        return ErrorCode::IndexNumberAlreadyExists;
    }
    Student tempStudent(firstName, lastName, pesel, address, sex, indexNumber);
    people_.emplace_back(std::make_shared<Student>(tempStudent));
    return ErrorCode::Ok;
}

ErrorCode DataBase::addEmployee(const std::string& firstName,
                                const std::string& lastName,
                                const std::string& pesel,
                                const Address& address,
                                const Sex& sex,
                                const size_t& salary) {
    if (!isPeselValid(pesel)) {
        return ErrorCode::InvalidPesel;
    }
    if (existsInDataBase(pesel)) {
        return ErrorCode::PeselAlreadyExists;
    }
    Employee tempEmployee(firstName, lastName, pesel, address, sex, salary);
    people_.emplace_back(std::make_shared<Employee>(tempEmployee));
    return ErrorCode::Ok;
}

ErrorCode DataBase::removeStudent(const size_t& indexNumber) {
    // sprawdzic czy nie ma wyciekow
    // czy warto robic remove/erase?
    if (!isValidIndexNumber(indexNumber)) {
        return ErrorCode::InvalidIndexNumber;
    }
    int numberOfErasedElements = std::erase_if(people_, [indexNumber](const std::shared_ptr<Person>& ptr){
        return ptr->getIndexNumber() == indexNumber;
    });
    if (numberOfErasedElements == 0) {
        return ErrorCode::IndexNumberNotFound;
    }
    return ErrorCode::Ok;
}

ErrorCode DataBase::removePerson(const std::string& pesel) {
    if (!isPeselValid(pesel)) {
        return ErrorCode::InvalidPesel;
    }
    int numberOfErasedElements = std::erase_if(people_, [pesel](const std::shared_ptr<Person>& ptr){
        return ptr->getPesel() == pesel;
    });
    if (numberOfErasedElements == 0) {
        return ErrorCode::PeselNotFound;
    }
    return ErrorCode::Ok;
}


ErrorCode DataBase::searchStudentByLastName(const std::string& lastName,
                                       std::vector<std::shared_ptr<Person>>& searchResults) {
    auto findLastName = [lastName](const std::shared_ptr<Person>& ptr){
            std::string lastNameToSearch = DataBase::stringToLower(lastName);
            std::string currentLastName = DataBase::stringToLower(ptr->getLastName());
            // return ptr->getLastName().find(lastName) != std::string::npos;
            return currentLastName.find(lastNameToSearch) != std::string::npos;
    };
    auto it = std::find_if(people_.cbegin(), people_.cend(), findLastName);
    if (it == people_.cend()) {
        return ErrorCode::LastNameNotFound;  // moze da sie jakos lepiej z ifami?
    }
    while (it != people_.end()) {
        searchResults.emplace_back(*it++);
        it = std::find_if(it, people_.cend(), findLastName);
    }
    return ErrorCode::Ok;
} 

ErrorCode DataBase::searchStudentByPesel(const std::string& pesel,
                                         std::vector<std::shared_ptr<Person>>& searchResults) {
    auto findPESEL = [pesel](const std::shared_ptr<Person>& person) {
        return person->getPesel().starts_with(pesel);
    };
    auto it = std::find_if(people_.cbegin(), people_.cend(), findPESEL);
    if (it == people_.cend()) {
        return ErrorCode::PeselNotFound;  // moze da sie jakos lepiej z ifami?
    }
    while (it != people_.end()) {
        searchResults.emplace_back(*it++);
        it = std::find_if(it, people_.cend(), findPESEL);
    }
    return ErrorCode::Ok;
}

std::string DataBase::stringToLower(const std::string& str) { // moze wywalic do innego cpp ?
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });
    return lower;
}

void DataBase::sortByLastName() { // reference to string?
    std::sort(people_.begin(), people_.end(), [](std::shared_ptr<Person>& a, std::shared_ptr<Person>& b){
        // std::string first = a->getLastName();
        // std::string second = b->getLastName();
        // std::tolower(first);
        // std::tolower(second);
        // return (first <=> second) < 0;
        return (a->getLastName() <=> b->getLastName()) < 0;
    });
}

void DataBase::sortByPesel() {
    std::sort(people_.begin(), people_.end(), [](std::shared_ptr<Person>& a, std::shared_ptr<Person>& b){
        return (a->getPesel() <=> b->getPesel()) < 0;
    });
}

void DataBase::sortBySalary() {
    std::sort(people_.begin(), people_.end(), [](std::shared_ptr<Person>& a, std::shared_ptr<Person>& b){
        return a->getSalary() > b->getSalary();
    });
}

ErrorCode DataBase::changeSalary(const std::string& pesel, const size_t& newSalary) {
    auto it = std::find_if(people_.begin(), people_.end(), [pesel](const std::shared_ptr<Person>& ptr){
        return ptr->getPesel() == pesel;
    });
    if (it != people_.end()) {
        if ((*it)->getType() == Person::PersonType::Student) {
            return ErrorCode::NotEmployee;
        }
        if (newSalary < minSalary || newSalary > maxSalary) {
            return ErrorCode::InvalidSalary;
        }
        (*it)->setSalary(newSalary);
        return ErrorCode::Ok;
    } 
    return ErrorCode::PeselNotFound;
}

void DataBase::generatePeople(const size_t& amount) {
    Person::PersonType type = dataGen_.randomPersonType();
    std::string firstName = dataGen_.randomFirstName();
    std::string lastName = dataGen_.randomLastName();
    std::string pesel = dataGen_.randomPeselPrototype();
    pesel += calculatePeselControlDigit(pesel);

    Address address(dataGen_.randomPostalCode(), dataGen_.randomCity(), dataGen_.randomStreetAndNumber());
    Sex sex = dataGen_.randomSex();
    std::cout << "generate: " << firstName << "  " << lastName << "  " << pesel << "  " <<  (sex == Sex::Male ? "Male" : sex == Sex::Female ? "Female" : "Other" ) << "  " << "\n";
    if (type == Person::PersonType::Student) {
        addStudent(firstName, lastName, pesel, address, sex, dataGen_.randomNumber(minIndexNumber, maxIndexNumber));
    } else {
        addEmployee(firstName, lastName, pesel, address, sex, dataGen_.randomNumber(minSalary, maxSalary));
    }
}


int DataBase::calculatePeselControlDigit(const std::string& pesel) const {
    std::array<char, 10> weights {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
    if (pesel.size() >= 10) { // moze wyrzucic pozniej...?
        std::transform(weights.begin(),
                       weights.end(),
                       pesel.begin(),
                       weights.begin(),
                       [](const char& weight, const char& digit){
                           return weight * (digit - '0');
                       });
        int modulo = std::reduce(weights.cbegin(), weights.cend(), 0) % 10;
        if (modulo == 0) {
            return 0;
        }
        return 10 - modulo;
    }
    return -1; // when string size is inappropiate
}

bool DataBase::isPeselValid(const std::string& pesel) {
    if (pesel.size() == 11) {
        return pesel.ends_with(calculatePeselControlDigit(pesel) + '0');
    }
    return false;
}

void DataBase::writeStringToFile(const std::string& str, std::ofstream& file) {
    // if (file.is_open()) { // moze nie bedzie potrzebne bo sprawdzane nadrzednie
    char size = static_cast<char>(str.size());
    file.write(&size, sizeof(char));
    file.write(&str[0], size);
}

void DataBase::readStringFromFile(std::string& str, std::ifstream& file) {
    char size;  // moze jednak zmienic na unsigned short?
    file.read(&size, sizeof(char)); 
    str.resize(size);
    file.read(&str[0], size);
}

bool DataBase::saveFile(const std::string& fileName) {
    std::ofstream file(fileName, file.out | file.binary);
    if (file.is_open()) {   // file.good() ????
        for (size_t i = 0; i < people_.size(); ++i) {
            writeStringToFile(people_[i]->getFirstName(), file);
            writeStringToFile(people_[i]->getLastName(), file);
            size_t indexNumber = people_[i]->getIndexNumber();
            file.write(reinterpret_cast<char*>(&indexNumber), sizeof(size_t));
            writeStringToFile(people_[i]->getPesel(), file);
            writeStringToFile(people_[i]->getPostalCode(), file);
            writeStringToFile(people_[i]->getCity(), file);
            writeStringToFile(people_[i]->getStreetAndNumber(), file);
            Sex sex = people_[i]->getSex();
            file.write(reinterpret_cast<char*>(&sex), sizeof(Sex));
        }
        return true;
    }
    return false;
}

bool DataBase::openFile(const std::string& fileName) {
    std::ifstream file(fileName, file.in | file.binary);
    if (file.is_open()) {
        people_.clear();
        while (!file.eof()) {
            std::string firstName;
            std::string lastName;
            size_t indexNumber;
            std::string pesel;
            std::string postalCode;
            std::string city;
            std::string streetAndNumber;
            Sex sex;
            readStringFromFile(firstName, file);
            readStringFromFile(lastName, file);
            file.read(reinterpret_cast<char*>(&indexNumber), sizeof(size_t));
            readStringFromFile(pesel, file);
            readStringFromFile(postalCode, file);
            readStringFromFile(city, file);
            readStringFromFile(streetAndNumber, file);
            file.read(reinterpret_cast<char*>(&sex), sizeof(Sex));
            Student tempStudent(firstName,
                                lastName,
                                pesel,
                                Address(postalCode, city, streetAndNumber),
                                sex,
                                indexNumber);
            people_.emplace_back(std::make_shared<Student>(tempStudent));
            // people_.emplace_back(std::make_shared<Person>(std::move(tempStudent)));
            file.peek();
        }
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Person>>& DataBase::data() {
    return people_;
}

bool DataBase::existsInDataBase(const size_t& indexNumber) const {
    auto it = std::find_if(people_.cbegin(),
                           people_.cend(),
                           [indexNumber](const std::shared_ptr<Person>& person){
                               return indexNumber == person->getIndexNumber();
                           });
    return it != people_.cend();
}

bool DataBase::existsInDataBase(const std::string& pesel) const {
    auto it = std::find_if(people_.cbegin(),
                           people_.cend(),
                           [pesel](const std::shared_ptr<Person>& person){
                               return pesel == person->getPesel();
                           });
    return it != people_.cend();

}

bool DataBase::isValidIndexNumber(const size_t& indexNumber) const {
    return indexNumber >= 1 && indexNumber <= maxIndexNumber;
}
