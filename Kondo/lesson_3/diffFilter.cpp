#include "filter.h"

cv::Mat difFilterCore(const cv::Mat img, const cv::Mat kernel)
{
	cv::Mat dstimg = cv::Mat::zeros(img.size(), CV_8UC1); // �����ŏ��������Ă����Ȃ��ƁA����at���g��������ŃG���[���ł�B
	int ksize = kernel.cols;

	if (img.channels() == 3)
	{
		// �J���[�摜�ւ̃G�b�W�t�B���^�͂Ȃ��H
	}

	if (img.channels() == 1)
	{
		// �G�b�W��������
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
				int conv = convolute(x, y, img, kernel);
				dstimg.at<uchar>(y, x) = abs(conv);
			}
		}
	}
	return dstimg;
}


cv::Mat diffFileter(const cv::Mat img, const int direction)
{
	int size = 3;
	// �����t�B���^�̃J�[�l���쐬
	cv::Mat kernel;
	switch (direction)
	{
		case HORIZONTAL:
			kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, -0.5, 0, 0.5, 0, 0, 0);
			break;
		case LONGITUDIAL:
			kernel = (cv::Mat_<float>(size, size) << 0, 0.5, 0, 0, 0, 0, 0, -0.5, 0);
			break;
		default:
			kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	}
	cv::Mat dstimg = difFilterCore(img, kernel);

	return dstimg;
}



cv::Mat prewitt(const cv::Mat img, const int direction)
{
	int size = 3;
	// ���ω��t�B���^�̃J�[�l���쐬
	cv::Mat kernel;
	switch (direction)
	{
	case HORIZONTAL:
		kernel = (cv::Mat_<float>(size, size) << -1.0, 0, 1.0, -1.0, 0, 1.0, -1.0, 0, 1.0);
		kernel = kernel * 1.0f / 6;
		break;
	case LONGITUDIAL:
		kernel = (cv::Mat_<float>(size, size) << 1.0, 1.0, 1.0, 0, 0, 0, -1.0, -1.0, -1.0);
		kernel = kernel * 1.0f / 6;
		break;
	default:
		kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	}
	
	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}


cv::Mat sobel(const cv::Mat img, const int direction)
{
	int size = 3;
	// ���ω��t�B���^�̃J�[�l���쐬
	cv::Mat kernel;
	switch (direction)
	{
	case HORIZONTAL:
		kernel = (cv::Mat_<float>(size, size) << -1.0, 0, 1.0, -2.0, 0, 2.0, -1.0, 0, 1.0);
		kernel = kernel * 1.0f / 8;
		break;
	case LONGITUDIAL:
		kernel = (cv::Mat_<float>(size, size) << 1.0, 2.0, 1.0, 0, 0, 0, -1.0, -2.0, -1.0);
		kernel = kernel * 1.0f / 8;
		break;
	default:
		kernel = (cv::Mat_<float>(size, size) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	}

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}



cv::Mat laplacianFilter(const cv::Mat img)
{
	int size = 3;
	// ���ω��t�B���^�̃J�[�l���쐬
	cv::Mat kernel = (cv::Mat_<float>(size, size) << 0, 1.0, 0, 1.0, -4.0, 1.0, 0, 1.0, 0);

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}
