#include "filter.h"

cv::Mat difFilterCore(cv::Mat img, cv::Mat kernel)
{
	cv::Mat dstimg = cv::Mat::zeros(img.size(), CV_8UC1); // �����ŏ��������Ă����Ȃ��ƁA����at���g��������ŃG���[���ł�B
	int ksize = kernel.cols;

	if (img.channels() == 3)
	{
		// �J���[�摜�ւ̃G�b�W�t�B���^�͂Ȃ��H
	}

	if (img.channels() == 1)
	{
		int margin = ksize / 2; // �G�b�W���ӂ̃}�[�W�������B
		cv::Mat reg;
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				// (size x size)�̗̈�̉摜��kernel�̗v�f���m�̐ς��v�Z
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();
				float mulsum = multSumMat(kernel, reg);
				// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
				// �������v�Z����ƁA�������ł�̂ŁA��Βl���Ƃ�B
				dstimg.at<uchar>(y, x) = (int)abs(mulsum);
			}
		}
	}
	return dstimg;
}


cv::Mat diffFileter(cv::Mat img, int direction)
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



cv::Mat prewitt(cv::Mat img, int direction)
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


cv::Mat sobel(cv::Mat img, int direction)
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



cv::Mat laplacianFilter(cv::Mat img)
{
	int size = 3;
	// ���ω��t�B���^�̃J�[�l���쐬
	cv::Mat kernel = (cv::Mat_<float>(size, size) << 0, 1.0, 0, 1.0, -4.0, 1.0, 0, 1.0, 0);

	cv::Mat dstimg = difFilterCore(img, kernel);
	return dstimg;
}
