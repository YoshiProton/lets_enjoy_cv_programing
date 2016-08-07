//
//  main.cpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/06/26.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "basic.h"

void info(){
  std::cout << "OpenCV version : " << CV_VERSION << std::endl;
  std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
  std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
  std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;
}


bool validate(int argc, const char * argv[]){
  bool rtn = true;
  
  if(argc < 3){
    std::cout << "invalid input" << std::endl;
    std::cout << "cv_beginers lesson_number section_number ..." << std::endl;
    rtn = false;
  }
  
  return rtn;
}


int main(int argc, const char * argv[]) {

#if DEBUG
  std::string dir = "/Users/sakiyamaK/Documents/event/lets_enjoy_cv_programing/sakiyama/img";
  
  std::string fullPath1;
  std::string fullPath2;
  std::string saveFullPath;
  
  fullPath1 = dir + "/" + "test_a.jpg";
  fullPath2 = dir + "/" + "test_b.jpg";
  
  saveFullPath = dir + "/" + "blend1.jpg";
  SameImageFile::alphaBlend1(fullPath1, fullPath2, 0.5, saveFullPath);
  
  saveFullPath = dir + "/" + "blend2.jpg";
  SameImageFile::alphaBlend2(fullPath1, fullPath2, 0.5, saveFullPath);
  
  
  saveFullPath = dir + "/" + "blend2.jpg";
  SameImageFile::alphaBlend3(fullPath1, fullPath2, saveFullPath);

  saveFullPath = dir + "/" + "emboss.jpg";
  SameImageFile::emboss(fullPath2, 10, 10, saveFullPath);

  saveFullPath = dir + "/" + "chromakey.jpg";
  SameImageFile::chromakey(fullPath1, fullPath2, saveFullPath);

#else
  
  if(!validate(argc, argv)){
    return 0;
  }
  
  int lessonNumber = atoi(argv[1]);
  
  switch (lessonNumber) {
    case 1:
      lesson1::exec(argc, argv);
      break;
    case 2:
      lesson2::exec(argc, argv);
      break;
    default:
      break;
  }
#endif
  return 0;
}
