#include "stdafx.h"
#include "IPfunc.h"

int main()
{
	cv::Mat input = cv::imread("../../image/lena.jpg");
	int cols = input.cols;
	int rows = input.rows;

	/*
	cv::Mat gray_cv(rows, cols, CV_8UC3); // �ۑ�1-2�p
	cv::Mat gray_own(rows, cols, CV_8UC3); // �ۑ�1-3�p
	cv::Mat scale_cv(rows * 2, cols * 2, CV_8UC3); // �ۑ�1-4�p
	cv::Mat scale_own(rows * 2, cols * 2, CV_8UC3); // �ۑ�1-5�p

	cv::cvtColor(input, gray_cv, CV_BGR2GRAY);
	my_grayscale(input, gray_own);

	cv::resize(input, scale_cv, cv::Size(0, 0), 2.0, 2.0, INTER_NEAREST);
	my_resizeNN(input, scale_own, 2.0);

	cv::imshow("", input); // �ۑ�1-1
	cv::waitKey(1000);
	cv::imwrite("image/task1/lena.jpg", input);
	cv::imwrite("image/task1/lena_gray_cv.jpg", gray_cv); // �ۑ�1-2 
	cv::imwrite("image/task1/lena_gray_own.jpg", gray_own); // �ۑ�1-3 
	cv::imwrite("image/task1/lena_scale_cv.jpg", scale_cv); // �ۑ�1-4 
	cv::imwrite("image/task1/lena_scale_own.jpg", scale_own); // �ۑ�1-5 

	cv::Vec3b centerPixel = input.at<cv::Vec3b>(rows / 2, cols / 2); // �ۑ�2-1�p

	cv::Mat input_hsv;
	cvtColor(input, input_hsv, CV_BGR2HSV);
	cv::Vec3b centerPixelHSV = input_hsv.at<cv::Vec3b>(rows / 2, cols / 2); // �ۑ�2-2�p

	cv::Mat image_hsv(rows, cols, CV_8UC3); // �ۑ�2-3�p
	my_valueSetHSV(image_hsv, 100, 100, 100);

	cv::Mat skin_own(rows, cols, CV_8UC3); // �ۑ�2-4�p
	my_skinDetect(input, skin_own);

	printf("RGB(%d, %d, %d)\n", centerPixel[2], centerPixel[1], centerPixel[0]); // �ۑ�2-1
	printf("HSV(%d, %d, %d)\n", centerPixelHSV[2], centerPixelHSV[1], centerPixelHSV[0]); // �ۑ�2-2
	cv::imwrite("image/task2/hsv100.jpg", image_hsv); // �ۑ�2-3
	cv::imwrite("image/task2/lena_skinDetect_own.jpg", skin_own); // �ۑ�2-4 

	*/

	// ���ω��t�B���^�e�X�g
	cv::Mat image_average(rows, cols, CV_8UC3); // �ۑ�3-1�p
	my_average(input, image_average, 3);
	cv::imwrite("image/task3/lena_average.jpg", image_average); // �ۑ�3-1

	// �v�����[�E�B�b�g�t�B���^�e�X�g
	cv::Mat image_prewitt(rows, cols, CV_8UC3);
	my_prewitt_x(input, image_prewitt);
	// my_prewitt_y(input, image_prewitt);
	cv::imwrite("image/task3/lena_prewitt.jpg", image_prewitt);

	// �\�[�x���t�B���^�e�X�g
	cv::Mat image_sobel(rows, cols, CV_8UC3);
	my_sobel_x(input, image_sobel);
	// my_sobel_y(input, image_sobel);
	cv::imwrite("image/task3/lena_sobel.jpg", image_sobel);

	return 0;
}
