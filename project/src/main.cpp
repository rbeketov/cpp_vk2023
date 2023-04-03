#include <iostream>
#include "calculator.h"

int main(int argc, char* argv[]) {
    print();
    std::cout << argv[argc-1] << std::endl;
    return 0;
}