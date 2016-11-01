#include <SFML/Window.hpp>
#include "game.h"
#include "gameManager.h"

void Game::start() {
  //Set the background
  GameManager::setBackground("map.png");

  //Set the ground
  ground.setTexture("ground.png");
  ground.setPositionY(640.0f);
  GameManager::addObject(&ground);

  //Set the player
  player.setTexture("player.png");
  GameManager::addObject(&player);
}

void Game::input() {
  float newX = 0.0f, newY = 0.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) newY = -playerSpeed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) newY = playerSpeed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) newX = -playerSpeed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) newX = playerSpeed;
  player.moveX(newX);
  player.moveY(newY);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    Object *box = new Object();
    box->setTexture("box.png");
    box->setPosition(GameManager::mouseX(), GameManager::mouseY());
    objectList.push_back(*box);
    GameManager::addObject(box);
  }
}

void Game::update() {
  if (player.sprite()->getGlobalBounds().intersects(ground.sprite()->getGlobalBounds())) {
    printf("H");
  }
}

void Game::finish() {}