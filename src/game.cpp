#include <SFML/Window.hpp>
#include "game.h"
#include "gameManager.h"

void Game::start() {
  //Set the background
  //GameManager::setBackground("map.png");

  //Set the ground
  ground.setTexture("ground.png");
  ground.setPosition(0.0f, 640.0f);
  GameManager::addObject(&ground);

  //Set the ground
  platformLeft.setTexture("platform.png");
  platformLeft.setPosition(0.0f, 480.0f);
  GameManager::addObject(&platformLeft);

  //Set the ground
  platformCenter.setTexture("platform.png");
  platformCenter.setPosition(384.0f, 300.0f);
  GameManager::addObject(&platformCenter);

  //Set the ground
  platformRight.setTexture("platform.png");
  platformRight.setPosition(768.0f, 480.0f);
  GameManager::addObject(&platformRight);

  //Set the player
  actor.setTexture("player.png");
  ground.setPosition(0.0f, 600.0f);
  GameManager::addActor(&actor);
}

void Game::input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) actor.jump();
  else actor.stopJumping();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) actor.crouch();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) actor.moveLeft();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) actor.moveRight();

  if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    Object *box = new Object();
    box->setTexture("box.png");
    box->setPosition(GameManager::mouseX(), GameManager::mouseY());
    objectList.push_back(*box);
    GameManager::addObject(box);
  }
}

void Game::update() {}

void Game::finish() {}