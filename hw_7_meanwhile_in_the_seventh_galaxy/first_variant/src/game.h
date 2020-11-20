#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H

#include "xor_sum.h"
#include "binary.h"

//class NullType {};

template <size_t Head, size_t... Tail>
struct FindMax;

////////////////   Conditional MAX search

template <bool cond, size_t Head, size_t... Tail>
struct  Max {
    static constexpr ssize_t num = FindMax<Tail...>::num;
    static constexpr ssize_t value = FindMax<Tail...>::value;
    static constexpr ssize_t max_num = FindMax<Tail...>::max_num;
};

template <size_t Head, size_t... Tail>
struct Max<true, Head, Tail...> {
    static constexpr ssize_t num = FindMax<Tail...>::num;
    static constexpr ssize_t value = Head;
    static constexpr ssize_t max_num = num;
};

template <bool cond, size_t Head>
struct  Max<cond, Head> {
    static constexpr ssize_t num = 0;
    static constexpr ssize_t value = Head;
    static constexpr ssize_t max_num = 0;
};

////////////////   Unconditional MAX search

template <size_t Head, size_t... Tail> // first and mid spec
struct FindMax {
    static constexpr ssize_t num = 1 + FindMax<Tail...>::num;  // count heaps here
    static constexpr ssize_t value = Max<(GetBit<Log2<XorSum<Head, Tail...>::value>::value, Head>::value == 1), Head, Tail...>::value; 
    static constexpr ssize_t max_num = Max<(GetBit<Log2<XorSum<Head, Tail...>::value>::value, Head>::value == 1), Head, Tail...>::max_num;   
};

template <size_t Head>  // last spec
struct  FindMax<Head> {
    static constexpr ssize_t num = 1;  // last element is count 1
    static constexpr ssize_t value = Head;
    static constexpr ssize_t max_num = 0;  // from last element
};

////////////////   Heap index calculate

template <size_t x, size_t... Heaps>  // usual spec
struct heap_index {
    static constexpr ssize_t value = FindMax<Heaps...>::num - FindMax<Heaps...>::max_num - 1;
};

template <size_t... Heaps>  // ZERO XOR spec
struct heap_index<0, Heaps...> {
    static constexpr ssize_t value = -1;
};

////////////////   Rocks count calculate

template<size_t xor_res, size_t max_res, size_t... Heaps>  // usual spec
struct rocks_count { 
    static constexpr ssize_t value = max_res - XorSum<XorSum<Heaps...>::value, max_res>::value;
};

template<size_t max_res, size_t... Heaps>  // ZERO XOR spec
struct rocks_count<0, max_res, Heaps...> {
    static constexpr ssize_t value = -1;
};

////////////////   Main part

template <size_t... Heaps>
struct Game {
    static constexpr bool first_player_wins = XorSum<Heaps...>::value;
    static constexpr ssize_t first_move_heap_index = heap_index<XorSum<Heaps...>::value, Heaps...>::value;
    static constexpr ssize_t first_move_rocks_count = rocks_count<XorSum<Heaps...>::value, FindMax<Heaps...>::value, Heaps...>::value;
    static constexpr ssize_t maxx = FindMax<Heaps...>::value;
    static constexpr ssize_t maxx_num = FindMax<Heaps...>::num - FindMax<Heaps...>::max_num;
    
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H.
