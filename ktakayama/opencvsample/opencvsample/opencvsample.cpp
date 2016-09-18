#include "stdafx.h"
#include "opencvsample.h"

int main()
{
	const std::string str_input = "image/input/";
	const cv::Mat input = cv::imread(str_input + "lena.jpg");

	test_task1(input);
	// test_task2(input);
	// test_task3(input);

	return 0;
}

// �ۑ�1
void test_task1(const cv::Mat input)
{
	const int cols = input.cols;
	const int rows = input.rows;

	const std::string str_task1 = "image/task1/";

	// �ۑ�1-1 �摜�\��
	cv::imshow("", input); 
	cv::waitKey(1000);
	cv::imwrite(str_task1 + "lena.png", input);

	// �ۑ�1-2 �O���[�X�P�[����(OpenCV)
	cv::Mat output_gray_cv(rows, cols, CV_8UC3);
	cv::cvtColor(input, output_gray_cv, CV_BGR2GRAY);
	cv::imwrite(str_task1 + "lena_gray_opencv.png", output_gray_cv);

	// �ۑ�1-3 �O���[�X�P�[����(����)
	cv::Mat output_gray_own(rows, cols, CV_8UC3);
	IPfunc::grayscale(input, output_gray_own);
	cv::imwrite(str_task1 + "lena_gray_own.png", output_gray_own);
	
	// �ۑ�1-4 ���T�C�YNN(OpenCV)
	double scale = 0.5;
	int scaleX = (int)floor(rows * scale);
	int scaleY = (int)floor(cols * scale);

	cv::Mat output_scale_cv(scaleX, scaleY, CV_8UC3);
	cv::resize(input, output_scale_cv, cv::Size(0, 0), scale, scale, cv::INTER_NEAREST);
	cv::imwrite(str_task1 + "lena_scale_nearest_opencv.png", output_scale_cv);

	// �ۑ�1-5 ���T�C�YNN(����)
	cv::Mat output_scale_own(scaleX, scaleY, CV_8UC3);
	IPinterpolation::resizeNN(input, output_scale_own, scale);
	cv::imwrite(str_task1 + "lena_scale_nearest_own.png", output_scale_own);

	// ����NN
	cv::Mat output_scale_diff(scaleX, scaleY, CV_8UC3);
	cv::absdiff(output_scale_cv, output_scale_own, output_scale_diff);
	cv::imwrite(str_task1 + "lena_scale_nearest_diff.png", output_scale_diff);

	// ���T�C�YBL(OpenCV)
	cv::resize(input, output_scale_cv, cv::Size(0, 0), scale, scale, cv::INTER_LINEAR);
	cv::imwrite(str_task1 + "lena_scale_bilinear_opencv.png", output_scale_cv);

	// ���T�C�YBL(����)
	IPinterpolation::resizeBL(input, output_scale_own, scale);
	cv::imwrite(str_task1 + "lena_scale_bilinear_own.png", output_scale_own);

	// ����BL
	cv::absdiff(output_scale_cv, output_scale_own, output_scale_diff);
	cv::imwrite(str_task1 + "lena_scale_bilinear_diff.png", output_scale_diff);

	// ���T�C�YBC(OpenCV)
	cv::resize(input, output_scale_cv, cv::Size(0, 0), scale, scale, cv::INTER_CUBIC);
	cv::imwrite(str_task1 + "lena_scale_bicubic_opencv.png", output_scale_cv);

	// ���T�C�YBC(����)
	IPinterpolation::resizeBC(input, output_scale_own, scale);
	cv::imwrite(str_task1 + "lena_scale_bicubic_own.png", output_scale_own);

	// ����BC
	cv::absdiff(output_scale_cv, output_scale_own, output_scale_diff);
	cv::imwrite(str_task1 + "lena_scale_bicubic_diff.png", output_scale_diff);

	// ���T�C�YBC(OpenCV)
	cv::resize(input, output_scale_cv, cv::Size(0, 0), scale, scale, cv::INTER_LANCZOS4);
	cv::imwrite(str_task1 + "lena_scale_lanczos4_opencv.png", output_scale_cv);

	// ���T�C�YBC(����)
	IPinterpolation::resizeLZ(input, output_scale_own, scale);
	cv::imwrite(str_task1 + "lena_scale_lanczos4_own.png", output_scale_own);

	// ����BC
	cv::absdiff(output_scale_cv, output_scale_own, output_scale_diff);
	cv::imwrite(str_task1 + "lena_scale_lanczos4_diff.png", output_scale_diff);

	return;
}

