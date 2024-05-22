#include "cliparse.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    CliParser parser{argc, argv};

    for (const auto& arg : parser) {
        std::cout << arg;
    }
}
