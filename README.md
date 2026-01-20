# CanvasDT
Four fundamentals of data structures exist: a **List** (array or linked list), a **Tree**, a **Graph**, and a **Map**. But what if we wanted to model just one data structure that can be shaped to any of these four?

Introducing **Canvas**, a data structure / data type I designed that is cursor-based, which works similarly to c++'s `std::vector`, but with features I designed for more freedom and separation of responsibility. It's designed to be as semantic as possible, and working with it feels like you're actually working with a Canvas. Idk maybe the name will change, but for now I'm still working with it. Here are some of it's features:

- Initialize as `Canvas<T>` and you've created yourself a simple **Array**. Initialize it as `Canvas<K,V>` and you now have a **Map**. Set `V` as another `Canvas<T>` and you can use it as an n-ary **Tree** or an unweighted **Graph**.
- Uses `struct Cursor`, which works similary to iterators in c++, except most functions in Canvas returns a Cursor by default, so you can do **Cursor Chaining**. Examples:
 ```cpp
    Canvas<int> canvas;

    auto cursor = canvas.position(4);
    for(int i = 0; i < 5; i++) cursor.insert(i+1);
    canvas.position(5).insert(10);

    Canvas<Person> people;
    people.build("Asteria", 20).move(2);
```

- Under the hood, it's really all just an array because it's the best data structure uwu *(but seriously, a data structure that is contiguous in memory and doesn't use pointers is immaculate)*, therefore it's an **Array-based implementation** of the other data structures.
- Need a range of Cursors? Use `struct Range`!
    - ex. `canvas.hold(canvas.begin(), canvas.end()).remove(5);`
    - *this removes elements that are equal to 5 within the range canvas[0] to canvas[size-1], which are `canvas.begin()` and `canvas.end()` respectively*
- and many more... I'll care to update this later I'm tired


### Not yet completed
- `Canvas<K,V>` and `Canvas<>` (a mixed list variant) implementation
- a way to enforce **LIFO**, **FIFO**, **minHeap** and **maxHeap** behavior
- a proper, universal `void display()` that matches the actual structure of the Canvas
- error handling
- more code documentation

### How to use
I don't really know dawg, copy my code maybe? The main logic is in the `Canvas.hpp` file, and I use the `main.cpp` for testing the code. I guess you can download these and run it yourself. Have fun!