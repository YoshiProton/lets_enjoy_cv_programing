#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
	cv::Mat color_img = cv::imread("lena.jpg", 1);
	cv::Mat hsv_img;

	cv::Vec3b *src = color_img.ptr<cv::Vec3b>(color_img.rows / 2); //j�s�ڂ̐擪��f�̃|�C���^���擾
	cv::Vec3b bgr = src[color_img.cols / 2];

	// ���S��f�l(RGB)�̕\��
	printf("RGB���S��f�l(%d,%d) = R:%d G:%d B:%d\n", color_img.cols / 2, color_img.rows / 2, bgr[2], bgr[1], bgr[0]);

	// HSV�ɕϊ�����
	cvtColor(color_img, hsv_img, CV_BGR2HSV);

	src = hsv_img.ptr<cv::Vec3b>(hsv_img.rows / 2); //j�s�ڂ̐擪��f�̃|�C���^���擾
	cv::Vec3b hsv = src[hsv_img.cols / 2];

	// ���S��f�l(HSV)�̕\��
	printf("HSV���S��f�l(%d,%d) = H:%d S:%d V:%d\n", hsv_img.cols / 2, hsv_img.rows / 2, hsv[0], hsv[1], hsv[2]);

	cv::Mat create_img(256, 256, CV_8UC3);
	cv::cvtColor(create_img, create_img, CV_BGR2HSV);

	for (int h = 0; h < create_img.rows; h++) {
		// �|�C���^�̎擾
		cv::Vec3b* ptr = create_img.ptr<cv::Vec3b>(h);
		for (int w = 0; w < create_img.cols; w++) {
			// �l�̐ݒ�
			// �Ώۂ̃s�N�Z����HSV����100,100,100��ݒ肷��B
			ptr[w] = cv::Vec3b(100.0/360*180, 255, 255);
		}
	}
	cv::cvtColor(create_img, create_img, CV_HSV2BGR);

	imwrite("create_img.png", create_img);


	cv::Mat nukidashi_img = color_img.clone();

	cv::cvtColor(nukidashi_img, nukidashi_img, CV_BGR2HSV);

	for (int h = 0; h < nukidashi_img.rows; h++) {
		// �|�C���^�̎擾
		cv::Vec3b* ptr = nukidashi_img.ptr<cv::Vec3b>(h);
		for (int w = 0; w < nukidashi_img.cols; w++) {
			cv::Vec3b hsv = ptr[w];
			// �l�̐ݒ�
			// ���F�̈�ȊO�ɂ�0��ݒ肷��B
			if (hsv[0] >= 0 && hsv[0] <= 15) {
				//�������Ȃ�
			}
			else {
				ptr[w] = cv::Vec3b(0, 0, 0);
			}
		}
	}
	cv::cvtColor(nukidashi_img, nukidashi_img, CV_HSV2BGR);

	imwrite("nukidashi_img.png", nukidashi_img);

	return 0;
}
