//
//  Util.cpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/07/09.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "Util.hpp"

namespace Util{
  cv::Mat loadImage(const std::string &fileName){
    cv::Mat rtn;
    rtn = cv::imread(fileName);
    if(rtn.empty()){
      std::cout << "invalid input_file_full_path : " << fileName << std::endl;
    }
    return rtn;
  }
}