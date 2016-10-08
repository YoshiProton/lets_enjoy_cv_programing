#include "filter.h"


int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("lena.jpg", 1);
	cv::Mat grayimg;
	cv::cvtColor(img, grayimg, CV_BGR2GRAY);

	// 平均化フィルタ
	////cv::Mat ave = averageFilter(grayimg, 5);
	//cv::Mat ave = averageFilter(img, 7);
	//cv::imshow("average", ave);

	// 微分(差分)フィルタ
	//cv::Mat dif = diffFileter(grayimg, LONGITUDIAL);
	//cv::imshow("diff", dif);
	// プレウィットフィルタ
	//cv::Mat prw = prewitt(grayimg, HORIZONTAL);
	//cv::imshow("prewitt", prw);
	// ソーベルフィルタ
	//cv::Mat sbl = sobel(grayimg, LONGITUDIAL);
	//cv::imshow("sobel", sbl);
	// ラプラシアンフィルタ
	//cv::Mat lap = laplacianFilter(grayimg);
	//cv::imshow("laplacian", lap);

	// アンシャープマスク
	////cv::Mat usm = unsharpmask(grayimg, 5);
	//cv::Mat usm = unsharpmask(img, 5); // カラーでやると、色がおかしい？RGBの混ざり方が変わるため？
	//cv::imshow("unsharpmask", usm);

	// メディアンフィルタ
	//cv::Mat med = medianFilter(grayimg, 3);
	cv::Mat med = medianFilter(img, 3);
	cv::imshow("median", med);

	// バイラテラルフィルタ (適当な、パラメータの値が不明。とりあえずうまくいっている？)
	//cv::Mat bilat = bilateralFilter(grayimg, 11, 3, 3);
	//bilat = bilateralFilter(bilat, 11, 3, 3);
	//cv::Mat bilat = bilateralFilter(img, 11, 3, 3);
	//cv::imshow("bilateral", bilat);
	//cv::imshow("original", grayimg);


	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}


//--------------------------



