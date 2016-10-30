/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include <SFML/Graphics.hpp>
#include "gameManager.h"

struct GameManagerData {
  sf::RenderWindow window;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<sf::Sprite *> listToDraw;
} data;

void GameManager::start() {
  data.window.create(sf::VideoMode(960, 704), "Multiplayer");
  data.window.setFramerateLimit(60);
}

void GameManager::finish() {}

void GameManager::setBackground(const char *imagePath) {
  data.backgroundTexture.loadFromFile(ASSETS::ImagePath(imagePath));
  data.backgroundSprite.setTexture(data.backgroundTexture);
  data.backgroundSprite.setOrigin(0.0f, 0.0f);
  data.backgroundSprite.setPosition(0.0f, 0.0f);
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

  //Clear screen
  data.window.clear(sf::Color::White);

  return opened;
}

void GameManager::draw() {
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