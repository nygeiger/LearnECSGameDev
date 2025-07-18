#include "../headers/GameEngine.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello, Mega Mario!" << std::endl;

    GameEngine g("assets.txt");
    g.run();
    return 0;
}