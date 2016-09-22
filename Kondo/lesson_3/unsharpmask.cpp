#include "filter.h"

cv::Mat unsharpmask(const cv::Mat img, const int k)
{
	int size = 3;
	// ���ω��t�B���^�̃J�[�l���쐬
	float arnd = -1.0f / 9 * k;
	float cntr = 1.0f + 8.0 / 9 * k;
	cv::Mat kernel = (cv::Mat_<float>(size, size) << arnd, arnd, arnd, arnd, cntr, arnd, arnd, arnd, arnd);

	cv::Mat dstimg = img.clone();
	if (img.channels() == 1)
	{
		dstimg = difFilterCore(img, kernel);
	}
	else if (img.channels() == 3)
	{
		std::vector<cv::Mat> channels;
		std::vector<cv::Mat> channels_dst;
		cv::split(img, channels);
		channels_dst = channels; //�������A�G�b�W���������Ă��Ȃ��̂ŁA���̃R�s�[

		for (int ch = 0; ch < img.channels(); ch++)
		{
			channels_dst[ch] = difFilterCore(channels[ch], kernel);
		}
		cv::merge(channels_dst, dstimg);
	}
	
	return dstimg;
}