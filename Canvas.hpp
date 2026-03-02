#pragma once
#include <iostream>
#include <new>
#include <utility>
#include <cassert>
#include "Views.hpp"

using log_t = unsigned int;

namespace lumi {
    template<typename T>
    class Canvas {
    public:

        // --------------------
        // CREATION
        // --------------------
        Canvas(): Canvas(0) {}
        
        Canvas(size_t init_size): Canvas(init_size, {}) {}

        Canvas(size_t init_size, T val) {
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
        // STRUCTURE
        // --------------------

        struct Cursor { //just focus about movement for now
            Canvas<T>* owner;
            size_t pos;

            Cursor(Canvas<T>* owner, size_t pos): owner(owner), pos(pos) {}

            Cursor insert()       { owner->add_at(pos, {}); return *this; }
            Cursor insert(T val) { owner->add_at(pos, val); return *this; }
            void erase()          { owner->remove_at(pos); }
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
            
            void insert(T val) {
                for(size_t i = start.pos; i <= finish.pos; i++) {
                    start.owner->add_at(i, val);
                }
            }

            void erase() {
                for(size_t i = finish.pos+1; i-- > start.pos;) {
                    start.owner->remove_at(i);
                }
            }

            void erase(T val) {
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
        Cursor insert() { return insert({}); }
        Cursor insert(T val) {
            add_at(_size, val);
            return position(_size - 1);
        }

        template<typename... Args>
        Cursor build(Args&&... args) {
            if(_size == _capacity) grow(1.6);
            new (&data[_size++]) T(std::forward<Args>(args)...);
            return position(_size - 1);
        }

        //REMOVE
        //no cursor chaining here for now
        void erase() { remove_at(_size - 1); }
        void erase(T val) {
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
                data[i].~T();
            }
            _size = 0;
        }

        //ACCESS
        T& operator[](size_t index) {
            assert(index < _size); //throw-->OutofBounds
            return data[index];
        }

        const T& operator[](size_t index) const {
            assert(index < _size); //throw-->OutofBounds
            return data[index];
        }

        T* first()          { return operator[](0); }
        T* last()           { return operator[](_size-1); }
        size_t size()        { return _size; }
        size_t capacity()    { return _capacity; }
        log_t allocations()  { return _allocations; }

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
        T*    data{};
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

        T* allocate(T* origin, size_t memory) {
            T* buffer = static_cast<T*>(::operator new(memory * sizeof(T)));

            for(size_t i = 0; i < _size; i++) {
                new (&buffer[i]) T(std::move(origin[i]));
                origin[i].~T();
            }

            ::operator delete(origin);
            _allocations++;
            return buffer;
        }

        void add_at(size_t index, T val) {
            assert(index <= _size);
            if(_size == _capacity) grow(1.6);

            for(size_t i = _size; i > index; i--) {
                new (&data[i]) T(std::move(data[i-1]));
                data[i-1].~T();
            }

            new (&data[index]) T(val);
            ++_size;
        }

        void remove_at(size_t index) {
            assert(_size > 0); //throw-->EmptyContainer
            assert(index < _size); //throw-->OutofBounds

            data[index].~T();

            for(size_t i = index; i+1 < _size; i++) {
                new (&data[i]) T(std::move(data[i+1]));
                data[i+1].~T();
            }

            --_size;
        }
    };
}