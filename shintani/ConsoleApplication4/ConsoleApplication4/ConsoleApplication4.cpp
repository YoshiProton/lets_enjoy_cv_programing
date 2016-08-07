// ConsoleApplication4.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifdef _DEBUG
//Debug���[�h�̏ꍇ
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_core2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_imgproc2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_highgui2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_objdetect2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_contrib2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_features2d2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_flann2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_gpu2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_legacy2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_ts2413d.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_video2413d.lib")
#else
//Release���[�h�̏ꍇ
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_core2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_imgproc2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_highgui2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_objdetect2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_contrib2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_features2d2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_flann2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_gpu2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_legacy2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_ts2413.lib")
#pragma comment(lib,"C:\\Users\\SAS\\Documents\\opencv\\build\\x64\\vc12\\lib\\opencv_video2413.lib")
#endif

int main()
{
	//�摜�̓ǂݍ���
	cv::Mat img_org = cv::imread("../../lena.JPG");
	imshow("original", img_org);
	//cvWaitKey(0);
	//cvDestroyWindow("original");
	//cvReleaseImage(&img_org);

	//�摜�̃O���C�X�P�[����
	cv::Mat img_gry;
	cv::cvtColor(img_org, img_gry, CV_BGR2GRAY);
	imshow("gray_lena", img_gry);
	cvWaitKey(0);

    return 0;
}

