/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "managers/gameManager.h"
#include "managers/networkManager.h"
#include "managers/sceneManager.h"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 704

static struct GameManagerData {
  sf::RenderWindow *window;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<Object *> listToDraw;
  std::vector<Bullet *> bulletsListToDraw;
  std::vector<Object *> collisionList;
  std::vector<Actor *> dynamicCollisionList;
  sf::Clock clock;
  sf::Font font;
} data;

void GameManager::Start(sf::RenderWindow *window) {
  //Set the window
  data.window = window;

  //Set the project default font
  if (!data.font.loadFromFile(ASSETS::FontPath("arial.ttf"))) {
    printf("ERROR loading the default font");
  }
}

void GameManager::Finish() {
  //Empty the lists of objects
  data.listToDraw.clear();
  data.collisionList.clear();
  data.dynamicCollisionList.clear();
  RemoveBackground();
}

void GameManager::SetBackground(const char *imagePath) {
  data.backgroundTexture.loadFromFile(ASSETS::ImagePath(imagePath));
  data.backgroundSprite.setTexture(data.backgroundTexture);
  data.backgroundSprite.setOrigin(0.0f, 0.0f);
  data.backgroundSprite.setPosition(0.0f, 0.0f);
}

void GameManager::RemoveBackground() {
  data.backgroundTexture.create(1, 1);
  data.backgroundSprite.setTexture(data.backgroundTexture);
}

void GameManager::AddObject(Object *object) {
  data.listToDraw.push_back(object);
  data.collisionList.push_back(object);
}

void GameManager::AddActor(Actor *actor) {
  data.listToDraw.push_back(actor);
  data.collisionList.push_back(actor);
  data.dynamicCollisionList.push_back(actor);
}

void GameManager::AddEnemy(Actor *actor) {
  data.listToDraw.push_back(actor);
}

void GameManager::AddBullet(Bullet *bullet) {
  if (data.bulletsListToDraw.size() > 30) {
    data.bulletsListToDraw.erase(data.bulletsListToDraw.begin());
  }
  data.bulletsListToDraw.push_back(bullet);
}

void GameManager::RemoveEnemy(Actor *actor) {
  int pos = -1;
  for (unsigned int i = 0; i < data.listToDraw.size(); ++i) {
    if (data.listToDraw.at(i)->ID() == actor->ID()) {
      pos = i;
    }
  }
  data.listToDraw.erase(data.listToDraw.begin() + pos);
}

void GameManager::RemoveBullet(std::string ownerID, std::string ID) {
  int pos = -1;
  for (unsigned int i = 0; i < data.bulletsListToDraw.size(); ++i) {
    if (data.bulletsListToDraw.at(i)->ID() == ID && data.bulletsListToDraw.at(i)->ownerID == ownerID) {
      pos = i;
    }
  }
  data.bulletsListToDraw.erase(data.bulletsListToDraw.begin() + pos);
}

void GameManager::ClearDrawList() {
  data.listToDraw.clear();
  data.collisionList.clear();
  data.dynamicCollisionList.clear();
  RemoveBackground();
}

bool GameManager::IsOpen() {
  bool opened = data.window->isOpen();

  //Clear screen
  data.window->clear(sf::Color::White);

  return opened;
}

void GameManager::CloseWindow() {
  data.window->close();
}

bool GameManager::WindowHasFocus() {
  return data.window->hasFocus();
}

void checkBulletCollision(Actor *actor) {
  static sf::FloatRect intersection;
  bool collision = false;
  std::vector<Bullet *> *bullets = SceneManager::getBullets();
  
  int posCollision = -1;
  for (unsigned int i = 0; i < bullets->size() && !collision; ++i) {
    if (bullets->at(i)->ownerID != actor->ID()) {
      if (actor->sprite()->getGlobalBounds().intersects(bullets->at(i)->sprite()->getGlobalBounds(), intersection)) {
        collision = true;
        posCollision = i;
      }
    }
  }

  if (collision) {
    std::string msg = "Hit:";
    msg.append(actor->ID()).append(":");
    msg.append(bullets->at(posCollision)->ownerID).append(":");
    msg.append(bullets->at(posCollision)->ID()).append(":");
    msg.append(std::to_string(bullets->at(posCollision)->damage));
    NetworkManager::SendTCPMsgToServer(msg.c_str());
    bullets->erase(bullets->begin() + posCollision);
  }
}

void GameManager::Draw() {
  //Update bullet movement
  std::vector<Bullet *> *bullets = SceneManager::getBullets();
  for (unsigned int i = 0; i < bullets->size(); ++i) {
    Bullet *bullet = bullets->at(i);
    float X = bullet->positionX() + bullet->speedX;
    float Y = bullet->positionY() + bullet->speedY;
    bullet->setPosition(X * velocity, Y * velocity);
  }

  //Update the collisions
  for (unsigned int i = 0; i < data.dynamicCollisionList.size(); ++i) {
    data.dynamicCollisionList.at(i)->updateCollisions();
  }

  checkBulletCollision(SceneManager::getPlayer());

  //Draw the background
  data.window->draw(data.backgroundSprite);

  //Draw
  for (unsigned int i = 0; i < data.listToDraw.size(); ++i) data.window->draw(*data.listToDraw.at(i)->sprite());
  for (unsigned int i = 0; i < data.bulletsListToDraw.size(); ++i) data.window->draw(*data.bulletsListToDraw.at(i)->sprite());
}

float GameManager::MouseX() {
  return (float)sf::Mouse::getPosition(*data.window).x;
}

float GameManager::MouseY() {
  return (float)sf::Mouse::getPosition(*data.window).y;
}

const int GameManager::WindowWidth() {
  return WINDOW_WIDTH;
}

const int GameManager::WindowHeight() {
  return WINDOW_HEIGHT;
}

bool GameManager::CheckCollision(Actor *actor) {
  static sf::FloatRect intersection;
  bool collision = false;
  for (unsigned int i = 0; i < data.collisionList.size() && !collision; ++i) {
    if (actor != data.collisionList.at(i)) {
      if (actor->sprite()->getGlobalBounds().intersects(data.collisionList.at(i)->sprite()->getGlobalBounds(), intersection)) {
        collision = true;
      }
    }
  }
  return collision;
}

sf::Time GameManager::Time() {
  return data.clock.getElapsedTime();
}

sf::Font *GameManager::Font() {
  return &data.font;
}