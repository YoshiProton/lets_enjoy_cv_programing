//
//  lesson1.hpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/07/09.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#ifndef lesson1_hpp
#define lesson1_hpp

#include <iostream>


namespace lesson1{
#if DEBUG
  void section1(const std::string &fileName);
  void section2(const std::string &fileName, const std::string &saveFileName);
  void section3(const std::string &fileName, const std::string &saveFileName);
  void section4(const std::string &fileName, const std::string &saveFileName);
  void section5(const std::string &fileName, const std::string &saveFileName);
#endif
  void exec(int argc, const char * argv[]);  
}

#endif /* lesson1_hpp */
