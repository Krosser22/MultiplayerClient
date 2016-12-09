/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/gameScene.h"

void GameScene::start() {
  GameManager::SetBackground("background.png"); //Set the background

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
  sceneData_->player.setTexture("player.png");
  sceneData_->player.setPosition(0.0f, 600.0f);
  GameManager::AddActor(&sceneData_->player);

  //Set the enemy
  /*sceneData_.enemies[0].setTexture("enemy.png");
  sceneData_.enemies[0].setPosition(800.0f, 600.0f);
  GameManager::AddActor(&sceneData_.enemies[0]);*/

  sceneData_->playing = true;
}

void GameScene::input() {
  if (GameManager::WindowHasFocus()) {
    //Player movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) sceneData_->player.crouch();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) sceneData_->player.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) sceneData_->player.moveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) sceneData_->player.jump();

    //Spawn test
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      static std::vector<Object> objectList_;
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