/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __ASSETS_H__
#define __ASSETS_H__

#include <string>

namespace ASSETS {
  //@param image: The path from the assets/images folder
  //@return: the correct path (it will be different on Windows or IOS)
  const char *ImagePath(const char *image);

  //@param sound: The path from the assets/sounds folder
  //@return: the correct path (it will be different on Windows or IOS)
  const char *SoundPath(const char *sound);

  //@param font: The path from the assets/fonts folder
  //@return: the correct path (it will be different on Windows or IOS)
  std::string *FontPath(const char *font);
}

#endif //__ASSETS_H__