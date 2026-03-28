#pragma once
#include <cassert>

namespace lumi {
    template<typename T> class Locus;

    template<typename T>
    struct Point {
        Locus<T>* owner;
        size_t pos;

        Point(Locus<T>* owner, size_t pos): owner(owner), pos(pos) {}

        Point insert()        { owner->add_at(pos, {}); return *this; }
        Point insert(T val)   { owner->add_at(pos, val); return *this; }
        void erase()          { owner->remove_at(pos); }
    };

    template<typename T>
    struct Chain {
        Point<T> start;
        Point<T> finish;

        Chain(Point<T> start, Point<T> finish): start(start), finish(finish) {
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
}