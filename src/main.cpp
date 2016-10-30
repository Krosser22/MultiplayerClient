#include "gameManager.h"
#include "game.h"

int main(int argc, char **argv) {
  //Starts the GameManager
  GameManager::start();

  //Starts the Game
  Game game;
  game.start();

  while (GameManager::isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    game.input();
    game.update();
    GameManager::draw();
  }
  game.finish();
  GameManager::finish();
  return EXIT_SUCCESS;
}