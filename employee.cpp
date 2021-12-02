#include "employee.hpp"


Employee::Employee(std::string firstName,
            std::string lastName,
            std::string pesel,
            Address address,
            Sex sex,
            size_t salary)
    : Person(PersonType::Employee, firstName, lastName, pesel, address, sex)
    , salary_{salary}
    {}

    size_t Employee::getIndexNumber() const {
        return 0;
    }
    size_t Employee::getSalary() const {
        return salary_;
    }