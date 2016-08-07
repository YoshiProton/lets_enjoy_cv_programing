#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>


void showimg(std::string winname, cv::Mat img);
void grayimg(cv::Mat img);
void grayimg_custom(cv::Mat img);
void resize2x(cv::Mat img);
void resize2x_custom(cv::Mat img, int method);

int main(int argc, char** argv)
{

	cv::Mat img = cv::imread("lena.jpg");

	//showimg("lena", img);
	//grayimg(img);
	//grayimg_custom(img);
	//resize2x(img);
	resize2x_custom(img, 2); // method =1(単純コピー), method = 2(リニア補間)

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}



// 画像の表示(Lesson 1-1)
//
void showimg(std::string winname, cv::Mat img)
{
	cv::namedWindow(winname, cv::WINDOW_AUTOSIZE);
	cv::imshow(winname, img);

}


// OpenCVの関数でグレー化 (Lesson 1-2)
//
void grayimg(cv::Mat img)
{
	cv::Mat dstimg;
	cv::cvtColor(img, dstimg, CV_BGR2GRAY);
	showimg("gray", dstimg);

	cv::imwrite("lena_gray.jpg", dstimg);
}


// RGBにウェイトをつけて、グレー化
//
void grayimg_custom(cv::Mat img)
{
	int width = img.cols;
	int height = img.rows;
	cv::Mat dstimg = cv::Mat(cv::Size(width, height), CV_8UC1);
	cv::Vec3b color;
	uchar gray;

	// RGBにウェイトをつけてグレー値の計算
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			color = img.at<cv::Vec3b>(j, i);
			gray = 0.2989 * color[2] + 0.5870 * color[1] + 0.140 * color[0];
			dstimg.at<uchar>(j, i) = gray;
		}
	}

	showimg("custom gray", dstimg);
	cv::imwrite("lena_gray_custom", dstimg);
}


// openCVの関数を使って、画像を２倍にして表示 (Lesson 1-4)
//
void resize2x(cv::Mat img)
{
	cv::Mat dstimg;
	int height = img.rows;
	int width = img.cols;
	double scale = 2.0;
	// OpenCVのサイズ変更関数　サイズで出力画像サイズを指定する必要。スケールではない。
	cv::resize(img, dstimg, cv::Size(width*scale, height*scale));
	
	showimg("x2 img", dstimg);
	cv::imwrite("lena_2.jpg", dstimg);
}


//
//
void resize2x_custom(cv::Mat img, int method)
{
	//int scale = 2;
	int height = img.rows;
	int width = img.cols;
	cv::Mat dstimg(width * 2, height * 2, CV_8UC3, cv::Scalar::all(0));

	////// 元画像の値を先に配置
	////for (int i = 0; i < width; i++)
	////{
	////	for (int j = 0; j < height; j = j++)
	////	{
	////		dstimg.at<cv::Vec3b>(j * 2, i * 2) = img.at<cv::Vec3b>(j, i);
	////	}
	////}

	// 補間の種類の選択
	if (method == 1)
	{ 
		// 補間
		cv::Vec3b color = cv::Vec3b::all(0);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				// ①単純に2x2の４つにオリジナル画像の画素値を配置
				color = img.at<cv::Vec3b>(j, i);
				dstimg.at<cv::Vec3b>(2 * j    , 2 * i    ) = color;  // すでに配置済みのためいらない
				dstimg.at<cv::Vec3b>(2 * j + 1, 2 * i    ) = color;
				dstimg.at<cv::Vec3b>(2 * j    , 2 * i + 1) = color;
				dstimg.at<cv::Vec3b>(2 * j + 1, 2 * i + 1) = color;
			}
		}
	}
	else if (method == 2)
	{
		cv::Vec3b color = cv::Vec3b::all(0);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				// ②リニア補間
				// 2x2の左上
				dstimg.at<cv::Vec3b>(2 * j, 2 * i) = img.at<cv::Vec3b>(j, i);
				
				// 2x2の左下
				if (j + 1 >= height) // 画像の下端の判定
					color = img.at<cv::Vec3b>(j, i);
				else
					// ※【注意】足した後に1/2にすると、画素値がオーバーフローするので、各々割ったのち足す。
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j + 1, i);
				dstimg.at<cv::Vec3b>(2 * j + 1, 2 * i) = color;

				// 2x2の右上
				if (i + 1 >= width) // 画像の右端の判定
					color = img.at<cv::Vec3b>(j, i);
				else
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j, i + 1);
				dstimg.at<cv::Vec3b>(2 * j, 2 * i + 1) = color;
				
				// 2x2の右下
				if (j + 1 >= height && i + 1 >= width) // 画像の右下角の場合、オリジナル画素値をセット
					color = img.at<cv::Vec3b>(j, i);
				else if (i + 1 >= width) // 画像の右端の場合、左上と左下の平均をセット
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j + 1, i);
				else if (j + 1 >= height) // 画像の下端の場合、左上と右上の平均をセット
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j, i + 1);
				else // 画像の中ほどにある場合は、周囲４つの平均をセット
					color = 0.25 * img.at<cv::Vec3b>(j, i) + 0.25 * dstimg.at<cv::Vec3b>(j, i + 1)
							+ 0.25 * img.at<cv::Vec3b>(j + 1, i) + 0.25 * dstimg.at<cv::Vec3b>(j + 1, i + 1);
				dstimg.at<cv::Vec3b>(2 * j + 1, 2 * i + 1) = color;
			}
		}
	}
	showimg("custom x2", dstimg);
}
