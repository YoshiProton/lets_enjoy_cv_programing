#include "filter.h"


int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("lena.jpg", 1);
	cv::Mat grayimg;
	cv::cvtColor(img, grayimg, CV_BGR2GRAY);

	// ���ω��t�B���^
	//cv::Mat ave = averageFilter(grayimg, 5);
	////cv::Mat ave = averageFilter(img, 5);
	//cv::imshow("average", ave);

	// �����t�B���^
	//cv::Mat dif = diffFileter(grayimg, LONGITUDIAL);
	//cv::imshow("diff", dif);
	// �v���E�B�b�g�t�B���^
	//cv::Mat prw = prewitt(grayimg, LONGITUDIAL);
	//cv::imshow("prewitt", prw);
	// �\�[�x���t�B���^
	//cv::Mat sbl = sobel(grayimg, LONGITUDIAL);
	//cv::imshow("sobel", sbl);
	// ���v���V�A���t�B���^
	//cv::Mat lap = laplacianFilter(grayimg);
	//cv::imshow("laplacian", lap);

	// �A���V���[�v�}�X�N
	//cv::Mat usm = unsharpmask(grayimg, 5);
	//cv::imshow("unsharpmask", usm);


	cv::Mat med = medianFilter(grayimg, 5);
	cv::imshow("median", med);



	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}


//--------------------------



