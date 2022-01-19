#pragma once
#include <string>

class Address {
public:
    Address(std::string postalCode, std::string city, std::string streetAndNumber);

    std::string getAddress() const;
    std::string getPostalCode() const;
    std::string getCity() const;
    std::string getStreetAndNumber() const;
    
    bool operator==(const Address& other) const;

private:
    std::string postalCode_;
    std::string city_;
    std::string streetAndNumber_;
};
