#include "stdafx.h"
#include "IPfunc.h"

int main()
{
	cv::Mat input = cv::imread("../../image/lena.jpg");
	int cols = input.cols;
	int rows = input.rows;

	cv::Mat gray_cv(rows, cols, CV_8UC3); // ‰Û‘è2 
	cv::Mat gray_own(rows, cols, CV_8UC3); // ‰Û‘è3
	cv::Mat scale_cv(rows * 2, cols * 2, CV_8UC3); // ‰Û‘è4
	cv::Mat scale_own(rows * 2, cols * 2, CV_8UC3); // ‰Û‘è5

	cv::cvtColor(input, gray_cv, CV_BGR2GRAY);
	my_grayscale(input, gray_own);

	cv::resize(input, scale_cv, cv::Size(0, 0), 2.0, 2.0, INTER_NEAREST);
	my_resize2(input, scale_own);

	// cv::imshow("", input);
	cv::imwrite("lena.jpg", input);
	cv::imwrite("lena_gray_cv.jpg", gray_cv);
	cv::imwrite("lena_gray_own.jpg", gray_own);

	cv::imwrite("lena_scale_cv.jpg", scale_cv);
	cv::imwrite("lena_scale_own.jpg", scale_own);

    return 0;
}
