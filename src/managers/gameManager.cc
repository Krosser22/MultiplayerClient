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
#include "server.h"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 704

struct GameManagerData {
  sf::RenderWindow *window;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<sf::Drawable *> listToDraw;
  std::vector<Object *> collisionList;
  std::vector<Actor *> dynamicCollisionList;
  sf::Clock clock;
  sf::Font font;
} gameManagerData;

void GameManager::Start(sf::RenderWindow *window) {
  //Set the window
  gameManagerData.window = window;

  //Set the project default font
  if (!gameManagerData.font.loadFromFile(ASSETS::FontPath("arial.ttf"))) {
    printf("ERROR loading the default font");
  }
}

void GameManager::Finish() {
  //Empty the lists of objects
  gameManagerData.listToDraw.clear();
  gameManagerData.collisionList.clear();
  gameManagerData.dynamicCollisionList.clear();
}

void GameManager::SetBackground(const char *imagePath) {
  gameManagerData.backgroundTexture.loadFromFile(ASSETS::ImagePath(imagePath));
  gameManagerData.backgroundSprite.setTexture(gameManagerData.backgroundTexture);
  gameManagerData.backgroundSprite.setOrigin(0.0f, 0.0f);
  gameManagerData.backgroundSprite.setPosition(0.0f, 0.0f);
}

void GameManager::RemoveBackground() {
  gameManagerData.backgroundTexture.create(1, 1);
  gameManagerData.backgroundSprite.setTexture(gameManagerData.backgroundTexture);
}

void GameManager::AddObject(Object *object) {
  gameManagerData.listToDraw.push_back(object->sprite());
  gameManagerData.collisionList.push_back(object);
}

void GameManager::AddActor(Actor *actor) {
  gameManagerData.listToDraw.push_back(actor->sprite());
  gameManagerData.collisionList.push_back(actor);
  gameManagerData.dynamicCollisionList.push_back(actor);
}

void GameManager::RemoveObject(Object *object) {
  printf("Empty function: removeObject()\n");
}

void GameManager::ClearDrawList() {
  printf("Empty function: clearDrawList()\n");
}

bool GameManager::IsOpen() {
  bool opened = gameManagerData.window->isOpen();

  //Clear screen
  gameManagerData.window->clear(sf::Color::White);

  return opened;
}

void GameManager::CloseWindow() {
  gameManagerData.window->close();
}

bool GameManager::WindowHasFocus() {
  return gameManagerData.window->hasFocus();
}

void GameManager::Draw() {
  //Update the collisions
  for (unsigned int i = 0; i < gameManagerData.dynamicCollisionList.size(); ++i) {
    gameManagerData.dynamicCollisionList.at(i)->updateCollisions();
  }

  //Draw the background
  gameManagerData.window->draw(gameManagerData.backgroundSprite);

  //Draw
  for (unsigned int i = 0; i < gameManagerData.listToDraw.size(); ++i) gameManagerData.window->draw(*gameManagerData.listToDraw.at(i));
}

float GameManager::MouseX() {
  return (float)sf::Mouse::getPosition(*gameManagerData.window).x;
}

float GameManager::MouseY() {
  return (float)sf::Mouse::getPosition(*gameManagerData.window).y;
}

int GameManager::WindowWidth() {
  return WINDOW_WIDTH;
}

int GameManager::WindowHeight() {
  return WINDOW_HEIGHT;
}

bool GameManager::CheckCollision(Actor *actor) {
  static sf::FloatRect intersection;
  bool collision = false;
  for (unsigned int i = 0; i < gameManagerData.collisionList.size() && !collision; ++i) {
    if (actor != gameManagerData.collisionList.at(i)) {
      if (actor->sprite()->getGlobalBounds().intersects(gameManagerData.collisionList.at(i)->sprite()->getGlobalBounds(), intersection)) {
        collision = true;
      }
    }
  }
  return collision;
}

sf::Time GameManager::Time() {
  return gameManagerData.clock.getElapsedTime();
}

sf::Font *GameManager::Font() {
  return &gameManagerData.font;
}