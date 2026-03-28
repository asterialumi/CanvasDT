#pragma once
#include <iostream>
#include <new>
#include <utility>
#include <cassert>

using log_t = unsigned int;

namespace lumi {
    template<typename T> struct Point;
    template<typename T> struct Chain;

    template<typename T>
    class Locus {
    public:
        // --------------------
        // CREATION
        // --------------------

        Locus(): Locus(0) {}
        
        Locus(size_t init_size): Locus(init_size, {}) {}

        Locus(size_t init_size, T val) {
            if(init_size > 0) {
                reserve(init_size);
                for(size_t i = 0; i < init_size; i++) {
                    insert(val);
                }
            }

            _size = init_size;
        }
        
        //DESTRUCTOR
        ~Locus() noexcept {
            clear();
            ::operator delete(data);
        }

        // --------------------
        // FUNCTIONS
        // --------------------

        //INSERT
        Point<T> insert() { return insert({}); }
        Point<T> insert(T val) {
            add_at(_size, val);
            return at(_size - 1);
        }

        template<typename... Args>
        Point<T> build(Args&&... args) {
            if(_size == _capacity) grow(1.6);
            new (&data[_size++]) T(std::forward<Args>(args)...);
            return at(_size - 1);
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

        T first()            { return operator[](0); }
        T last()             { return operator[](_size-1); }
        size_t size()        { return _size; }
        size_t capacity()    { return _capacity; }
        log_t allocations()  { return _allocations; }

        //MOVEMENT
        Point<T> at(size_t index) { return Point{ this, index }; }
        Chain<T> range(Point<T> begin, Point<T> end) { return { begin, end }; }

        Point<T> begin() { return at(0); }
        Point<T> end()   { return at(_size - 1); }

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
            std::cout << "]" << std::endl;

        }

        void reserve(int memory) {
            if(memory < _size) return; //throw-->LengthUnderflow
            _capacity = memory;
            data = allocate(data, _capacity);
        }
        
        template<template<typename> typename AspectType>
        auto view() {
            return AspectType<T> { *this };
        }
    private:
        // --------------------
        // VARIABLES
        // --------------------
        T* data{};

        friend struct Point<T>;
        friend struct Chain<T>;
    
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

#include "Traces.hpp"
#include "Aspects.hpp"