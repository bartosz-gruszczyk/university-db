#pragma once
#include <string>
#include "address.hpp"

enum class Sex {
    Female, Male, Other
};


class Student {
public:

private:
    std::string firstName_;
    std::string lastName_;
    size_t indexNumber_;
    std::string pesel_;

    Sex sex_;
    
};