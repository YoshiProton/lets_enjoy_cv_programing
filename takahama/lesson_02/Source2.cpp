#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
	cv::Mat color_img = cv::imread("lena.jpg", 1);
	cv::Mat hsv_img;

	cv::Vec3b *src = color_img.ptr<cv::Vec3b>(color_img.rows / 2); //j行目の先頭画素のポインタを取得
	cv::Vec3b bgr = src[color_img.cols / 2];

	// 中心画素値(RGB)の表示
	printf("RGB中心画素値(%d,%d) = R:%d G:%d B:%d\n", color_img.cols / 2, color_img.rows / 2, bgr[2], bgr[1], bgr[0]);

	// HSVに変換する
	cvtColor(color_img, hsv_img, CV_BGR2HSV);

	src = hsv_img.ptr<cv::Vec3b>(hsv_img.rows / 2); //j行目の先頭画素のポインタを取得
	cv::Vec3b hsv = src[hsv_img.cols / 2];

	// 中心画素値(HSV)の表示
	printf("HSV中心画素値(%d,%d) = H:%d S:%d V:%d\n", hsv_img.cols / 2, hsv_img.rows / 2, hsv[0], hsv[1], hsv[2]);

	cv::Mat create_img(256, 256, CV_8UC3);
	cv::cvtColor(create_img, create_img, CV_BGR2HSV);

	for (int h = 0; h < create_img.rows; h++) {
		// ポインタの取得
		cv::Vec3b* ptr = create_img.ptr<cv::Vec3b>(h);
		for (int w = 0; w < create_img.cols; w++) {
			// 値の設定
			// 対象のピクセルにHSV順に100,100,100を設定する。
			ptr[w] = cv::Vec3b(100.0/360*180, 255, 255);
		}
	}
	cv::cvtColor(create_img, create_img, CV_HSV2BGR);

	imwrite("create_img.png", create_img);


	cv::Mat nukidashi_img = color_img.clone();

	cv::cvtColor(nukidashi_img, nukidashi_img, CV_BGR2HSV);

	for (int h = 0; h < nukidashi_img.rows; h++) {
		// ポインタの取得
		cv::Vec3b* ptr = nukidashi_img.ptr<cv::Vec3b>(h);
		for (int w = 0; w < nukidashi_img.cols; w++) {
			cv::Vec3b hsv = ptr[w];
			// 値の設定
			// 肌色領域以外には0を設定する。
			if (hsv[0] >= 0 && hsv[0] <= 15) {
				//何もしない
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

/*
typedef Vec<uchar, 2> Vec2b;
typedef Vec<uchar, 3> Vec3b;
typedef Vec<uchar, 4> Vec4b;

typedef Vec<short, 2> Vec2s;
typedef Vec<short, 3> Vec3s;
typedef Vec<short, 4> Vec4s;

typedef Vec<int, 2> Vec2i;
typedef Vec<int, 3> Vec3i;
typedef Vec<int, 4> Vec4i;

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
typedef Vec<float, 6> Vec6f;

typedef Vec<double, 2> Vec2d;
typedef Vec<double, 3> Vec3d;
typedef Vec<double, 4> Vec4d;
typedef Vec<double, 6> Vec6d;
*/

/*
// 画像の読み込み
cv::Mat srcImg = cv::imread("sample.png");

for (int y = 0; y < srcImg.rows; y++) {
	// ポインタの取得
	cv::Vec3b* ptr = srcImg.ptr<cv::Vec3b>(y);
	for (int x = 0; x < srcImg.cols; x++) {
		// 値の取得
		// 対象のピクセルが赤だった場合、BGRの順に"0,0,255"と出力される。
		cv::Vec3b bgr = ptr[x];
		printf("%d,%d,%d\n", bgr[0], bgr[1], bgr[2]);

		// 値の設定
		// 対象のピクセルにBGR順に255,0,0(青)を設定する。
		ptr[x] = cv::Vec3b(255, 0, 0);
	}
}
// 結果としてsrcImgが真っ青になる。

*/