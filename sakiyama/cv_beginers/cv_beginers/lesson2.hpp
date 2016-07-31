//
//  lesson2.hpp
//  cv_beginers
//
//  Created by sakiyamaK on 2016/07/31.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#ifndef lesson2_hpp
#define lesson2_hpp

#include <iostream>


namespace lesson2{
#if DEBUG
  void section1(const std::string &fileName);
  void section2(const std::string &fileName);
  void section3(const std::string &fileName);
  void section4(const std::string &fileName, const std::string &saveFileName);
#endif
  void exec(int argc, const char * argv[]);
}


#endif /* lesson2_hpp */
