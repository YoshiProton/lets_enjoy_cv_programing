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

  void section3(const std::string &fileName, const std::string saveFileName){
    
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
        for(int c = 0 ; c < mat.channels(); c++){
          u_long p = i * mat.step + j * mat.elemSize() + c;
          color += mat.data[p];
        }
        color /= mat.channels();
        
        for(int c = 0 ; c < saveMat.channels(); c++){
          u_long p = i * mat.step + j * mat.elemSize() + c;
          saveMat.data[p] = color;
        }
      }
    }
    
    if(!cv::imwrite(saveFileName, saveMat)){
      std::cout << "save error!! : " << saveFileName << std::endl;
    }
  }
  
  void section4(const std::string &fileName, const std::string saveFileName){
  
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

  }


  void exec(int argc, const char * argv[]){
    
    int sectionNumber = atoi(argv[2]);
    std::string inputFileFullPath = std::string(argv[3]);
    std::string saveFileFullPath = std::string(argv[4]);
    
    switch (sectionNumber) {
      case 1:
        section1(inputFileFullPath);
        break;
      case 2:
        section2(inputFileFullPath, saveFileFullPath);
        break;
      case 3:
        section3(inputFileFullPath, saveFileFullPath);
        break;
      default:
        //エラーハンドリング
        break;
    }
  }
}