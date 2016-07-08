//
//  lesson1.cpp
//  cv_beginers
//
//  Created by 崎山 圭 on 2016/07/09.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "lesson1.hpp"
#include "Util.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

namespace lesson1 {

  bool validate(int argc, const char * argv[]){
    bool rtn = true;
    
    if(argc < 4){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path save_file_full_path" << std::endl;
      rtn = false;
    }
    
    return rtn;
  }
  
  void section1(const std::string &fileName){
    cv::Mat mat = Util::loadImage(fileName);
    cv::imshow("lesson1-1", mat);
    cv::waitKey();
  }

  void section2(const std::string &fileName, const std::string $saveFileName){

    cv::Mat loadImage = cv::imread(fileName);
    
    cv::Mat saveImage;
    cv::cvtColor(loadImage, saveImage, cv::COLOR_BGR2GRAY);
    
    if(!cv::imwrite($saveFileName, saveImage)){
      std::cout << "save error!! : " << $saveFileName << std::endl;
    }
  }

  void section3(const std::string &fileName, const std::string $saveFileName){
    
    cv::Mat loadImage = cv::imread(fileName);
    
    cv::Mat saveImage(loadImage.cols, loadImage.rows, CV_32FC(loadImage.channels()));
    
    for(int i = 0 ; i < loadImage.rows ; i++){
      for(int j = 0; j < loadImage.cols ; j++){
        int color = 0;
        for(int c = 0 ; c < loadImage.channels(); c++){
          u_long p = i * loadImage.step + j * loadImage.elemSize() + c;
          color += loadImage.data[p];
        }
        color /= loadImage.channels();
        
        for(int c = 0 ; c < saveImage.channels(); c++){
          u_long p = i * loadImage.step + j * loadImage.elemSize() + c;
          saveImage.data[p] = color;
        }
      }
    }
    
    if(!cv::imwrite($saveFileName, saveImage)){
      std::cout << "save error!! : " << $saveFileName << std::endl;
    }
  }


  void exec(int argc, const char * argv[]){
    if(!validate(argc, argv)){
      return;
    }
    
    int sectionNumber = atoi(argv[2]);
    std::string inputFileFullPath = std::string(argv[3]);
    std::string saveFileFullPath = std::string(argv[4]);
    
    switch (sectionNumber) {
      case 1:
        section1(inputFileFullPath);
        break;
      case 2:
        section2(inputFileFullPath, saveFileFullPath);
      case 3:
        section3(inputFileFullPath, saveFileFullPath);
      default:
        //エラーハンドリング
        break;
    }
  }
}