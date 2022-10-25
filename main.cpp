#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <game/GameRunner.hpp>

using namespace sf;

int main(void) {
    
    GameRunner *game = GameRunner::Game();
    
    game->init();
    game->run();

    return EXIT_SUCCESS;
}