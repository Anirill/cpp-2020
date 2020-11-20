#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H

#include "xor_sum.h"
#include "binary.h"

////////////////   Declaration

template <
    size_t xs, 
    size_t Head, 
    size_t... Tail
    >
struct FindHeap;

template <size_t xs, size_t... Heaps>
struct StartSearch;

////////////////   Conditional HEAP search

template <
    bool cond, 
    size_t xs, 
    size_t Head, 
    size_t... Tail
    >
struct  Search {
    static constexpr ssize_t num = FindHeap<xs, Tail...>::num;
    static constexpr ssize_t value = FindHeap<xs, Tail...>::value;
    static constexpr ssize_t heap_to_use = FindHeap<xs, Tail...>::heap_to_use;
};

template <
    size_t xs, 
    size_t Head, 
    size_t... Tail
    >
struct Search<true, xs, Head, Tail...> {
    static constexpr ssize_t num = FindHeap<xs, Tail...>::num;
    static constexpr ssize_t value = Head;
    static constexpr ssize_t heap_to_use = num;
};

template <bool cond, size_t xs, size_t Head>
struct  Search<cond, xs, Head> {
    static constexpr ssize_t num = 0;
    static constexpr ssize_t value = Head;
    static constexpr ssize_t heap_to_use = 0;
};

////////////////   Unconditional HEAP search

template <size_t xs, size_t Head, size_t... Tail> // first and mid spec
struct FindHeap {
    static constexpr ssize_t num = 1 + FindHeap<xs, Tail...>::num;  // count heaps here

    static constexpr ssize_t value = 
        Search<
            ((GetBit<Log2<xs>::value - 1, Head>::value == 1)),     
            xs,        
            Head, 
            Tail...
        >::value; 

    static constexpr ssize_t heap_to_use = 
        Search<
            ((GetBit<Log2<xs>::value - 1, Head>::value == 1)), 
            xs,            
            Head, 
            Tail...
        >::heap_to_use;   
};

template <size_t xs, size_t Head>  // last spec
struct  FindHeap<xs, Head> {
    static constexpr ssize_t num = 1;  // last element is count 1
    static constexpr ssize_t value = Head;
    static constexpr ssize_t heap_to_use = 0;  // from last element
};

////////////////   Heap index calculate

template <size_t xs, size_t... Heaps>  // usual spec
struct HeapIndex {
    static constexpr ssize_t value = StartSearch<xs, Heaps...>::num - StartSearch<xs, Heaps...>::heap_to_use - 1;
};

template <size_t... Heaps>  // ZERO XOR spec
struct HeapIndex<0, Heaps...> {
    static constexpr ssize_t value = -1;
};

////////////////   Rocks count calculate

template <size_t xor_res, size_t search_res, size_t... Heaps>  // usual spec
struct RocksCount { 
    static constexpr ssize_t value = search_res - XorSum<XorSum<Heaps...>::value, search_res>::value;
};

template <size_t search_res, size_t... Heaps>  // ZERO XOR spec
struct RocksCount<0, search_res, Heaps...> {
    static constexpr ssize_t value = -1;
};

////////////////   Main part

template <size_t xs, size_t... Heaps>  // usual spec
struct StartSearch {
    static constexpr ssize_t num = FindHeap<xs, Heaps...>::num;
    static constexpr ssize_t value = FindHeap<xs, Heaps...>::value;
    static constexpr ssize_t heap_to_use = FindHeap<xs, Heaps...>::heap_to_use;
};

template <size_t... Heaps>  // ZERO XOR spec
struct StartSearch<0, Heaps...> {
    static constexpr ssize_t num = 0;
    static constexpr ssize_t value = 0;
    static constexpr ssize_t heap_to_use = 0;

};

template <size_t... Heaps>
struct Game {
    static constexpr bool first_player_wins = XorSum<Heaps...>::value;
    static constexpr ssize_t first_move_heap_index = HeapIndex<XorSum<Heaps...>::value, Heaps...>::value;
    static constexpr ssize_t first_move_rocks_count = RocksCount<
        XorSum<Heaps...>::value, 
        StartSearch<XorSum<Heaps...>::value, Heaps...>::value, 
        Heaps...
        >::value;   
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H.
