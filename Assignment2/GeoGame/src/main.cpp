#include <iostream>
#include <string>

#include "../headers/Vec2.h"
#include "../headers/Game.h"

// g++ -std=c++17 main.cpp Vec2.cpp -o CLmain -I/opt/homebrew/Cellar/sfml/3.0.0_1/include -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-window -lsfml-graphics -lsfml-system
sf::Font getFont()
{
    sf::Font myFont;
    std::string fontLocation = "../fonts/Bytesized/Bytesized-Regular.ttf";
    if (!myFont.openFromFile(fontLocation))
    {
        // # if we can't load the font, print an error to the error console and exit
        std::cerr << "Could not load font!" << std::endl;
        exit(-1);
    }
    return myFont;
}

int main (int argc, char *argv[]) {
    // // Initialize the game
    // Game game;
    // game.init();

    // // Main game loop
    // while (game.isRunning()) {
    //     game.update();
    //     game.render();
    // }

    // // Clean up and exit
    // game.cleanup();
    std::cout << "Hello, World!" << std::endl;

    Vec2 v1(100, 200);
    Vec2 v2(300, 500);

    std::cout << "v1: (" << v1.x << ", " << v1.y << ")" << std::endl;
    std::cout << "v2: (" << v2.x << ", " << v2.y << ")" << std::endl;
    std::cout << "v1 + v2: (" << (v1 + v2).x << ", " << (v1 + v2).y << ")" << std::endl;
    std::cout << "v1 + v2: (" << (v1 + v2).x << ", " << (v1 + v2).y << ")" << std::endl;


    Game game("../config/configFile.txt");
    game.run();


    return 0;
}