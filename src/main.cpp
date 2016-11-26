/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "gameManager.h"
#include "game.h"
#include "server.h"

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

  //Finish the game
  game.finish();
  GameManager::finish();
  return 0;
}