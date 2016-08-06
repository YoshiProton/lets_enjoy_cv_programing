//
//  SameImageFile.cpp
//  cv_beginers
//
//  Created by sakiyamaK on 2016/08/03.
//  Copyright © 2016年 崎山 圭. All rights reserved.
//

#include "basic.h"
#include "SameImageFile.hpp"



namespace SameImageFile {
  void alphaBlend1(std::string &fileFullPath1, std::string &fileFullPath2, double alpha,
                  std::string &saveFullPath){
    
    cv::Mat mat1;
    cv::Mat mat2;
    if(!(Util::loadMat(fileFullPath1, mat1) && Util::loadMat(fileFullPath2, mat2))){
      return;
    }
    
    if(mat1.size() != mat2.size()){
      std::cout << "[ERROR] 画像サイズが違います" << std::endl;
      return;
    }
    
    cv::Mat dst;
    //dst(I)= saturate(src1(I)*alpha + src2(I)*beta +  gamma)
    cv::addWeighted(mat1, alpha, mat2, 1.0 - alpha, 0.0, dst);
    
    cv::imwrite(saveFullPath, dst);

    std::cout << __FUNCTION__ << " : finish" << std::endl;
    
  }
  
  void alphaBlend2(std::string &fileFullPath1, std::string &fileFullPath2, double alpha,
                   std::string &saveFullPath){
    cv::Mat mat1;
    cv::Mat mat2;
    if(!(Util::loadMat(fileFullPath1, mat1) && Util::loadMat(fileFullPath2, mat2))){
      return;
    }

    if(mat1.size() != mat2.size()){
      std::cout << "[ERROR] 画像サイズが違います" << std::endl;
      return;
    }
    
    cv::Mat dst = cv::Mat::zeros(mat1.size(), CV_8UC3);
    for(int i = 0 ; i < dst.rows ; i++){
      for(int j = 0; j < dst.cols ; j++){
        auto color1 = *mat1.ptr<cv::Vec3b>(i,j);
        auto color2 = *mat2.ptr<cv::Vec3b>(i,j);
        auto color3 = alpha * color1 + (1.0 - alpha) * color2;
        *dst.ptr<cv::Vec3b>(i, j) = color3;
      }
    }
    
    cv::imwrite(saveFullPath, dst);
    
    std::cout << __FUNCTION__ << " : finish" << std::endl;
  }
  
  void alphaBlend3(std::string &fileFullPath1, std::string &fileFullPath2,
                   std::string &saveFullPath){
    cv::Mat mat1;
    cv::Mat mat2;
    if(!(Util::loadMat(fileFullPath1, mat1) && Util::loadMat(fileFullPath2, mat2))){
      return;
    }
    
    if(mat1.size() != mat2.size()){
      std::cout << "[ERROR] 画像サイズが違います" << std::endl;
      return;
    }

    cv::Mat dst(mat1.size(), mat1.type(), cv::Scalar::all(0));

    for(int i = 0 ; i < dst.rows ; i++){
      for(int j = 0; j < dst.cols ; j++){
        double alpha = (double)j / dst.cols;
        auto color1 = *mat1.ptr<cv::Vec3b>(i,j);
        auto color2 = *mat2.ptr<cv::Vec3b>(i,j);
        auto color3 = alpha * color1 + (1.0 - alpha) * color2;
        *dst.ptr<cv::Vec3b>(i, j) = color3;
      }
    }
    
    cv::imwrite(saveFullPath, dst);
    
    std::cout << __FUNCTION__ << " : finish" << std::endl;
  }
  
  void emboss(std::string &fileFullPath, int moveX, int moveY, std::string &saveFullPath){
    cv::Mat mat;
    if(!Util::loadMat(fileFullPath, mat, 0)){
      return;
    }
    
    //ネガポジ反転
    cv::Mat invMat = ~mat;
    //出力画像の用意
    cv::Mat dst(mat.size(), mat.type(), cv::Scalar::all(0));
    //引く分
    int gray = 128;

    for(int i = 0 ; i < dst.rows ; i++){
      for(int j = 0; j < dst.cols ; j++){
        auto color1 = *mat.ptr<uchar>(i, j);
        //平行移動した画素を取得
        auto color2 = *invMat.ptr<uchar>(i + moveY, j + moveX);
        auto color3 = color1 + color2 - gray;
        color3 = color3 < 0 ? 0 : color3;
        color3 = color3 > 255 ? 255 : color3;
        *dst.ptr(i, j) = color3;
      }
    }
    
    cv::imwrite(saveFullPath, dst);
    
    std::cout << __FUNCTION__ << " : finish" << std::endl;
  }

  void chromakey(std::string &fileFullPath1, std::string &fileFullPath2,
                 std::string &saveFullPath){
    cv::Mat mat1;
    cv::Mat mat2;
    if(!(Util::loadMat(fileFullPath1, mat1) && Util::loadMat(fileFullPath2, mat2))){
      return;
    }
    
    if(mat1.size() != mat2.size()){
      std::cout << "[ERROR] 画像サイズが違います" << std::endl;
      return;
    }
    
    cv::Mat dst(mat1.size(), mat1.type(), cv::Scalar::all(0));
    
    for(int i = 0 ; i < dst.rows ; i++){
      for(int j = 0; j < dst.cols ; j++){
        auto color1 = *mat1.ptr<cv::Vec3b>(i,j);
        auto color2 = *mat2.ptr<cv::Vec3b>(i,j);
        cv::Vec3b setColor;
        //jpg画像は画素が若干変化するため白といっても255ではなくなっている
        if(color1[0] > 250 &&color1[1] > 250 && color1[2] > 250){
          setColor = color2;
        }
        else{
          setColor = color1;
        }
        *dst.ptr<cv::Vec3b>(i, j) = setColor;
      }
    }
    
    cv::imwrite(saveFullPath, dst);
    
    std::cout << __FUNCTION__ << " : finish" << std::endl;
  }

}
