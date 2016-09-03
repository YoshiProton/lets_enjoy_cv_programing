#include "stdafx.h"
#include "opencvsample.h"

int main()
{
	const std::string str_input = "image/input/";
	const cv::Mat input = cv::imread(str_input + "lena.jpg");

	test_task1(input);
	test_task2(input);
	// test_task3(input);

	return 0;
}

// 課題1
void test_task1(const cv::Mat input)
{
	const int cols = input.cols;
	const int rows = input.rows;

	const std::string str_task1 = "image/task1/";

	// 課題1-1 画像表示
	cv::imshow("", input); 
	cv::waitKey(1000);
	cv::imwrite(str_task1 + "lena.jpg", input);

	// 課題1-2 グレースケール化(OpenCV)
	cv::Mat output_gray_cv(rows, cols, CV_8UC3);
	cv::cvtColor(input, output_gray_cv, CV_BGR2GRAY);
	cv::imwrite(str_task1 + "lena_gray_cv.jpg", output_gray_cv);

	// 課題1-3 グレースケール化(自作)
	cv::Mat output_gray_own(rows, cols, CV_8UC3);
	IPfunc::grayscale(input, output_gray_own);
	cv::imwrite(str_task1 + "lena_gray_own.jpg", output_gray_own);
	
	// 課題1-4 リサイズ(OpenCV)
	cv::Mat output_scale_cv(rows * 2, cols * 2, CV_8UC3);
	cv::resize(input, output_scale_cv, cv::Size(0, 0), 2.0, 2.0, cv::INTER_NEAREST);
	cv::imwrite(str_task1 + "lena_scale_cv.jpg", output_scale_cv);

	// 課題1-5 リサイズ(自作)
	cv::Mat output_scale_own(rows * 2, cols * 2, CV_8UC3);
	IPfunc::resizeNN(input, output_scale_own, 2.0);
	cv::imwrite(str_task1 + "lena_scale_own.jpg", output_scale_own);

	return;
}

// 課題2
void test_task2(const cv::Mat input)
{
	const int cols = input.cols;
	const int rows = input.rows;

	const std::string str_task2 = "image/task2/";

	// 課題2-1 中心画素取得
	cv::Vec3b centerPixel = input.at<cv::Vec3b>(rows / 2, cols / 2);
	printf("RGB(%d, %d, %d)\n", centerPixel[2], centerPixel[1], centerPixel[0]);

    // 課題2-2 中心画素取得(HSV)
	cv::Mat input_hsv;
	cvtColor(input, input_hsv, CV_BGR2HSV);
	cv::Vec3b centerPixelHSV = input_hsv.at<cv::Vec3b>(rows / 2, cols / 2);
	printf("HSV(%d, %d, %d)\n", centerPixelHSV[2], centerPixelHSV[1], centerPixelHSV[0]);

	// 課題2-3 HSV値セット
	cv::Mat image_hsv(rows, cols, CV_8UC3);
	IPfunc::valueSetHSV(image_hsv, 100, 100, 100);
	cv::imwrite(str_task2 + "hsv100.jpg", image_hsv);

	// 課題2-4 肌色領域取得
	cv::Mat skin_own(rows, cols, CV_8UC3);
	IPfunc::skinDetect(input, skin_own);
	cv::imwrite(str_task2 + "lena_skinDetect_own.jpg", skin_own);

	return;
}

// 課題3
void test_task3(const cv::Mat input)
{
	const int cols = input.cols;
	const int rows = input.rows;

	const std::string str_task3 = "image/task3/";
	cv::Mat output(rows, cols, CV_8UC3);

	// 平均化フィルタテスト
	IPfilter::average(input, output, 3);
	cv::imwrite(str_task3 + "5-2/lena_average.jpg", output);

	// ガウシアンフィルタテスト
	IPfilter::gaussian(input, output, 0.8f, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian1.jpg", output);
	IPfilter::gaussian(input, output, 1.0f, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian2.jpg", output);
	IPfilter::gaussian(input, output, 1.3f, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian3.jpg", output);

	// ガウシアンフィルタテスト(Pascal)
	IPfilter::gaussian_pascal(input, output, 1);
	cv::imwrite(str_task3 + "5-2/lena_gaussian_pascal1.jpg", output);
	IPfilter::gaussian_pascal(input, output, 2);
	cv::imwrite(str_task3 + "5-2/lena_gaussian_pascal2.jpg", output);
	IPfilter::gaussian_pascal(input, output, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian_pascal3.jpg", output);

	// プリューウィットフィルタテスト
	IPfilter::prewitt_x(input, output);
	// IPfilter::prewitt_y(input, output);
	cv::imwrite(str_task3 + "5-3/lena_prewitt.jpg", output);

	// ソーベルフィルタテスト
	IPfilter::sobel_x(input, output);
	// IPfilter::sobel_y(input, output);
	cv::imwrite(str_task3 + "5-3/lena_sobel.jpg", output);

	// ラプラシアンフィルタテスト
	IPfilter::laplacian(input, output);
	cv::imwrite(str_task3 + "5-3/lena_laplacian.jpg", output);

	// 鮮鋭化フィルタテスト
	IPfilter::sharpening(input, output);
	cv::imwrite(str_task3 + "5-4/lena_sharpening.jpg", output);

	// メディアンフィルタテスト
	IPfilter::median(input, output, 1);
	cv::imwrite(str_task3 + "5-5/lena_median1.jpg", output);
	IPfilter::median(input, output, 5);
	cv::imwrite(str_task3 + "5-5/lena_median5.jpg", output);

	// バイラテラルフィルタテスト
	IPfilter::bilateral(input, output, 1, 1.0f, 0.05f);
	cv::imwrite(str_task3 + "5-5/lena_bilateral01.jpg", output);
	IPfilter::bilateral(input, output, 1, 1.0f, 0.05f, 5);
	cv::imwrite(str_task3 + "5-5/lena_bilateral05.jpg", output);
	IPfilter::bilateral(input, output, 1, 1.0f, 0.05f, 20);
	cv::imwrite(str_task3 + "5-5/lena_bilateral20.jpg", output);

	// ノンローカルミーンフィルタテスト
	IPfilter::nonlocalmean(input, output, 1, 1, 0.05f);
	cv::imwrite(str_task3 + "5-5/lena_nonlocalmean01.jpg", output);
	IPfilter::nonlocalmean(input, output, 1, 1, 0.05f, 5);
	cv::imwrite(str_task3 + "5-5/lena_nonlocalmean05.jpg", output);
	IPfilter::nonlocalmean(input, output, 1, 1, 0.05f, 20);
	cv::imwrite(str_task3 + "5-5/lena_nonlocalmean20.jpg", output);

	return;
}