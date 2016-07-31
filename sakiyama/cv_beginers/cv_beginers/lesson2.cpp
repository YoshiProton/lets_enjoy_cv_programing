//
//  lesson2.cpp
//  cv_beginers
//
//  Created by sakiyamaK on 2016/07/31.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "lesson2.hpp"
#include "Util.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

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
    
    auto color = GET_COLOR(mat, mat.rows / 2, mat.cols / 2);
    std::cout << "filename = " << fileName << " center [r, g, b] = " << color << std::endl;
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

    auto color = GET_COLOR(mat, mat.rows / 2, mat.cols / 2);
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

  void exec(int argc, const char * argv[]);
}
