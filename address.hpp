#pragma once
#include <string>

class Address {
public:
    Address(std::string postalCode, std::string city, std::string streetAndNumber)
    : postalCode_{postalCode}
    , city_{city}
    , streetAndNumber_{streetAndNumber}
    {}

    std::string getAddress() const {
        return postalCode_ + ' ' + city_ + " ul." + streetAndNumber_;
    }

    std::string getPostalCode() const {
        return postalCode_;
    }

    std::string getCity() const {
        return city_;
    }

    std::string getStreetAndNumber() const {
        return streetAndNumber_;
    }

private:
    std::string postalCode_;
    std::string city_;
    std::string streetAndNumber_;
};