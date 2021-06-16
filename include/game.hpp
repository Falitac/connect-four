#pragma once
#include <SFML/Graphics.hpp>
#include "menuState.hpp"
#include "playState.hpp"

#include <iostream>
#include <map>
#include <utility>
#include <memory>
#include <vector>
#include <stack>
#include <array>

using StatePtr = std::unique_ptr<State>;
using TexturePtr = std::unique_ptr<sf::Texture>;
using std::tuple;
using std::get;
using std::cout;
using std::endl;

extern const unsigned GEM_COUNT;

class Game {
private:
  bool isRunning;
  sf::String gameName;

  StatePtr nextState;
  std::stack<StatePtr> states; 
  bool shouldChangeState;

  void handleEvents();
  void update(float);
  void render();
  void showPerformanceInfo(sf::Clock& debugClock, unsigned& fpsCount, unsigned& tickCount);
  void checkStates();
public:
  sf::RenderWindow window;
  sf::Font defaultFont;
  std::map<int, bool> pressedKeys;

  Game();
  void run();

  void pushState(StatePtr);
  void changeState(const bool& shouldChange);
};




