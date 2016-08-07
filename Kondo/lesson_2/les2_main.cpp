#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>



void showCenterColor(cv::Mat image);
void showCenterColorHSV(cv::Mat image);
void showSpecifiedColorImage(int height, int width, int hue, int sat, int val);
void extractSpecifiedColorFromImage(cv::Mat image, int hueMin, int hueMax);

int main(int argc, char ** argv)
{
	cv::Mat img = cv::imread("lena.jpg");
	
	// Les2-1
	//showCenterColor(img);
	// Les2-2
	//showCenterColorHSV(img);
	// Les2-3
	//showSpecifiedColorImage(256, 256, 100, 100, 100);
	// Les2-4
	extractSpecifiedColorFromImage(img, 20,150);

	//cv::imshow("lena", img);
	cv::waitKey(0);
	return 0;
}





// Les 2-1
// �摜�̐^�񒆂̉�f�l��Ԃ�
void showCenterColor(cv::Mat image)
{
	// �����E���̔����̒l
	int half_cols = image.cols / 2;
	int half_rows = image.rows / 2;
	// �����̉�f�l���Ƃ�
	cv::Vec3b color = image.at<cv::Vec3b>(half_rows, half_cols);

	std::cout << "(R, G, B) = (" << (int)color[2] << ", " << (int)color[1] << ", " << (int)color[0] << ")" << std::endl;
}


// Les2-2
// �摜�̐^�񒆂̉�f�l���AHSV�ŕԂ�
void showCenterColorHSV(cv::Mat image)
{
	// �����E���̔������v�Z
	int half_cols = image.cols / 2;
	int half_rows = image.rows / 2;
	cv::Mat hsvimg;
	// HSV�ւ̕ϊ�
	cv::cvtColor(image, hsvimg, CV_BGR2HSV);
	cv::Vec3b color = hsvimg.at<cv::Vec3b>(half_rows, half_cols);

	std::cout << "(H, S, V) = (" << (int)color[0] << ", " << (int)color[1] << ", " << (int)color[2] << ")" << std::endl;
}


// Les2-3
// 256x256�̉摜�T�C�Y�ŁA(HSV) = (100, 100, 100)�̉摜��\��
void showSpecifiedColorImage(int height, int width, int hue, int sat, int val)
{
	// �w��T�C�Y�̃[������������Mat��p�ӁiHSV�̉�f�l�����邱�Ƃ�z��j
	cv::Mat hsv = cv::Mat::zeros(cv::Size(height, width), CV_8UC3);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// HSV�̒l������
			hsv.at<cv::Vec3b>(y, x)[0] = hue;
			hsv.at<cv::Vec3b>(y, x)[1] = sat;
			hsv.at<cv::Vec3b>(y, x)[2] = val;
		}
	}
	// HSV����RGB�ւ̕Ԋ�
	cv::Mat rgbimg;
	cv::cvtColor(hsv, rgbimg, CV_HSV2BGR);

	cv::namedWindow("image");
	cv::imshow("image", rgbimg);
	cv::imwrite("color_pattern.png", rgbimg);
}


// Les2-4
// �摜����w��F���͈͂̐F�������o���ĕ\������B
void extractSpecifiedColorFromImage(cv::Mat image, int hueMin, int hueMax)
{
	if (hueMin < 0)
	{
		std::cout << "Hue value should be in the range (0-180). set the value larger than 0." << std::endl;
		return;
	}

	if (hueMax > 180)
	{
		std::cout << "Hue value should be in the range (0-180). set the value smaller than 180." << std::endl;
		return;
	}

	if (hueMin > hueMax)
	{
		std::cout << "min/max value of hue is oppositely selected."  << std::endl;
		return;
	}

	cv::Mat hsvimg;
	cv::cvtColor(image, hsvimg, CV_BGR2HSV);

	int cols = hsvimg.cols;
	int rows = hsvimg.rows;
	
	cv::Mat dstimg(cv::Size(cols, rows), CV_8UC3, cv::Scalar::all(0));
	
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			// HSV�̒��o
			cv::Vec3b hsv = hsvimg.at<cv::Vec3b>(y, x);
			int hue = hsv[0];
			//int sat = hsv[1];
			//int val = hsv[2];
			if (hueMin < hue && hue <= hueMax)
			{
				dstimg.at<cv::Vec3b>(y, x) = hsv;
			}
			else
			{
				// do nothing
			}
		}
	}
	// HSV����RGB�ϊ�
	cv::Mat dstrgbimg;
	cv::cvtColor(dstimg, dstrgbimg, CV_HSV2BGR);

	cv::imshow("lena", dstrgbimg);


	// ��R����̃R�[�h�Q��
	// ���s���̊֐������擾�ł���̂��B
	std::cout << __FUNCTION__ << ": finished." << std::endl;
}

