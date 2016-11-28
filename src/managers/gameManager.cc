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
  sf::RenderWindow window;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<sf::Drawable *> listToDraw;
  std::vector<Object *> collisionList;
  std::vector<Actor *> dynamicCollisionList;
  sf::Clock clock;
  sf::Font font;
} data;

void GameManager::start() {
  //Create the window with a default values
  data.window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Multiplayer");
  data.window.setFramerateLimit(60);

  //Starts the connection with the server
  Server::startClient();

  //Set the project default font
  if (!data.font.loadFromFile(ASSETS::FontPath("arial.ttf"))) {
    printf("ERROR loading the default font");
  }
}

void GameManager::finish() {
  //Finish the connection with the server
  Server::finishClient();

  //Empty the lists of objects
  data.listToDraw.clear();
  data.collisionList.clear();
  data.dynamicCollisionList.clear();
}

void GameManager::setBackground(const char *imagePath) {
  data.backgroundTexture.loadFromFile(ASSETS::ImagePath(imagePath));
  data.backgroundSprite.setTexture(data.backgroundTexture);
  data.backgroundSprite.setOrigin(0.0f, 0.0f);
  data.backgroundSprite.setPosition(0.0f, 0.0f);
}

void GameManager::removeBackground() {
  data.backgroundTexture.create(1, 1);
  data.backgroundSprite.setTexture(data.backgroundTexture);
}

void GameManager::addObject(Object *object) {
  data.listToDraw.push_back(object->sprite());
  data.collisionList.push_back(object);
}

void GameManager::addActor(Actor *actor) {
  data.listToDraw.push_back(actor->sprite());
  data.collisionList.push_back(actor);
  data.dynamicCollisionList.push_back(actor);
}

void GameManager::addButton(Button *button) {
  data.listToDraw.push_back(button->sprite());
  data.listToDraw.push_back(button->getText());
}

void GameManager::addText(Text *text) {
  data.listToDraw.push_back(text->sprite());
  data.listToDraw.push_back(text->getText());
}

void GameManager::removeObject(Object *object) {
  printf("Empty function: removeObject()\n");
}

void GameManager::clearDrawList() {
  printf("Empty function: clearDrawList()\n");
}

bool GameManager::isOpen() {
  bool opened = data.window.isOpen();

  //Events
  sf::Event event;
  while (data.window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) data.window.close();
  }

  //Clear screen
  data.window.clear(sf::Color::White);

  return opened;
}

void GameManager::closeWindow() {
  data.window.close();
}

bool GameManager::windowHasFocus() {
  return data.window.hasFocus();
}

void GameManager::draw() {
  //Update the collisions
  for (unsigned int i = 0; i < data.dynamicCollisionList.size(); ++i) {
    data.dynamicCollisionList.at(i)->updateCollisions();
  }

  //Draw the background
  data.window.draw(data.backgroundSprite);

  //Draw
  for (unsigned int i = 0; i < data.listToDraw.size(); ++i) data.window.draw(*data.listToDraw.at(i));

  //Display the buffer on the screen
  data.window.display();
}

float GameManager::mouseX() {
  return (float)sf::Mouse::getPosition(data.window).x;
}

float GameManager::mouseY() {
  return (float)sf::Mouse::getPosition(data.window).y;
}

float GameManager::getWindowWidth() {
  return WINDOW_WIDTH;
}

float GameManager::getWindowHeight() {
  return WINDOW_HEIGHT;
}

bool GameManager::checkCollision(Actor *actor) {
  sf::FloatRect intersection;
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

sf::Time GameManager::getTime() {
  return data.clock.getElapsedTime();
}

sf::Font *GameManager::getFont() {
  return &data.font;
}