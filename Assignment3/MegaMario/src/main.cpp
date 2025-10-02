#include "headers/GameEngine.h"
#include <iostream>

// g++ -std=c++17 *.cpp -o ../bin/CLmain -I/Users/nyles/GeneralWorkshop/Personal/SelfTeach/GameProgramingC++/Assignment3/MegaMario -I/opt/homebrew/Cellar/sfml/3.0.1/include -L/opt/homebrew/Cellar/sfml/3.0.1/lib -lsfml-window -lsfml-graphics -lsfml-system

// https://www.sfml-dev.org/tutorials/3.0/
// https://www.sfml-dev.org/documentation/3.0.0/index.html

int main(int argc, char* argv[]) {
    std::cout << "Hello, Mega Mario!" << std::endl;

    GameEngine g("../assets/assets.txt");
    g.run();
    return 0;
}