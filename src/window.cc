/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include <SFML/Graphics.hpp>

static sf::RenderWindow window;

void Window::createWindow(int width, int height, char *title) {
  window.create(sf::VideoMode(width, height), title);
  window.setFramerateLimit(60);
}

bool Window::isOpen() {
  return window.isOpen();
}