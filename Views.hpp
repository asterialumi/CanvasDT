#pragma once
#include "Canvas.hpp"

namespace lumi {
    //ListView();
    //TreeView();
    //GraphView();
    //MapView();
    //HeapView();
    //SetView();
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