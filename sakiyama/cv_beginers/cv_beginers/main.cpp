//
//  main.cpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/06/26.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "lesson1.hpp"


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
  std::cout << "OpenCV version : " << CV_VERSION << std::endl;
  std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
  std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
  std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;
  
  std::string exec = "cv_beginers";
  std::string lessonNumber = "1";
  std::string sectionNumber = "2";
  
  std::string dir = "/Users/sakiyamaK/Documents/study/lets_enjoy_cv_programing/_lesson/20160709";
  
  std::string fileName = "lena.jpg";
  std::string fullPath = dir + "/" + fileName;
  
  std::string saveFileName = "lena_gray.jpg";
  std::string saveFullPath = dir + "/" + saveFileName;
  
  const char *input[] = {exec.c_str(), lessonNumber.c_str(),
    sectionNumber.c_str(), fullPath.c_str(), saveFullPath.c_str()};
  
  lesson1::exec(5, input);
#else
  
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
#endif
  return 0;
}
