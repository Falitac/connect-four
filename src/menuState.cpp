#include "../include/menuState.hpp"

#include <iostream>
using std::cout;
using std::endl;



MenuState::MenuState(Game& game_a):
State(game_a) {
}


void MenuState::handleEvents(sf::Event& event) {
  if(event.type == sf::Event::KeyPressed) {
    cout << event.key.code << endl;
    if(event.key.code == sf::Keyboard::Escape) {
      game->pushState(std::make_unique<PlayState>(*game));
      game->changeState(true);
    }
  }
}


void MenuState::update(float deltaTime) {
}


void MenuState::render() {
  game->window.clear({0x4c, 0x46, 0xae});
  game->window.display();
}
