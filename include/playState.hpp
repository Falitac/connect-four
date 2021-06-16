#pragma once
#include "state.hpp"
#include "game.hpp"
#include "board.hpp"
#include "random.hpp"
#include <memory>
#include <vector>

class PlayState :public State {
public:
  PlayState(Game&);

  virtual void handleEvents(sf::Event&);
  virtual void update(float);
  virtual void render();
private:
  Board board;
};
