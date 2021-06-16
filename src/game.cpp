#include "../include/game.hpp"

using std::cout;
using std::endl;


Game::Game()
:isRunning(true),
gameName("Connect four"),
shouldChangeState(false) {
  window.create({640, 640}, gameName, sf::Style::Default);

  defaultFont.loadFromFile("resources/carten.otf");

  states.push(std::make_unique<PlayState>(*this));
}


void Game::run() {
  sf::Time accumulator;
  sf::Time lastFrameTime;
  sf::Time fixedTickTime = sf::seconds(1.0f / 60.0f);
  sf::Clock timeStepClock;
  sf::Clock debugClock;
  unsigned fpsCount = 0;
  unsigned tickCount = 0;
  debugClock.restart();
  timeStepClock.restart();

  while(isRunning && !states.empty()) {
    checkStates();
    fpsCount++;
    accumulator +=  timeStepClock.getElapsedTime() - lastFrameTime;
    lastFrameTime = timeStepClock.getElapsedTime();

    handleEvents();

    while(accumulator >= fixedTickTime) {
      tickCount++;
      update(fixedTickTime.asSeconds());
      accumulator -= fixedTickTime;
    }
    showPerformanceInfo(debugClock, fpsCount, tickCount);
    render();
  }
}


void Game::handleEvents() {
  for(sf::Event event; window.pollEvent(event);) {
    states.top()->handleEvents(event);
    switch(event.type) {
    case sf::Event::KeyPressed:
      pressedKeys[event.key.code] = true;
      break;
    case sf::Event::KeyReleased:
      pressedKeys[event.key.code] = false;
      break;
    case sf::Event::Closed:
      isRunning = false;
      window.close();
      break;
    default:
      break;
    }
  }
}


void Game::update(float deltaTime) {
  states.top()->update(deltaTime);
}


void Game::render() {
  states.top()->render();
}


void Game::showPerformanceInfo(sf::Clock& debugClock, unsigned& fpsCount, unsigned& tickCount) {
  using std::tuple;
  using std::get;
  if(debugClock.getElapsedTime() >= sf::seconds(1.0f)) {
    #ifndef NDEBUG
    window.setTitle(
      gameName  
      + " FPS: "
      + std::to_string(fpsCount)
      + " TICKS: "
      + std::to_string(tickCount)
    );
    #endif
    debugClock.restart();
    tickCount = 0;
    fpsCount = 0;
  }
}


void Game::checkStates() {
	if(shouldChangeState) {
		if(!states.empty()) {
			states.pop();
		} else {
			return;
    }
		if(nextState != nullptr) {
			states.push(std::move(nextState));
			std::cout << "State Changed!" << std::endl;
		}
		shouldChangeState = false;
	}
}


void Game::pushState(StatePtr state) {
  if(state != nullptr) {
    nextState = std::move(state);
  }
}


void Game::changeState(const bool& shouldChange) {
  shouldChangeState = shouldChange;
}