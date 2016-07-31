//
//  Util.hpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/07/09.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include <iostream>
#include <opencv2/opencv.hpp>

#define GET_P(mat, y, x) (y) * (mat).step + (x) * (mat).elemSize()

#define GET_COLOR(mat, i, j) (mat).ptr<cv::Vec3b>(i)[j]

#define SET_COLOR(mat, i, j, color) (mat).ptr<cv::Vec3b>(i)[j]=(color)

namespace Util {
  bool loadMat(const std::string &fileName, cv::Mat &mat, int flags=1);
}

#endif /* Util_hpp */
