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
#define WIN_FONT_PATH "../../../../assets/fonts/"

//IOS Paths
#define IOS_IMAGE_PATH "assets/images/"
#define IOS_SOUND_PATH "assets/sounds/"
#define IOS_FONT_PATH "assets/fonts/"

//Path on the different OS targets
#ifdef _WIN32
#define IMAGE_PATH WIN_IMAGE_PATH
#define SOUND_PATH WIN_SOUND_PATH
#define FONT_PATH WIN_FONT_PATH
#elif __APPLE__
#define IMAGE_PATH IOS_IMAGE_PATH
#define SOUND_PATH IOS_SOUND_PATH
#define FONT_PATH IOS_FONT_PATH
#endif

static std::string imagePath;
const char *ASSETS::ImagePath(const char *image) {
  imagePath = IMAGE_PATH;
  return imagePath.append(image).c_str();
}

static std::string soundPath;
const char *ASSETS::SoundPath(const char *sound) {
  soundPath = SOUND_PATH;
  return soundPath.append(sound).c_str();
}

static std::string fontPath;
std::string *ASSETS::FontPath(const char *font) {
  fontPath = FONT_PATH;
  return &fontPath.append(font);
}