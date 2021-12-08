#include "data_generator.hpp"
#include <random>

size_t DataGenerator::randomNumber(const size_t& rangeMin, const size_t& rangeMax) const {
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<> distribution(rangeMin, rangeMax);
    return distribution(randomGenerator);
}

std::string DataGenerator::randomCity() const {
    return cities_[randomNumber(0, cities_.size() - 1)];
}