// �ۑ�2
void test_task2(const cv::Mat input)
{
	const int cols = input.cols;
	const int rows = input.rows;

	const std::string str_task2 = "image/task2/";

	// �ۑ�2-1 ���S��f�擾
	cv::Vec3b centerPixel = input.at<cv::Vec3b>(rows / 2, cols / 2);
	printf("RGB(%d, %d, %d)\n", centerPixel[2], centerPixel[1], centerPixel[0]);

    // �ۑ�2-2 ���S��f�擾(HSV)
	cv::Mat input_hsv;
	cvtColor(input, input_hsv, CV_BGR2HSV);
	cv::Vec3b centerPixelHSV = input_hsv.at<cv::Vec3b>(rows / 2, cols / 2);
	printf("HSV(%d, %d, %d)\n", centerPixelHSV[2], centerPixelHSV[1], centerPixelHSV[0]);

	// �ۑ�2-3 HSV�l�Z�b�g
	cv::Mat image_hsv(rows, cols, CV_8UC3);
	IPfunc::valueSetHSV(image_hsv, 100, 100, 100);
	cv::imwrite(str_task2 + "hsv100.png", image_hsv);

	// �ۑ�2-4 ���F�̈�擾
	cv::Mat skin_own(rows, cols, CV_8UC3);
	IPfunc::skinDetect(input, skin_own);
	cv::imwrite(str_task2 + "lena_skinDetect_own.png", skin_own);

	return;
}

// �ۑ�3
void test_task3(const cv::Mat input)
{
	const int cols = input.cols;
	const int rows = input.rows;

	const std::string str_task3 = "image/task3/";
	cv::Mat output(rows, cols, CV_8UC3);

	// ���ω��t�B���^�e�X�g
	IPfilter::average(input, output, 3);
	cv::imwrite(str_task3 + "5-2/lena_average.png", output);

	// �K�E�V�A���t�B���^�e�X�g
	IPfilter::gaussian(input, output, 0.8f, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian1.png", output);
	IPfilter::gaussian(input, output, 1.0f, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian2.png", output);
	IPfilter::gaussian(input, output, 1.3f, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian3.png", output);

	// �K�E�V�A���t�B���^�e�X�g(Pascal)
	IPfilter::gaussian_pascal(input, output, 1);
	cv::imwrite(str_task3 + "5-2/lena_gaussian_pascal1.png", output);
	IPfilter::gaussian_pascal(input, output, 2);
	cv::imwrite(str_task3 + "5-2/lena_gaussian_pascal2.png", output);
	IPfilter::gaussian_pascal(input, output, 3);
	cv::imwrite(str_task3 + "5-2/lena_gaussian_pascal3.png", output);

	// �v�����[�E�B�b�g�t�B���^�e�X�g
	IPfilter::prewitt_x(input, output);
	// IPfilter::prewitt_y(input, output);
	cv::imwrite(str_task3 + "5-3/lena_prewitt.png", output);

	// �\�[�x���t�B���^�e�X�g
	IPfilter::sobel_x(input, output);
	// IPfilter::sobel_y(input, output);
	cv::imwrite(str_task3 + "5-3/lena_sobel.png", output);

	// ���v���V�A���t�B���^�e�X�g
	IPfilter::laplacian(input, output);
	cv::imwrite(str_task3 + "5-3/lena_laplacian.png", output);

	// �N�s���t�B���^�e�X�g
	IPfilter::sharpening(input, output);
	cv::imwrite(str_task3 + "5-4/lena_sharpening.png", output);

	// ���f�B�A���t�B���^�e�X�g
	IPfilter::median(input, output, 1);
	cv::imwrite(str_task3 + "5-5/lena_median1.png", output);
	IPfilter::median(input, output, 5);
	cv::imwrite(str_task3 + "5-5/lena_median5.png", output);

	// �o�C���e�����t�B���^�e�X�g
	IPfilter::bilateral(input, output, 1, 1.0f, 0.05f);
	cv::imwrite(str_task3 + "5-5/lena_bilateral01.png", output);
	IPfilter::bilateral(input, output, 1, 1.0f, 0.05f, 5);
	cv::imwrite(str_task3 + "5-5/lena_bilateral05.png", output);
	IPfilter::bilateral(input, output, 1, 1.0f, 0.05f, 20);
	cv::imwrite(str_task3 + "5-5/lena_bilateral20.png", output);

	// �m�����[�J���~�[���t�B���^�e�X�g
	IPfilter::nonlocalmean(input, output, 1, 1, 0.05f);
	cv::imwrite(str_task3 + "5-5/lena_nonlocalmean01.png", output);
	IPfilter::nonlocalmean(input, output, 1, 1, 0.05f, 5);
	cv::imwrite(str_task3 + "5-5/lena_nonlocalmean05.png", output);
	IPfilter::nonlocalmean(input, output, 1, 1, 0.05f, 20);
	cv::imwrite(str_task3 + "5-5/lena_nonlocalmean20.png", output);

	return;
}