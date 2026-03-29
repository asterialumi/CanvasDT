#include <iostream>
#include "../include/lumi/Locus.hpp"
using namespace lumi;

void space() {
    std::cout << std::endl << std::endl;
}

int main() {
    Locus<int> locus;
    
    std::cout << "INSERT W/ CURSOR: " << std::endl;
    locus.insert(10);
    locus.at(0).insert(5);
    locus.display();

    space();

    std::cout << "GET: " << std::endl;
    std::cout << "canvas[0] = " << locus[0] << std::endl;
    std::cout << "also canvas[0] = " << locus.first() << std::endl;
    
    space();

    std::cout << "RESERVE: " << std::endl;
    locus.reserve(8);
    locus.display();

    space();

    std::cout << "INSERT W/ RANGE: " << std::endl;
    locus.trace(locus.begin(), locus.at(5)).insert(2);
    locus.display();

    space();

    std::cout << "ERASE W/ CURSOR: " << std::endl;
    locus.erase(5);
    locus.end().erase();
    locus.display();

    space();
    
    std::cout << "ERASE W/ RANGE: " << std::endl;
    locus.trace(locus.at(2), locus.end()).erase(2);
    locus.display();

    space();

    std::cout << "CLEAR: " << std::endl;
    locus.clear();
    locus.display();
    return 0;
}