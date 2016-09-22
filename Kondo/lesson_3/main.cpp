#include "filter.h"


int main(int argc, char** argv)
{
	cv::Mat img = cv::imread("lena.jpg", 1);
	cv::Mat grayimg;
	cv::cvtColor(img, grayimg, CV_BGR2GRAY);

	// ���ω��t�B���^
	////cv::Mat ave = averageFilter(grayimg, 5);
	//cv::Mat ave = averageFilter(img, 7);
	//cv::imshow("average", ave);

	// ����(����)�t�B���^
	//cv::Mat dif = diffFileter(grayimg, LONGITUDIAL);
	//cv::imshow("diff", dif);
	// �v���E�B�b�g�t�B���^
	//cv::Mat prw = prewitt(grayimg, HORIZONTAL);
	//cv::imshow("prewitt", prw);
	// �\�[�x���t�B���^
	//cv::Mat sbl = sobel(grayimg, LONGITUDIAL);
	//cv::imshow("sobel", sbl);
	// ���v���V�A���t�B���^
	//cv::Mat lap = laplacianFilter(grayimg);
	//cv::imshow("laplacian", lap);

	// �A���V���[�v�}�X�N
	////cv::Mat usm = unsharpmask(grayimg, 5);
	//cv::Mat usm = unsharpmask(img, 5); // �J���[�ł��ƁA�F�����������HRGB�̍���������ς�邽�߁H
	//cv::imshow("unsharpmask", usm);

	// ���f�B�A���t�B���^
	//cv::Mat med = medianFilter(grayimg, 3);
	cv::Mat med = medianFilter(img, 3);
	cv::imshow("median", med);

	// �o�C���e�����t�B���^ (�K���ȁA�p�����[�^�̒l���s���B�Ƃ肠�������܂������Ă���H)
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



