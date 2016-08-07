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
	resize2x_custom(img, 2); // method =1(�P���R�s�[), method = 2(���j�A���)

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}



// �摜�̕\��(Lesson 1-1)
//
void showimg(std::string winname, cv::Mat img)
{
	cv::namedWindow(winname, cv::WINDOW_AUTOSIZE);
	cv::imshow(winname, img);

}


// OpenCV�̊֐��ŃO���[�� (Lesson 1-2)
//
void grayimg(cv::Mat img)
{
	cv::Mat dstimg;
	cv::cvtColor(img, dstimg, CV_BGR2GRAY);
	showimg("gray", dstimg);

	cv::imwrite("lena_gray.jpg", dstimg);
}


// RGB�ɃE�F�C�g�����āA�O���[��
//
void grayimg_custom(cv::Mat img)
{
	int width = img.cols;
	int height = img.rows;
	cv::Mat dstimg = cv::Mat(cv::Size(width, height), CV_8UC1);
	cv::Vec3b color;
	uchar gray;

	// RGB�ɃE�F�C�g�����ăO���[�l�̌v�Z
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


// openCV�̊֐����g���āA�摜���Q�{�ɂ��ĕ\�� (Lesson 1-4)
//
void resize2x(cv::Mat img)
{
	cv::Mat dstimg;
	int height = img.rows;
	int width = img.cols;
	double scale = 2.0;
	// OpenCV�̃T�C�Y�ύX�֐��@�T�C�Y�ŏo�͉摜�T�C�Y���w�肷��K�v�B�X�P�[���ł͂Ȃ��B
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

	////// ���摜�̒l���ɔz�u
	////for (int i = 0; i < width; i++)
	////{
	////	for (int j = 0; j < height; j = j++)
	////	{
	////		dstimg.at<cv::Vec3b>(j * 2, i * 2) = img.at<cv::Vec3b>(j, i);
	////	}
	////}

	// ��Ԃ̎�ނ̑I��
	if (method == 1)
	{ 
		// ���
		cv::Vec3b color = cv::Vec3b::all(0);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				// �@�P����2x2�̂S�ɃI���W�i���摜�̉�f�l��z�u
				color = img.at<cv::Vec3b>(j, i);
				dstimg.at<cv::Vec3b>(2 * j    , 2 * i    ) = color;  // ���łɔz�u�ς݂̂��߂���Ȃ�
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
				// �A���j�A���
				// 2x2�̍���
				dstimg.at<cv::Vec3b>(2 * j, 2 * i) = img.at<cv::Vec3b>(j, i);
				
				// 2x2�̍���
				if (j + 1 >= height) // �摜�̉��[�̔���
					color = img.at<cv::Vec3b>(j, i);
				else
					// ���y���Ӂz���������1/2�ɂ���ƁA��f�l���I�[�o�[�t���[����̂ŁA�e�X�������̂������B
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j + 1, i);
				dstimg.at<cv::Vec3b>(2 * j + 1, 2 * i) = color;

				// 2x2�̉E��
				if (i + 1 >= width) // �摜�̉E�[�̔���
					color = img.at<cv::Vec3b>(j, i);
				else
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j, i + 1);
				dstimg.at<cv::Vec3b>(2 * j, 2 * i + 1) = color;
				
				// 2x2�̉E��
				if (j + 1 >= height && i + 1 >= width) // �摜�̉E���p�̏ꍇ�A�I���W�i����f�l���Z�b�g
					color = img.at<cv::Vec3b>(j, i);
				else if (i + 1 >= width) // �摜�̉E�[�̏ꍇ�A����ƍ����̕��ς��Z�b�g
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j + 1, i);
				else if (j + 1 >= height) // �摜�̉��[�̏ꍇ�A����ƉE��̕��ς��Z�b�g
					color = 0.5 * img.at<cv::Vec3b>(j, i) + 0.5 * img.at<cv::Vec3b>(j, i + 1);
				else // �摜�̒��قǂɂ���ꍇ�́A���͂S�̕��ς��Z�b�g
					color = 0.25 * img.at<cv::Vec3b>(j, i) + 0.25 * dstimg.at<cv::Vec3b>(j, i + 1)
							+ 0.25 * img.at<cv::Vec3b>(j + 1, i) + 0.25 * dstimg.at<cv::Vec3b>(j + 1, i + 1);
				dstimg.at<cv::Vec3b>(2 * j + 1, 2 * i + 1) = color;
			}
		}
	}
	showimg("custom x2", dstimg);
}
