//
//  main.cpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/06/26.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include <iostream>
#include "lesson1.hpp"

bool validate(int argc, const char * argv[]){
  bool rtn = true;
  
  if(argc < 3){
    std::cout << "invalid input" << std::endl;
    std::cout << "exec lesson_number section_number ..." << std::endl;
    rtn = false;
  }
  
  return rtn;
}


int main(int argc, const char * argv[]) {
    
  if(!validate(argc, argv)){
    return 0;
  }
  
  int lessonNumber = atoi(argv[1]);
  
  switch (lessonNumber) {
    case 1:
      lesson1::exec(argc, argv);
      break;
    default:
      break;
  }
  
  return 0;
}
