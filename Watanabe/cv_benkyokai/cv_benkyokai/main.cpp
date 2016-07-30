//
//  main.cpp
//  cv_benkyokai
//
//  Created by  Hiroyuki Watanabe on 2016/07/24.
//  Copyright © 2016年  Hiroyuki Watanabe. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//1 - OpenCVのメソッドを用いて、同フォルダのlena.jpgを読み込み、表示させてください
void kadai1(){

    std::cout << "kadai1" << std::endl;

    std::string lenaName = "/Users/Hiroyuki/lets_enjoy_cv_programing/_lesson/20160709/lena.jpg";
    cv::Mat gazo = cv::imread(lenaName);
    cv::imshow("aaaa", gazo);
    cv::waitKey();
}


//2 - OpenCVのメソッドを用いて、lena.jpgを白黒濃淡画像に変換し、lena_gray.jpgというファイル名で保存してください

//3 - 2の課題をOpenCVのメソッドを使わないで行ってください。(読み込み・保存はOpenCV利用可)

//4 - OpenCVのメソッドを使ってlena.jpgを2倍に拡大して、lena_2.jpgというファイル名で保存してください

//5 - 2の課題をOpenCVのメソッドを使わないで行ってください。(読み込み・保存はOpenCV利用可)



int main(int argc, const char * argv[]) {
    // insert code here...
    
    kadai1();
    
    return 0;
}
