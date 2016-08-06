//
//  SameImageFile.hpp
//  cv_beginers
//
//  Created by sakiyamaK on 2016/08/03.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#ifndef SameImageFile_hpp
#define SameImageFile_hpp

#include <iostream>

namespace SameImageFile {
  void alphaBlend1(std::string &fileFullPath1, std::string &fileFullPath2, double alpha,
                   std::string &saveFullPath);
  //フルスクラッチ版
  void alphaBlend2(std::string &fileFullPath1, std::string &fileFullPath2, double alpha,
                   std::string &saveFullPath);

  void alphaBlend3(std::string &fileFullPath1, std::string &fileFullPath2,
                   std::string &saveFullPath);
  
  void emboss(std::string &fileFullPath, int moveX, int moveY, std::string &saveFullPath);
  
  void chromakey(std::string &fileFullPath1, std::string &fileFullPath2,
                 std::string &saveFullPath);
}
#endif /* SameImageFile_hpp */
