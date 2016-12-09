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

static struct GameManagerData {
  sf::RenderWindow *window;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<sf::Drawable *> listToDraw;
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
  data.listToDraw.push_back(object->sprite());
  data.collisionList.push_back(object);
}

void GameManager::AddActor(Actor *actor) {
  data.listToDraw.push_back(actor->sprite());
  data.collisionList.push_back(actor);
  data.dynamicCollisionList.push_back(actor);
}

void GameManager::AddEnemy(Actor *actor) {
  data.listToDraw.push_back(actor->sprite());
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

void GameManager::Draw() {
  //Update the collisions
  for (unsigned int i = 0; i < data.dynamicCollisionList.size(); ++i) {
    data.dynamicCollisionList.at(i)->updateCollisions();
  }

  //Draw the background
  //data.window->draw(data.backgroundSprite);

  //Draw
  for (unsigned int i = 0; i < data.listToDraw.size(); ++i) data.window->draw(*data.listToDraw.at(i));
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