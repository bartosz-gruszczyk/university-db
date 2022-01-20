#include "person.hpp"

Person::Person(PersonType type,
               std::string firstName,
               std::string lastName,
               std::string pesel,
               Address address,
               Sex sex) 
    : type_{type}
    , firstName_{firstName}
    , lastName_{lastName}
    , pesel_{pesel}
    , address_{address}
    , sex_{sex}
    {}

Person::~Person() {}

Person::PersonType Person::getType() const {
    return type_;
}

std::string Person::getFirstName() const {
    return firstName_;
}

std::string Person::getLastName() const {
    return lastName_;
}

std::string Person::getPesel() const {
    return pesel_;
}

std::string Person::getAddress() const {
    return address_.getAddress();
}

Sex Person::getSex() const {
    return sex_;
}

std::string Person::getPostalCode() const {
    return address_.getPostalCode();
}

std::string Person::getCity() const {
    return address_.getCity();
}

std::string Person::getStreetAndNumber() const {
    return address_.getStreetAndNumber();
}

const Address& Person::address() {
    return address_;
}
