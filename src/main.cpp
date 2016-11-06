#include "gameManager.h"
#include "game.h"
#include "server.h"

#define SERVER_ON

////////////////////////////////////////////
//
#ifdef SERVER_ON
int main(int argc, char **argv) {
  //Starts the Server
  Server server;
  server.start();

  //Update the Server
  while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    server.update();
  }

  //Finish the server
  server.finish();
  return 0;
}
//
////////////////////////////////////////////

#else

////////////////////////////////////////////
//
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
  return 0;
}
#endif
//
////////////////////////////////////////////