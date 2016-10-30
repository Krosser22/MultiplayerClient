/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "gameManager.h"

struct GameManagerData {
  sf::RenderWindow window;
  std::vector<sf::Sprite *> listToDraw;
  b2Vec2 gravity;
  b2World *world;
  GameManagerData() {
    gravity.x = 0.0f;
    gravity.y = 9.8f;
    world = new b2World(gravity);
  }
} data;

void GameManager::start() {
  data.window.create(sf::VideoMode(960, 704), "Multiplayer");
  data.window.setFramerateLimit(60);
}

void GameManager::finish() {
  delete data.world;
}

void GameManager::addToDraw(Object *object) {
  data.listToDraw.push_back((sf::Sprite *)object->sprite());
}

bool GameManager::isOpen() {
  bool opened = data.window.isOpen();

  sf::Event event;
  while (data.window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) data.window.close();
  }

  // Clear screen
  data.window.clear(sf::Color::White);

  /** Simulate the world */
  data.world->Step(1 / 60.f, 8, 3);

  return opened;
}

void GameManager::draw() {
  for (unsigned int i = 0; i < data.listToDraw.size(); ++i) {
    data.window.draw(*data.listToDraw.at(i));
  }
  data.window.display();
}