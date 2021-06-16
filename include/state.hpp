#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class State
{
protected:
  Game* game;
public:
  State(Game &game) {
    this->game = &game;
  }
  virtual ~State() {
    game = nullptr;
  }

  virtual void handleEvents(sf::Event&) = 0;
  virtual void update(float) = 0;
  virtual void render() = 0;
};
