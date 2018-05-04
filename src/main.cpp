#include <iostream>

#include "game/game.hpp"

int main()
{
    try
    {
        game::Game game;
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        std::cin.get();
    }

    return 0;
}
