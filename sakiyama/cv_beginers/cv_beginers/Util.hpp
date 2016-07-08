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

namespace Util{
  cv::Mat loadImage(const std::string &fileName);
}
#endif /* Util_hpp */
