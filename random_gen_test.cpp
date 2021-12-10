#include <iostream>
#include "data_generator.hpp"

int main() {

    DataGenerator gen;

    for (int i = 0; i < 25; ++i) {
        std::cout << i << ": "
                  << gen.randomFirstName() << "  "
                  << gen.randomLastName() << "  "
                  << gen.randomCity() << "  "
                  << gen.randomStreetAndNumber() << '\n';
    }



    return 0;
}