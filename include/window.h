/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Window {
public:
  Window() {};
  ~Window() {};

  void createWindow(int width, int height, const char *title);

  bool isOpen();
  
  void clear();
  
  void draw();
  
  void addToDraw(sf::Sprite *sprite);
};

#endif //__WINDOW_H__