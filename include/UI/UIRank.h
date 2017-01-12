/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: S6106112@live.tees.ac.uk   /////
*** /////            2016-2017             /////
*** ////////////////////////////////////////////
**/

#ifndef __UI_RANK_H__
#define __UI_RANK_H__

#include <string>

namespace UIRank {
  //Draw the Rank
  void Draw(bool open = true);

  //Add a data to the Rank
  void AddData(int points, std::string nick);

  //Clear the ranking data
  void Clear();
}

#endif //__UI_RANK_H__