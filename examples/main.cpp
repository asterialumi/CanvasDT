// #include "CursorArray.hpp"
#include "../include/lumi/Locus.hpp"
#include <iostream>
#include <print>
using namespace lumi;

int main() {
    std::print("Success! You are now using C++23 on GCC 15.\n");
    /*
    Capabilities I want:

    Canvas<int> page = {1,2,3,4,5}; - initializer list
    
    page[0] = operator[] access

    auto cursor = page.position(0); = position mark

    (auto is Canvas<T>::Cursor)

    auto stack = page.last();
    auto queue = page.first();

    stack.push(10); = STACK BEHAVIOR
    queue.push(12); = QUEUE BEHAVIOR

    (push is special to Cursors only, to make it more semantic. Cursors have identical functions to Container, but push is designed to
    push at the back ALWAYS, regardless to which position the Cursor is pointing)

    stack.peek(); = peeks the value (returns)
    stack.pop(); = pops the value (removes), checks if the Cursor is pointing at either 0 or _size - 1

    */

    Locus<int> page;
    page.insert(10);
    page.insert();
    page.at(1).insert(5);
    Point<int> start = page.at(0);
    start.insert(15);
    start.insert(20);
    page.display();

    page.at(2); //returns non-void
    std::cout << std::endl << "did it work wtf" << std::endl; //testing if not assigning a function returning non-void works, it did

    Locus<int> page2(5); //constructing Canvas with size 5
    Locus<int> page3(5,100); //constructing Canvas with 5 100s
    std::cout << "page 2 size: " << page2.size() << std::endl;
    page2.display();
    page3.display();

    std::cout << std::endl << "holy shit!: " << page[0];
    page[0] = 200;
    std::cout << std::endl << "i changed it uwu: " << page[0] << std::endl;

    for(int i = 0; i < 3; i++) page3.erase();
    page3.display();

    //std::cout << page; this does NOT work
    
    Locus<int> test;
    for(int i = 0; i < 5; i++) test.insert(i+1);
    std::cout << "Before hold: ";
    test.display();

    test.range(test.begin(), test.end()).insert(2);

    std::cout << std::endl << "After hold: ";
    test.display();

    test.range(test.begin(), test.end()).erase(2);
    test.display();

    //cursor chaining
    auto cursor = test.at(0);
    cursor.insert(4)
          .insert(9)
          .insert(16)
          .insert(25);

    test.display();

    return 0;
}