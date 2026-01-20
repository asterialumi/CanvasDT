// #include "CursorArray.hpp"
#include "Canvas.hpp"
#include <iostream>
//#include <print>


int main() {
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

    Canvas<int> page;
    page.insert(10);
    page.insert();
    page.position(1).insert(5);
    Canvas<int>::Cursor start = page.position(0);
    start.insert(15);
    start.insert(20);
    page.display();

    page.position(2); //returns non-void
    std::cout << std::endl << "did it work wtf" << std::endl; //testing if not assigning a function returning non-void works, it did

    Canvas<int> page2(5); //constructing Canvas with size 5
    Canvas<int> page3(5,100); //constructing Canvas with 5 100s
    Canvas<> page4;
    std::cout << "page 2 size: " << page2.size() << std::endl;
    page2.display();
    page3.display();

    std::cout << std::endl << "holy shit!: " << page[0];
    page[0] = 200;
    std::cout << std::endl << "i changed it uwu: " << page[0] << std::endl;

    for(int i = 0; i < 3; i++) page3.erase();
    page3.display();

    //std::cout << page; this does NOT work
    
    Canvas<int> test;
    for(int i = 0; i < 5; i++) test.insert(i+1);
    std::cout << "Before hold: ";
    test.display();

    test.hold(test.begin(), test.end()).insert(2);

    std::cout << std::endl << "After hold: ";
    test.display();

    test.hold(test.begin(), test.end()).erase(2);
    test.display();
    return 0;
}