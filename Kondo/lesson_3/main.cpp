#include "filter.h"


int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("lena.jpg", 1);
	cv::Mat grayimg;
	cv::cvtColor(img, grayimg, CV_BGR2GRAY);

	// 平均化フィルタ
	//cv::Mat ave = averageFilter(grayimg, 5);
	////cv::Mat ave = averageFilter(img, 5);
	//cv::imshow("average", ave);

	// 微分フィルタ
	//cv::Mat dif = diffFileter(grayimg, LONGITUDIAL);
	//cv::imshow("diff", dif);
	// プレウィットフィルタ
	//cv::Mat prw = prewitt(grayimg, LONGITUDIAL);
	//cv::imshow("prewitt", prw);
	// ソーベルフィルタ
	//cv::Mat sbl = sobel(grayimg, LONGITUDIAL);
	//cv::imshow("sobel", sbl);
	// ラプラシアンフィルタ
	//cv::Mat lap = laplacianFilter(grayimg);
	//cv::imshow("laplacian", lap);

	// アンシャープマスク
	//cv::Mat usm = unsharpmask(grayimg, 5);
	//cv::imshow("unsharpmask", usm);


	cv::Mat med = medianFilter(grayimg, 5);
	cv::imshow("median", med);



	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}


//--------------------------



