//
//  lesson2.cpp
//  cv_beginers
//
//  Created by sakiyamaK on 2016/07/31.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "basic.h"
#include "lesson2.hpp"

namespace lesson2{
  void section1(const std::string &fileName){
    
    std::cout << "section 1" << std::endl;
    
    //バリデーション
    if(fileName.empty() || fileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path" << std::endl;
      return;
    }
  
    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;
    
    auto color = *mat.ptr(mat.rows / 2, mat.cols / 2);
    std::cout << "filename = " << fileName << " center [b, g, r] = " << color << std::endl;
  }
  
  void section2(const std::string &fileName){

    std::cout << "section 2" << std::endl;
    
    //バリデーション
    if(fileName.empty() || fileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path" << std::endl;
      return;
    }
    
    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;
    
    cv::cvtColor(mat, mat, CV_BGR2HSV);

    auto color = *mat.ptr(mat.rows / 2, mat.cols / 2);
    std::cout << "filename = " << fileName << " center [h, s, v] = " << color << std::endl;
    
  }
  
  
  void section3(const std::string &saveFileName){

    std::cout << "section 3" << std::endl;
    
    //バリデーション
    if(saveFileName.empty() || saveFileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_save_file_full_path" << std::endl;
      return;
    }
    
    cv::Mat mat(256, 256, CV_8UC3);
    
    mat.forEach<cv::Vec3b>([](cv::Vec3b &p, const int * position) -> void {
      p[0] = 100;
      p[1] = 100;
      p[2] = 100;
    });
    
    cv::cvtColor(mat, mat, CV_HSV2BGR);
    
    if(!cv::imwrite(saveFileName, mat)){
      std::cout << "save error!! : " << saveFileName << std::endl;
    }

  }
  
  void section4(const std::string &fileName, const std::string &saveFileName){
    std::cout << "section 4" << std::endl;
    
    //バリデーション
    if(fileName.empty() || fileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path" << std::endl;
      return;
    }
    
    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;
    
    cv::cvtColor(mat, mat, CV_BGR2HSV);
    
    mat.forEach<cv::Vec3b>([](cv::Vec3b &p, const int * position) -> void {
      if(15 < p[0]){
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
      }
    });
    
    cv::cvtColor(mat, mat, CV_HSV2BGR);
    
    if(!cv::imwrite(saveFileName, mat)){
      std::cout << "save error!! : " << saveFileName << std::endl;
    }
    
  }

  void exec(int argc, const char * argv[]){
    int sectionNumber = atoi(argv[2]);
    
    switch (sectionNumber) {
      case 1:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        section1(inputFileFullPath);
        break;
      }
      case 2:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        section2(inputFileFullPath);
        break;
      }
      case 3:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        section3(inputFileFullPath);
        break;
      }
      case 4:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        std::string saveFileFullPath = std::string(argv[4]);
        section4(inputFileFullPath, saveFileFullPath);
        break;
      }
      default:
        //エラーハンドリング
        break;
    }

  }
}
