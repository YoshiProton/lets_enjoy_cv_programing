//
//  Util.cpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/07/09.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "Util.hpp"
#include <opencv2/opencv.hpp>

namespace Util {
  bool loadMat(const std::string &fileName, cv::Mat &mat, int flags){
    mat = cv::imread(fileName, flags);
    if(mat.empty() || mat.rows == 0 || mat.cols == 0){
      std::cout << "invalid input_file_full_path : " << fileName << std::endl;
      return false;
    }
    return true;
  }
}