/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "scenes/gameScene.h"
#include "UI/UIChat.h"
#include "UI/UIRank.h"
#include "UI/UIGroup.h"
#include "input.h"

void GameScene::start() {
  GameManager::SetBackground("background.png"); //Set the background

  //Set the limits
  {
    //Set the ground1
    ground1_.setTexture("ground.png");
    ground1_.setPosition(0.0f, 640.0f);
    GameManager::AddObject(&ground1_);

    //Set the ground2
    ground2_.setTexture("ground.png");
    ground2_.setPosition(0.0f, 576.0f);
    GameManager::AddObject(&ground2_);

    //Set the left wall
    leftWall_.setTexture("wall.png");
    leftWall_.setPosition(-64.0f, 0.0f);
    GameManager::AddObject(&leftWall_);

    //Set the right wall
    rightWall_.setTexture("wall.png");
    rightWall_.setPosition(960.0f, 0.0f);
    GameManager::AddObject(&rightWall_);

    //Set the roof
    roof_.setTexture("ground.png");
    roof_.setPosition(0.0f, -64.0f);
    GameManager::AddObject(&roof_);
  }

  //Set the platforms
  {
    switch (sceneData_->game) {
    case 1:
      //Left top
      platforms_.push_back(new Object());
      platforms_.at(0)->setTexture("platform.png");
      platforms_.at(0)->setPosition(0.0f, 300.0f);
      GameManager::AddObject(platforms_.at(0));

      //Middle bottom
      platforms_.push_back(new Object());
      platforms_.at(1)->setTexture("platform.png");
      platforms_.at(1)->setPosition(384.0f, 480.0f);
      GameManager::AddObject(platforms_.at(1));

      //Right top
      platforms_.push_back(new Object());
      platforms_.at(2)->setTexture("platform.png");
      platforms_.at(2)->setPosition(768.0f, 300.0f);
      GameManager::AddObject(platforms_.at(2));
      break;
    case 2:
      //Left bottom
      platforms_.push_back(new Object());
      platforms_.at(0)->setTexture("platform.png");
      platforms_.at(0)->setPosition(0.0f, 480.0f);
      GameManager::AddObject(platforms_.at(0));

      //Middle-left
      platforms_.push_back(new Object());
      platforms_.at(1)->setTexture("platform.png");
      platforms_.at(1)->setPosition(288.0f, 300.0f);
      GameManager::AddObject(platforms_.at(1));

      //Middle-right
      platforms_.push_back(new Object());
      platforms_.at(2)->setTexture("platform.png");
      platforms_.at(2)->setPosition(480.0f, 300.0f);
      GameManager::AddObject(platforms_.at(2));

      //Right bottom
      platforms_.push_back(new Object());
      platforms_.at(3)->setTexture("platform.png");
      platforms_.at(3)->setPosition(768.0f, 480.0f);
      GameManager::AddObject(platforms_.at(3));
      break;
    case 3:
      //Left top
      platforms_.push_back(new Object());
      platforms_.at(0)->setTexture("platform.png");
      platforms_.at(0)->setPosition(0.0f, 200.0f);
      GameManager::AddObject(platforms_.at(0));

      //Left top-mid
      platforms_.push_back(new Object());
      platforms_.at(1)->setTexture("platform.png");
      platforms_.at(1)->setPosition(192.0f, 264.0f);
      GameManager::AddObject(platforms_.at(1));

      //Middle bottom
      platforms_.push_back(new Object());
      platforms_.at(2)->setTexture("platform.png");
      platforms_.at(2)->setPosition(384.0f, 450.0f);
      GameManager::AddObject(platforms_.at(2));

      //Right top-mid
      platforms_.push_back(new Object());
      platforms_.at(3)->setTexture("platform.png");
      platforms_.at(3)->setPosition(576.0f, 264.0f);
      GameManager::AddObject(platforms_.at(3));

      //Right top
      platforms_.push_back(new Object());
      platforms_.at(4)->setTexture("platform.png");
      platforms_.at(4)->setPosition(768.0f, 200.0f);
      GameManager::AddObject(platforms_.at(4));
      break;
    default:
      //Left top
      platforms_.push_back(new Object());
      platforms_.at(0)->setTexture("platform.png");
      platforms_.at(0)->setPosition(0.0f, 480.0f);
      GameManager::AddObject(platforms_.at(0));

      //Midle bottom
      platforms_.push_back(new Object());
      platforms_.at(1)->setTexture("platform.png");
      platforms_.at(1)->setPosition(384.0f, 300.0f);
      GameManager::AddObject(platforms_.at(1));

      //Right top
      platforms_.push_back(new Object());
      platforms_.at(2)->setTexture("platform.png");
      platforms_.at(2)->setPosition(768.0f, 480.0f);
      GameManager::AddObject(platforms_.at(2));
      break;
    }
  }

  //Set the player
  sceneData_->player.setTexture("player.png");
  sceneData_->player.setLife(sceneData_->player.maxLife());
  sceneData_->player.setPosition(460.0f, 100.0f);
  GameManager::AddActor(&sceneData_->player);

  sceneData_->playing = true;
  UIChat::Clear();

  //Add the enemies
  for (unsigned int i = 0; i < sceneData_->enemies.size(); ++i) {
    GameManager::AddObject(sceneData_->enemies.at(i));
    sceneData_->enemies.at(i)->setLife(sceneData_->enemies.at(i)->maxLife());
    sceneData_->enemies.at(i)->setTexture("enemy.png");
  }
}

void GameScene::input() {
  if (GameManager::WindowHasFocus()) {
    if (MYINPUT::IsKeyPressed(INPUT_KEY_ENTER)) {
      chatEnable_ = !chatEnable_;
    }

    if (!chatEnable_) {
      //Player movement
      if (!sceneData_->player.isDead()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) sceneData_->player.crouch();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) sceneData_->player.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) sceneData_->player.moveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) sceneData_->player.jump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) sceneData_->player.interact();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) sceneData_->player.action();
      }

      //Spawn test
      /*static std::vector<Object *> objectList_;
      if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        Object *box = new Object();
        box->setTexture("box.png");
        box->setPosition(GameManager::MouseX(), GameManager::MouseY());
        objectList_.push_back(box);
        GameManager::AddObject(box);
      }*/

      //Escape to logout the game
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        SceneManager::ChangeScene("Login");
        NetworkManager::Logout();
      }
    }
  }
}

void GameScene::update() {
  UIChat::Draw(chatEnable_);
  UIRank::Draw(/*sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)*/);
  UIGroup::Draw();
}

void GameScene::finish() {
  sceneData_->bullets.clear();
  //sceneData_->enemies.clear();
  GameManager::ClearDrawList();
}