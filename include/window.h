/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __WINDOW_H__
#define __WINDOW_H__

class Window {
public:
  Window() {};
  ~Window() {};

  void createWindow(int width, int height, char *title);

  bool isOpen();
};

#endif //__WINDOW_H__