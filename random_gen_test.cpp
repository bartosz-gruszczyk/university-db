#include <iostream>
#include "data_generator.hpp"

int main() {

    DataGenerator gen;

    for (int i = 0; i < 25; ++i) {
        std::cout << i << ": " << gen.randomCity() << '\n';
    }



    return 0;
}