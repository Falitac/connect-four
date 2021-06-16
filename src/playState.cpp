#include "../include/playState.hpp"


#include <iostream>
using std::cout;
using std::endl;

PlayState::PlayState(Game& game_a):
State(game_a),
board(Board(game_a)) {
}

void PlayState::handleEvents(sf::Event& event) {
  board.handleEvents(event);
}

void PlayState::update(float deltaTime) {
  board.update(deltaTime);
}

void PlayState::render() {
  game->window.clear({0x33, 0x33, 0x33});
  board.render();
  
  game->window.display();
}
 