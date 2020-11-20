#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H

#include "xor_sum.h"
#include "binary.h"

//class NullType {};

template <size_t Head, size_t... Tail>
struct FindHeap;

////////////////   Conditional MAX search

template <bool cond, size_t Head, size_t... Tail>
struct  Search {
    static constexpr ssize_t num = FindHeap<Tail...>::num;
    static constexpr ssize_t value = FindHeap<Tail...>::value;
    static constexpr ssize_t heap_to_use = FindHeap<Tail...>::heap_to_use;
};

template <size_t Head, size_t... Tail>
struct Search<true, Head, Tail...> {
    static constexpr ssize_t num = FindHeap<Tail...>::num;
    static constexpr ssize_t value = Head;
    static constexpr ssize_t heap_to_use = num;
};

template <bool cond, size_t Head>
struct  Search<cond, Head> {
    static constexpr ssize_t num = 0;
    static constexpr ssize_t value = Head;
    static constexpr ssize_t heap_to_use = 0;
};

////////////////   Unconditional MAX search

template <size_t Head, size_t... Tail> // first and mid spec
struct FindHeap {
    static constexpr ssize_t num = 1 + FindHeap<Tail...>::num;  // count heaps here
    static constexpr ssize_t value = Search<(GetBit<Log2<XorSum<Head, Tail...>::value>::value, Head>::value == 1), Head, Tail...>::value; 
    static constexpr ssize_t heap_to_use = Search<(GetBit<Log2<XorSum<Head, Tail...>::value>::value, Head>::value == 1), Head, Tail...>::heap_to_use;   
};

template <size_t Head>  // last spec
struct  FindHeap<Head> {
    static constexpr ssize_t num = 1;  // last element is count 1
    static constexpr ssize_t value = Head;
    static constexpr ssize_t heap_to_use = 0;  // from last element
};

////////////////   Heap index calculate

template <size_t x, size_t... Heaps>  // usual spec
struct HeapIndex {
    static constexpr ssize_t value = FindHeap<Heaps...>::num - FindHeap<Heaps...>::heap_to_use - 1;
};

template <size_t... Heaps>  // ZERO XOR spec
struct HeapIndex<0, Heaps...> {
    static constexpr ssize_t value = -1;
};

////////////////   Rocks count calculate

template<size_t xor_res, size_t max_res, size_t... Heaps>  // usual spec
struct RocksCount { 
    static constexpr ssize_t value = max_res - XorSum<XorSum<Heaps...>::value, max_res>::value;
};

template<size_t max_res, size_t... Heaps>  // ZERO XOR spec
struct RocksCount<0, max_res, Heaps...> {
    static constexpr ssize_t value = -1;
};

////////////////   Main part

template <size_t... Heaps>
struct Game {
    static constexpr bool first_player_wins = XorSum<Heaps...>::value;
    static constexpr ssize_t first_move_heap_index = HeapIndex<XorSum<Heaps...>::value, Heaps...>::value;
    static constexpr ssize_t first_move_rocks_count = RocksCount<XorSum<Heaps...>::value, FindHeap<Heaps...>::value, Heaps...>::value;
    static constexpr ssize_t maxx = FindHeap<Heaps...>::value;
    static constexpr ssize_t maxx_num = FindHeap<Heaps...>::num - FindHeap<Heaps...>::heap_to_use;
    
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H.
