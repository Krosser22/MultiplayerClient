/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "window.h"

sf::RenderWindow window;
std::vector<sf::Sprite *> listToDraw;

void Window::createWindow(int width, int height, const char *title) {
  window.create(sf::VideoMode(width, height), title);
  window.setFramerateLimit(60);
}

bool Window::isOpen() {
  bool opened = window.isOpen();
  
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }
  
  // Clear screen
  window.clear(sf::Color::White);

  return opened;
}

void Window::clear() {
  window.clear(sf::Color::White);
}

void Window::draw() {
  for(unsigned int i = 0; i < listToDraw.size(); ++i) {
    window.draw(*listToDraw.at(i));
  }
  window.display();
}

void Window::addToDraw(sf::Sprite *sprite) {
  listToDraw.push_back(sprite);
}