#pragma once
#include <SFML/Graphics.hpp>

using OptionalPairNums = std::optional<std::pair<std::size_t, std::size_t>>;

class Game;

class Board {
public:
  Board(Game& game);

  void update(const float& deltaTime);
  void render();
  void handleEvents(sf::Event& event);
private:
  Game* game;
  std::vector<std::vector<uint8_t>> board;
  float boxSize;
  float padding;
  sf::Vector2i mousePosition;

  bool tryToSet;
  uint8_t ture;
  uint8_t playerCount;
  std::array<sf::Color, 3> colors;

  

  OptionalPairNums lowestBox;
  OptionalPairNums findLowest();
  void resetBoard();
  bool checkFour(std::size_t x, std::size_t y);
};
