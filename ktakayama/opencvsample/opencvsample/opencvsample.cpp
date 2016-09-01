#include "stdafx.h"
#include "IPfunc.h"

int main()
{
	cv::Mat input = cv::imread("../../image/lena.jpg");
	int cols = input.cols;
	int rows = input.rows;

	/*
	cv::Mat gray_cv(rows, cols, CV_8UC3); // 課題1-2用
	cv::Mat gray_own(rows, cols, CV_8UC3); // 課題1-3用
	cv::Mat scale_cv(rows * 2, cols * 2, CV_8UC3); // 課題1-4用
	cv::Mat scale_own(rows * 2, cols * 2, CV_8UC3); // 課題1-5用

	cv::cvtColor(input, gray_cv, CV_BGR2GRAY);
	my_grayscale(input, gray_own);

	cv::resize(input, scale_cv, cv::Size(0, 0), 2.0, 2.0, INTER_NEAREST);
	my_resizeNN(input, scale_own, 2.0);

	cv::imshow("", input); // 課題1-1
	cv::waitKey(1000);
	cv::imwrite("image/task1/lena.jpg", input);
	cv::imwrite("image/task1/lena_gray_cv.jpg", gray_cv); // 課題1-2 
	cv::imwrite("image/task1/lena_gray_own.jpg", gray_own); // 課題1-3 
	cv::imwrite("image/task1/lena_scale_cv.jpg", scale_cv); // 課題1-4 
	cv::imwrite("image/task1/lena_scale_own.jpg", scale_own); // 課題1-5 

	cv::Vec3b centerPixel = input.at<cv::Vec3b>(rows / 2, cols / 2); // 課題2-1用

	cv::Mat input_hsv;
	cvtColor(input, input_hsv, CV_BGR2HSV);
	cv::Vec3b centerPixelHSV = input_hsv.at<cv::Vec3b>(rows / 2, cols / 2); // 課題2-2用

	cv::Mat image_hsv(rows, cols, CV_8UC3); // 課題2-3用
	my_valueSetHSV(image_hsv, 100, 100, 100);

	cv::Mat skin_own(rows, cols, CV_8UC3); // 課題2-4用
	my_skinDetect(input, skin_own);

	printf("RGB(%d, %d, %d)\n", centerPixel[2], centerPixel[1], centerPixel[0]); // 課題2-1
	printf("HSV(%d, %d, %d)\n", centerPixelHSV[2], centerPixelHSV[1], centerPixelHSV[0]); // 課題2-2
	cv::imwrite("image/task2/hsv100.jpg", image_hsv); // 課題2-3
	cv::imwrite("image/task2/lena_skinDetect_own.jpg", skin_own); // 課題2-4 

	*/

	// 平均化フィルタテスト
	cv::Mat image_average(rows, cols, CV_8UC3); // 課題3-1用
	my_average(input, image_average, 3);
	cv::imwrite("image/task3/lena_average.jpg", image_average); // 課題3-1

	// ガウシアンフィルタテスト
	cv::Mat image_gaussian(rows, cols, CV_8UC3);
	my_gaussian(input, image_gaussian, 0.8f, 3);
	cv::imwrite("image/task3/lena_gaussian1.jpg", image_gaussian);
	my_gaussian(input, image_gaussian, 1.0f, 3);
	cv::imwrite("image/task3/lena_gaussian2.jpg", image_gaussian);
	my_gaussian(input, image_gaussian, 1.3f, 3);
	cv::imwrite("image/task3/lena_gaussian3.jpg", image_gaussian);

	// ガウシアンフィルタテスト(Pascal)
	cv::Mat image_gaussian_pascal(rows, cols, CV_8UC3);
	my_gaussian_pascal(input, image_gaussian_pascal, 1);
	cv::imwrite("image/task3/lena_gaussian_pascal1.jpg", image_gaussian_pascal);
	my_gaussian_pascal(input, image_gaussian_pascal, 2);
	cv::imwrite("image/task3/lena_gaussian_pascal2.jpg", image_gaussian_pascal);
	my_gaussian_pascal(input, image_gaussian_pascal, 3);
	cv::imwrite("image/task3/lena_gaussian_pascal3.jpg", image_gaussian_pascal);

	// プリューウィットフィルタテスト
	cv::Mat image_prewitt(rows, cols, CV_8UC3);
	my_prewitt_x(input, image_prewitt);
	// my_prewitt_y(input, image_prewitt);
	cv::imwrite("image/task3/lena_prewitt.jpg", image_prewitt);

	// ソーベルフィルタテスト
	cv::Mat image_sobel(rows, cols, CV_8UC3);
	my_sobel_x(input, image_sobel);
	// my_sobel_y(input, image_sobel);
	cv::imwrite("image/task3/lena_sobel.jpg", image_sobel);

	// ラプラシアンフィルタテスト
	cv::Mat image_laplacian(rows, cols, CV_8UC3);
	my_laplacian(input, image_laplacian);
	cv::imwrite("image/task3/lena_laplacian.jpg", image_laplacian);

	// 鮮鋭化フィルタテスト
	cv::Mat image_sharpening(rows, cols, CV_8UC3);
	my_sharpening(input, image_sharpening);
	cv::imwrite("image/task3/lena_sharpening.jpg", image_sharpening);

	// メディアンフィルタテスト
	//cv::Mat image_median(rows, cols, CV_8UC3);
	//my_median(input, image_median);
	//cv::imwrite("image/task3/lena_median.jpg", image_median);

	// バイラテラルフィルタテスト
	cv::Mat image_bilateral(rows, cols, CV_8UC3);
	my_bilateral(input, image_bilateral, 1, 1.0f, 0.05f);
	cv::imwrite("image/task3/lena_bilateral01.jpg", image_bilateral);
	my_bilateral(input, image_bilateral, 1, 1.0f, 0.05f, 5);
	cv::imwrite("image/task3/lena_bilateral05.jpg", image_bilateral);
	my_bilateral(input, image_bilateral, 1, 1.0f, 0.05f, 20);
	cv::imwrite("image/task3/lena_bilateral20.jpg", image_bilateral);

	// ノンローカルミーンフィルタテスト
	cv::Mat image_nonlocalmean(rows, cols, CV_8UC3);
	my_nonlocalmean(input, image_nonlocalmean, 1, 1, 0.05f);
	cv::imwrite("image/task3/lena_nonlocalmean01.jpg", image_nonlocalmean);
	my_nonlocalmean(input, image_nonlocalmean, 1, 1, 0.05f, 5);
	cv::imwrite("image/task3/lena_nonlocalmean05.jpg", image_nonlocalmean);
	my_nonlocalmean(input, image_nonlocalmean, 1, 1, 0.05f, 20);
	cv::imwrite("image/task3/lena_nonlocalmean20.jpg", image_nonlocalmean);

	return 0;
}
