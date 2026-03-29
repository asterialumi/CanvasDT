#pragma once

namespace lumi {
    template<typename T> class Locus;

    template<typename T>
    class List { //Doubly-linked List, can be Circular
    public:
        
    private:
        Locus<T>& source;
        
    };

    template<typename T>
    class Tree { //n-ary tree, n can be restricted to a number, for instance 2 (binary tree)
    public:
        
    private:
        Locus<T>& source;
        
    };

    template<typename T, typename W = void>
    class Graph { //unweighted by default
    public:
        
    private:
        Locus<T>& source;
        Locus<W> edges;
        
    };

    template<typename T>
    class Graph<T,void> { //weighted version
    public:
        
    private:
        Locus<T>& source;
        
    };

    template<typename K, typename V>
    class Map {
    public:
        
    private:
        Locus<K> keys;
        Locus<V>& values;
        
    };

    template<typename T>
    class Set {
    public:
        
    private:
        Locus<T>& source;
        
    };

    /*
    set = hashset
    bag = hash multiset
    flow = ordered set

    map = unordered map

    */
}

//DONE
/*

- start conceptualizing class diagram so I don't get lost again
- namespace lumi
- change Canvas definition to be a "framework" for more specialized structures (Views), might change the naming later
- Canvas is now just a pure array with readable and more quality of life functions/abstractions
- change T1 to T
- remove Canvas<K,V>, its now part of MapView()
- create Views.hpp

*/


//TODO
/*

- finish class diagram and upload to git
- complete cursor-chaining
- make the actual exception handling (maybe another header)
- implement views, make sure to implement their display()s well
- separate cursor and range into another header for simplicity and readability

*/