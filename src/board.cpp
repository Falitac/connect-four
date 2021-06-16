#include "../include/board.hpp"
#include "../include/game.hpp"

#include <iostream>

void Board::handleEvents(sf::Event& event) {
  switch(event.type) {
    case sf::Event::MouseMoved:
      mousePosition = sf::Mouse::getPosition(game->window);
    break;
    case sf::Event::MouseButtonPressed:
      tryToSet = true;
    break;
    default:
    break;
  }
}

void Board::update(const float& deltaTime) {
  lowestBox = findLowest();
  if(tryToSet) {
    tryToSet = false;
    if(lowestBox) {
      board.at(lowestBox->second).at(lowestBox->first) = ture;
      if(checkFour(lowestBox->first, lowestBox->second)) {
        std::cout << "Player ";
        std::cout << static_cast<unsigned long long>(ture);
        std::cout << " wins!\n";
        //resetBoard();
      }
      if(ture == playerCount) {
        ture = 1;
      } else {
        ture++;
      }
    }
  }
  if(game->pressedKeys[sf::Keyboard::A]) {
    resetBoard();
  }
}

void Board::render() {
  sf::RectangleShape box;
  box.setOutlineThickness(3);
  box.setSize({boxSize, boxSize});
  for(std::size_t row = 0; row < board.size(); row++) {
    for(std::size_t col = 0; col < board[row].size(); col++) {
      box.setPosition({
        (boxSize + padding) * col + padding,
        (boxSize + padding) * row + padding
      });
      box.setOutlineColor(sf::Color::Black);
      box.setFillColor(colors[board[row][col]]);

      if(lowestBox) {
        if(col == lowestBox->first && row == lowestBox->second) {
          box.setOutlineColor(sf::Color::White);
        }
      }
      game->window.draw(box);
    }
  }

  box.setPosition({
    padding,
    (boxSize + padding) * board.size() + padding
  });
  box.setFillColor(colors[ture]);
  game->window.draw(box);
}
 

bool Board::checkFour(std::size_t x, std::size_t y) {
  using std::cout;
  uint8_t player = board[y][x];

  int counterLeft = 0;
  int counterRight = 0;
  int counter = 0;

  // collumn check
  for(std::size_t i = y; i < board.size() && i < y + 4; i++) {
    if(board[i][x] == player) {
      counter++;
    }
  }
  if(counter >= 4) {
    return true;
  }

  // row check
  for(std::size_t i = x + 1; i < board[0].size() && i < x + 4; i++) {
    std::cout << i << std::endl;
    if(board[y][i] != player) {
      break;
    } else {
      counterRight++;
    }
  }
  for(std::size_t i = x - 1; i >= 0 && i > x - 4; i--) {
    if(board[y][i] != player) {
      break;
    } else {
      counterLeft++;
    }
  }

  if(counterLeft + counterRight + 1 >= 4) {
    return true;
  }

  counterLeft = counterRight = 0;

  //diagonal check from up to down
  for(int i = 1; ; i++) {
    if(y + i >= board.size() || x + i >= board[0].size()) {
      break;
    }
    if(board[y + i][x + i] != player) {
      break;
    } else {
      counterRight++;
    }
  }
  for(int i = 1; ; i++) {
    if(int(y) - i < 0 || int(x) - i < 0) {
      break;
    }
    if(board[y - i][x - i] != player) {
      break;
    } else {
      counterLeft++;
    }
  }
  if(counterLeft + counterRight + 1 >= 4) {
    return true;
  }

  counterLeft = counterRight = 0;

  //diagonal check from down to up
  for(int i = 1; ; i++) {
    if(int(y) - i < 0 || int(x) + i >= board[0].size()) {
      break;
    }
    if(board[y - i][x + i] != player) {
      break;
    } else {
      counterRight++;
    }
  }
  for(int i = 1; ; i++) {
    if(y + i >= board.size() || int(x) - i < 0) {
      break;
    }
    if(board[y + i][x - i] != player) {
      break;
    } else {
      counterLeft++;
    }
  }
  if(counterLeft + counterRight + 1 >= 4) {
    return true;
  }

  return false;
}

OptionalPairNums
Board::findLowest() {
  std::pair<std::size_t, std::size_t> result;
  result.first = mousePosition.x / (boxSize + padding);

  if(result.first < 0 or result.first >= board[0].size()) {
    return {};
  } else {
    result.second = board.size();
    while(result.second > 0) {
      result.second--;
      if(board[result.second][result.first] == 0) {
        return result;
      }
    }
  }
  return {};
}


void Board::resetBoard() {
  std::fill(board.begin(), board.end(), std::vector<uint8_t>(board[0].size(), 0));
}

Board::Board(Game& game):
game(&game),
boxSize(80.f),
padding(10),
tryToSet(false),
ture(1),
playerCount(2) {
  board = std::vector(6, std::vector<uint8_t>(7, 0));
  colors = {
    sf::Color{0x40, 0x50, 0x60},
    sf::Color::Red,
    sf::Color::Green
  };

}