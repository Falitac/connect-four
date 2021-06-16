#pragma once
#include "state.hpp"
#include "playState.hpp"
#include "game.hpp"
#include <vector>
#include <memory>

class MenuState :public State {
private:

public:
  MenuState(Game &);

  virtual void handleEvents(sf::Event&);
  virtual void update(float);
  virtual void render();
};
