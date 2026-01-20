#pragma once
#include <iostream>
#include <new>
#include <utility>
#include <cassert>

//DECLARATION
struct empty {};
template< typename T1 = empty, typename T2=void >
class Canvas;

//DEFINITION
using log_t = unsigned int;

//Canvas<T> = linear
//Canvas<K,V> = associative
//Canvas<Canvas<T>> or Canvas<K, Canvas<T>> = hierarchical and network

template<typename T1>
class Canvas<T1, void> {
public:

    // --------------------
    // CREATION
    // --------------------
    Canvas(): Canvas(0) {}
    
    Canvas(size_t init_size): Canvas(init_size, {}) {}

    Canvas(size_t init_size, T1 val) {
        if(init_size > 0) {
            reserve(init_size);
            for(size_t i = 0; i < init_size; i++) {
                insert(val);
            }
        }

        _size = init_size;
    }
    
    //DESTRUCTOR
    ~Canvas() noexcept {
        clear();
        ::operator delete(data);
    }

    // --------------------
    // INTERFACE
    // --------------------

    struct Cursor { //just focus about movement for now
        Canvas<T1>* owner;
        size_t pos;

        Cursor(Canvas<T1>* owner, size_t pos): owner(owner), pos(pos) {}

        void insert()       { owner->add_at(pos, {}); }
        void insert(T1 val) { owner->add_at(pos, val); }
        void erase()        { owner->remove_at(pos); }
    };

    struct Range {
        Cursor start;
        Cursor finish;

        Range(Cursor start, Cursor finish): start(start), finish(finish) {
            assert(start.owner == finish.owner); //throw-->DifferentOwners
            assert(start.pos <= finish.pos); //throw-->InvalidRange
        }

        void insert() {
            for(size_t i = start.pos; i <= finish.pos; i++) {
                start.owner->add_at(i, {});
            }
        }
        
        void insert(T1 val) {
            for(size_t i = start.pos; i <= finish.pos; i++) {
                start.owner->add_at(i, val);
            }
        }

        void erase() {
            for(size_t i = finish.pos+1; i-- > start.pos;) {
                start.owner->remove_at(i);
            }
        }

        void erase(T1 val) {
            for(size_t i = finish.pos+1; i-- > start.pos;) {
                if(start.owner->data[i] == val) {
                    start.owner->remove_at(i);
                }
            }
        }
    };

    // --------------------
    // FUNCTIONS
    // --------------------

    //INSERT
    void insert() { add_at(_size, {}); }
    void insert(T1 val) { add_at(_size, val); }

    //REMOVE
    void erase() { remove_at(_size - 1); }
    void erase(T1 val) {
        for(size_t i = 0; i < _size; i++) {
            if(data[i] == val) {
                remove_at(i);
                return;
            }
        }

        return; //throw-->ElementDoesNotExist
    }

    void clear() {
        for(size_t i = 0; i < _size; i++) {
            data[i].~T1();
        }
        _size = 0;
    }

    //ACCESS
    T1& operator[](size_t index) {
        assert(index < _size); //throw-->OutofBounds
        return data[index];
    }

    const T1& operator[](size_t index) const {
        assert(index < _size); //throw-->OutofBounds
        return data[index];
    }

    T1* first()       { return operator[](0); }
    T1* last()        { return operator[](_size-1); }
    size_t size()        { return _size; }
    size_t capacity()    { return _capacity; }
    log_t allocations() { return _allocations; }

    //MOVEMENT
    Cursor position(size_t index) { return Cursor{ this, index }; }
    Range hold(Cursor begin, Cursor end) { return { begin, end }; }

    Cursor begin() { return position(0); }
    Cursor end()   { return position(_size - 1); }

    //UTILITY
    void display() const {
        //not final
        std::cout << _size << "/" << _capacity << std::endl;
        std::cout << "Allocations: " << _allocations << std::endl;
        
        std::cout << "[";
        for(size_t i = 0; i < _size; i++) {
            std::cout << data[i];
            if(i+1 < _size) std::cout << ",";
        }
        std::cout << "]";

    }

    void reserve(int memory) {
        if(memory < _size) return; //throw-->LengthUnderflow
        _capacity = memory;
        data = allocate(data, _capacity);
    }

private:
    // --------------------
    // VARIABLES
    // --------------------
    T1*    data{};
    size_t _size{};
    size_t _capacity{};
    log_t  _allocations{};


    // --------------------
    // HELPERS
    // --------------------
    void grow(float factor) {
        factor = factor * _capacity;
        if(factor - static_cast<int>(factor) > 0.5) factor++;
        _capacity = _capacity == 0 ? 2 : factor;
        data = allocate(data, _capacity);
        
        //DEBUG
        std::cout << "grow:" << _size << "/" << _capacity << std::endl;
    }

    T1* allocate(T1* origin, size_t memory) {
        T1* buffer = static_cast<T1*>(::operator new(memory * sizeof(T1)));

        for(size_t i = 0; i < _size; i++) {
            new (&buffer[i]) T1(std::move(origin[i]));
            origin[i].~T1();
        }

        ::operator delete(origin);
        _allocations++;
        return buffer;
    }

    void add_at(size_t index, T1 val) {
        assert(index <= _size);
        if(_size == _capacity) grow(1.6);

        for(size_t i = _size; i > index; i--) {
            new (&data[i]) T1(std::move(data[i-1]));
            data[i-1].~T1();
        }

        new (&data[index]) T1(val);
        ++_size;
    }

    void remove_at(size_t index) {
        assert(_size > 0); //throw-->EmptyContainer
        assert(index < _size); //throw-->OutofBounds

        data[index].~T1();

        for(size_t i = index; i+1 < _size; i++) {
            new (&data[i]) T1(std::move(data[i+1]));
            data[i+1].~T1();
        }

        --_size;
    }
};













template<typename T1, typename T2>
class Canvas {
    T1* key;
    T2* value;
    
};

template<>
class Canvas<empty, void> {
    //Mixed List
};