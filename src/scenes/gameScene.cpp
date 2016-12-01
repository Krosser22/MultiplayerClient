/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Window.hpp>
#include "scenes/gameScene.h"
#include "managers/gameManager.h"
#include "managers/sceneManager.h"

void GameScene::start() {
  //Set the background
  GameManager::SetBackground("background.png");

  //Set the ground
  ground_.setTexture("ground.png");
  ground_.setPosition(0.0f, 640.0f);
  GameManager::AddObject(&ground_);

  //Set the ground
  platformLeft_.setTexture("platform.png");
  platformLeft_.setPosition(0.0f, 480.0f);
  GameManager::AddObject(&platformLeft_);

  //Set the ground
  platformCenter_.setTexture("platform.png");
  platformCenter_.setPosition(384.0f, 300.0f);
  GameManager::AddObject(&platformCenter_);

  //Set the ground
  platformRight_.setTexture("platform.png");
  platformRight_.setPosition(768.0f, 480.0f);
  GameManager::AddObject(&platformRight_);

  //Set the player
  actor_.setTexture("player.png");
  ground_.setPosition(0.0f, 600.0f);
  GameManager::AddActor(&actor_);
}

void GameScene::input() {
  if (GameManager::WindowHasFocus()) {
    //Player movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) actor_.crouch();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) actor_.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) actor_.moveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) actor_.jump();
    else actor_.stopJumping();

    //Spawn test
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      Object *box = new Object();
      box->setTexture("box.png");
      box->setPosition(GameManager::MouseX(), GameManager::MouseY());
      objectList_.push_back(*box);
      GameManager::AddObject(box);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      SceneManager::ChangeScene("Login");
    }
  }
}

void GameScene::update() {}

void GameScene::finish() {}