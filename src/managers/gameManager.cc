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

struct GameManagerData {
  sf::RenderWindow window;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<sf::Sprite *> listToDraw;
  std::vector<Object *> collisionList;
  std::vector<Actor *> dynamicCollisionList;
  sf::Clock clock;
} data;

void GameManager::start() {
  //Create the window with a default values
  data.window.create(sf::VideoMode(960, 704), "Multiplayer");
  data.window.setFramerateLimit(60);

  //Starts the connection with the server
  Server::startClient();
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
  data.listToDraw.push_back((sf::Sprite *) object->sprite());
  data.collisionList.push_back(object);
}

void GameManager::addActor(Actor *actor) {
  data.listToDraw.push_back((sf::Sprite *) actor->sprite());
  data.collisionList.push_back(actor);
  data.dynamicCollisionList.push_back(actor);
}

void GameManager::removeObject(Object *object) {}

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