//
//  lesson3.cpp
//  cv_beginers
//
//  Created by sakiyamaK on 2016/08/21.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "basic.h"
#include "lesson3.hpp"

namespace lesson3 {
  //平均化フィルタ
  void section1(const std::string &fileName, bool isUseOpenCV = true){
    std::cout << "section 1" << std::endl;

    if(isUseOpenCV){
      
      //バリデーション
      if(fileName.empty() || fileName.length() == 0){
        std::cout << "invalid input" << std::endl;
        return;
      }
      
      cv::Mat mat;
      if(!Util::loadMat(fileName, mat)) return;
      
      cv::blur(mat, mat, {3,3});
      
    }
    else{
      
    }
  }
//  void section2(const std::string &fileName);
//  void section3(const std::string &fileName);
//  void section4(const std::string &fileName, const std::string &saveFileName);

}