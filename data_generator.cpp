#include "data_generator.hpp"
#include "database.hpp" /// podejrzane... static const
#include <random>
// #include <string>

size_t DataGenerator::randomNumber(const size_t& rangeMin, const size_t& rangeMax) const {
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<> distribution(rangeMin, rangeMax);
    return distribution(randomGenerator);
}

std::string DataGenerator::randomFirstName(const Sex& sex) const {  // refactor this??
    if (sex == Sex::Male) {
        return maleFirstNames_[randomNumber(0, maleFirstNames_.size() - 1)];
    }
    if (sex == Sex::Female) {
        return femaleFirstNames_[randomNumber(0, femaleFirstNames_.size() - 1)];
    }
    size_t tempRandomNumber = randomNumber(0, maleFirstNames_.size() + femaleFirstNames_.size() - 1);
    if (tempRandomNumber < maleFirstNames_.size()) {
        return maleFirstNames_[tempRandomNumber];
    }
    return femaleFirstNames_[tempRandomNumber - maleFirstNames_.size()];
}

std::string DataGenerator::randomLastName() const {
    return lastNames_[randomNumber(0, lastNames_.size() - 1)];
}

std::string DataGenerator::randomPeselPrototype() const {
    return randomNumberWithZeros(1, 99)
         + randomNumberWithZeros(1, 12)
         + randomNumberWithZeros(1, 31)
         + randomNumberWithZeros(1, 9999);
}

std::string DataGenerator::randomCity() const {
    return cities_[randomNumber(0, cities_.size() - 1)];
}

std::string DataGenerator::randomStreetAndNumber() const {
    return streets_[randomNumber(0, streets_.size() - 1)] + ' ' + std::to_string(randomNumber(1, 999));
}

std::string DataGenerator::randomPostalCode() const {
    return randomNumberWithZeros(1, 99) + '-' + randomNumberWithZeros(1, 999);
}

Sex DataGenerator::randomSex() const {
    return static_cast<Sex>(randomNumber(0, 2));
}

Person::PersonType DataGenerator::randomPersonType() const {
    return static_cast<Person::PersonType>(randomNumber(0, 1));
}

std::string DataGenerator::randomNumberWithZeros(const int& rangeMin, int rangeMax) const {
        size_t randNum = randomNumber(rangeMin, rangeMax);
        std::string zeros{""};
        auto temp = randNum;
        while (rangeMax / 10 != 0) {
            rangeMax /= 10;
            temp /=10;
            if (temp == 0) {
                zeros += '0';
            }
        }
        return zeros + std::to_string(randNum);
}
