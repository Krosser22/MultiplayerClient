/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#include "assets.h"

//Windows Paths
#define WIN_IMAGE_PATH "../../../../assets/images/"
#define WIN_SOUND_PATH "../../../../assets/sounds/"

//IOS Paths
#define IOS_IMAGE_PATH "assets/images/"
#define IOS_SOUND_PATH "assets/sounds/"

//Path on the different OS targets
#ifdef _WIN32
#define IMAGE_PATH WIN_IMAGE_PATH
#define SOUND_PATH WIN_SOUND_PATH
#elif __APPLE__
#define IMAGE_PATH IOS_IMAGE_PATH
#define SOUND_PATH IOS_SOUND_PATH
#endif

const char *ASSETS::ImagePath(const char *image) {
  std::string path = IMAGE_PATH;
  return path.append(image).c_str();
}

const char *ASSETS::SoundPath(const char *sound) {
  std::string path = SOUND_PATH;
  return path.append(sound).c_str();
}