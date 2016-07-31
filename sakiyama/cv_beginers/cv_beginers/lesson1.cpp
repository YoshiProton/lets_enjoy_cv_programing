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

    cv::imshow("lesson1-1", mat);
    cv::waitKey();
  }

  void section2(const std::string &fileName, const std::string &saveFileName){
    
    std::cout << "section 2" << std::endl;
    
    //バリデーション
    if(fileName.empty() || fileName.length() == 0 ||
       saveFileName.empty() || saveFileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path save_file_full_path" << std::endl;
      return;
    }

    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;
    
    cv::Mat saveMat;
    cv::cvtColor(mat, saveMat, cv::COLOR_BGR2GRAY);
    
    if(!cv::imwrite(saveFileName, saveMat)){
      std::cout << "save error!! : " << saveFileName << std::endl;
    }
  }

  void section3(const std::string &fileName, const std::string &saveFileName){
    
    std::cout << "section 3" << std::endl;

    //バリデーション
    if(fileName.empty() || fileName.length() == 0 ||
       saveFileName.empty() || saveFileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path save_file_full_path" << std::endl;
      return;
    }

    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;

    std::cout << mat.channels() << std::endl;
    
    cv::Mat saveMat(mat.cols, mat.rows, CV_8UC(mat.channels()));
    
    for(int i = 0 ; i < mat.rows ; i++){
      for(int j = 0; j < mat.cols ; j++){
        int color = 0;
        u_long p = GET_P(mat, i, j);
        for(int c = 0 ; c < mat.channels(); c++){
          color += mat.data[p + c];
        }
        color /= mat.channels();
        
        for(int c = 0 ; c < saveMat.channels(); c++){
          saveMat.data[p + c] = color;
        }
      }
    }
    
    if(!cv::imwrite(saveFileName, saveMat)){
      std::cout << "save error!! : " << saveFileName << std::endl;
    }
  }
  
  void section4(const std::string &fileName, const std::string &saveFileName){
  
    std::cout << "section 4" << std::endl;
    
    //バリデーション
    if(fileName.empty() || fileName.length() == 0 ||
       saveFileName.empty() || saveFileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path save_file_full_path" << std::endl;
      return;
    }
    
    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;
    
    cv::Mat dst;
    cv::resize(mat, dst, cv::Size(mat.rows * 2, mat.cols * 2));

    if(!cv::imwrite(saveFileName, dst)){
      std::cout << "save error!! : " << saveFileName << std::endl;
    }
  }
  
  void section5(const std::string &fileName, const std::string &saveFileName){

    std::cout << "section 5" << std::endl;
    
    //バリデーション
    if(fileName.empty() || fileName.length() == 0 ||
       saveFileName.empty() || saveFileName.length() == 0){
      std::cout << "invalid input" << std::endl;
      std::cout << "exec lesson_number section_number(1~5) input_file_full_path save_file_full_path" << std::endl;
      return;
    }
    
    cv::Mat mat;
    if(!Util::loadMat(fileName, mat)) return;
    
    cv::Mat dst(mat.rows * 2, mat.cols * 2, CV_8UC3);
    
    for(int i = 0 ; i < dst.rows ; i++){
      for(int j = 0; j < dst.cols ; j++){

        unsigned long p1 = GET_P(mat, i / 2, j / 2);
        unsigned long p2 = GET_P(dst, i, j);
        
        for(int c = 0 ; c < mat.channels() ; c++){
          dst.data[p2 + c] = mat.data[p1 + c];
        }
      }
    }
    
    if(!cv::imwrite(saveFileName, dst)){
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
        std::string saveFileFullPath = std::string(argv[4]);
        section2(inputFileFullPath, saveFileFullPath);
        break;
      }
      case 3:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        std::string saveFileFullPath = std::string(argv[4]);
        section3(inputFileFullPath, saveFileFullPath);
        break;
      }
      case 4:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        std::string saveFileFullPath = std::string(argv[4]);
        section4(inputFileFullPath, saveFileFullPath);
        break;
      }
      case 5:
      {
        std::string inputFileFullPath = std::string(argv[3]);
        std::string saveFileFullPath = std::string(argv[4]);
        section5(inputFileFullPath, saveFileFullPath);
        break;
      }
      default:
        //エラーハンドリング
        break;
    }
  }
}