#include "data_generator.hpp"
#include <random>
// #include <string>

size_t DataGenerator::randomNumber(const size_t& rangeMin, const size_t& rangeMax) const {
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<> distribution(rangeMin, rangeMax);
    return distribution(randomGenerator);
}

std::string DataGenerator::randomFirstName() const {
    return firstNames_[randomNumber(0, firstNames_.size() - 1)];
}

std::string DataGenerator::randomLastName() const {
    return lastNames_[randomNumber(0, lastNames_.size() - 1)];
}

std::string DataGenerator::randomPeselPrototype() const {
    return std::to_string(randomNumber(0, 99))
         + std::to_string(randomNumber(0, 12))
         + std::to_string(randomNumber(0, 31));
}

std::string DataGenerator::randomCity() const {
    return cities_[randomNumber(0, cities_.size() - 1)];
}

std::string DataGenerator::randomStreetAndNumber() const {
    return streets_[randomNumber(0, streets_.size() - 1)] + ' ' + std::to_string(randomNumber(1, 999));
}

std::string DataGenerator::randomPostalCode() const {
    return std::to_string(randomNumber(0, 99)) + '-' + std::to_string(randomNumber(0,999));
}

Sex DataGenerator::randomSex() const {
    return static_cast<Sex>(randomNumber(0, 2));
}

Person::PersonType DataGenerator::randomPersonType() const {
    return static_cast<Person::PersonType>(randomNumber(0, 1));
}