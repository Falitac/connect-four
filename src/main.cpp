#include "../include/game.hpp"

#include <iostream>

int main() {
  Game game;

  try {
    game.run();
  } catch(std::exception& e) {
    std::cout << "Error occured: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch(...) {
    std::cout << "Error occured\n";
    return EXIT_FAILURE;
  }
}
