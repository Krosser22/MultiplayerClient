#include <SFML/Window.hpp>
#include "game.h"
#include "gameManager.h"

void Game::start() {
  //Set the background
  GameManager::setBackground("map.png");

  //Set the ground
  ground.setTexture("ground.png");
  ground.setPositionY(240.0f);
  GameManager::addToDraw(&ground);

  //Set the player
  player.setTexture("player.png");
  GameManager::addToDraw(&player);
}

void Game::input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.moveY(-playerSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.moveY(playerSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.moveX(-playerSpeed);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.moveX(playerSpeed);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    Object *box = new Object();
    box->setTexture("box.png");
    box->setPosition(GameManager::mouseX(), GameManager::mouseY());
    objectList.push_back(*box);
    GameManager::addToDraw(box);
  }
}

void Game::update() {
  if (player.sprite()->getGlobalBounds().intersects(ground.sprite()->getGlobalBounds())) {
    printf("H");
  }
}

void Game::finish() {}