#include "address.hpp"

Address::Address(std::string postalCode, std::string city, std::string streetAndNumber)
    : postalCode_{postalCode}
    , city_{city}
    , streetAndNumber_{streetAndNumber}
    {}

std::string Address::getAddress() const {
    return postalCode_ + ' ' + city_ + " ul." + streetAndNumber_;
}

std::string Address::getPostalCode() const {
    return postalCode_;
}

std::string Address::getCity() const {
    return city_;
}

std::string Address::getStreetAndNumber() const {
    return streetAndNumber_;
}

bool Address::operator==(const Address& other) const {
    return postalCode_ == other.getPostalCode()
        && city_ == other.getCity()
        && streetAndNumber_ == other.getStreetAndNumber();
}
