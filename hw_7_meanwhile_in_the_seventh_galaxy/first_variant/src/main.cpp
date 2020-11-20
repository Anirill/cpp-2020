#include <iostream>
#include "game.h"



int main () {
    using game = Game<28, 27, 24, 22, 15>;
    //using game = Game<22, 24, 27, 28>;
    //using game = Game<4, 4, 4, 4>;

    std::cout << (game::first_player_wins ? "First" : "Second") << " player wins." << std::endl;
    std::cout << game::maxx << std::endl;
    std::cout << game::maxx_num << std::endl;
    
    if (game::first_player_wins)
        std::cout <<
            "To win, remove " << game::first_move_rocks_count <<
            " from heap " << (game::first_move_heap_index + 1) << std::endl;

    return 0;

}
