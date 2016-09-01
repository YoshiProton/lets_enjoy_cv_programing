#include "filter.h"


int getMedianVal(cv::Mat reg, int center)
{
	std::vector<int> vec; 
	cv::Mat reshaped = reg.reshape(1, 1); //1channel, 1�s��reshape

	for (int i = 0; i < reshaped.cols; i++)
	{
		vec.push_back(reshaped.at<uchar>(0, i));
	}
	std::sort(vec.begin(), vec.end());

	return vec[center];
}

cv::Mat medianFilter(cv::Mat img, int ksize)
{
	// �G�b�W�̏����͂��Ȃ��̂ŁA�I���W�i���摜���R�s�[
	cv::Mat dstimg = img.clone();
	int center = ksize*ksize / 2 + 1;

	// �����̊ȗ����̂��߁A�G�b�W���ӂ̏��������Ă��Ȃ��o�[�W����
	// �O���[�摜
	if (img.channels() == 1)
	{
		int margin = ksize / 2; // �G�b�W���ӂ̃}�[�W�������B
		cv::Mat reg;
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
			{
				// (size x size)�̗̈�̉摜��kernel�̗v�f���m�̐ς��v�Z
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();
				
				int med = getMedianVal(reg, center);

				// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
				dstimg.at<uchar>(y, x) = med;
			}
		}
	}
	else if (img.channels() == 3)
	{
		//�i�J���[�̏ꍇ�͊eBGR�ɁAgrayimg�ւƓ��������j
		// BGR�ɑ΂��āAgray�ւ̏������ċA�Ăяo�����Ă��悳���������A
		// x,y��for�����]�v�ɂȂ肻���Ȃ̂ŁA�R�A�̏�����BGR�̃��[�v�ɂ����B
		std::vector<cv::Mat> channels;
		std::vector<cv::Mat> channels_dst;
		cv::split(img, channels);
		channels_dst = channels; //�������A�G�b�W���������Ă��Ȃ��̂ŁA���̃R�s�[

		int margin = ksize / 2; // �������Ȃ��G�b�W���ӂ̃}�[�W���B
		cv::Mat reg;
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
			{
				// channels���ɕ��ω�����
				for (int i = 0; i < channels.size(); i++)
				{
					// (size x size)�̗̈�̉摜��kernel�̗v�f���m�̐ς��v�Z
					reg = channels[i](cv::Rect(x - margin, y - margin, ksize, ksize)).clone();
					int med = getMedianVal(reg, center);
					// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
					channels_dst[i].at<uchar>(y, x) = med;
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] �G�b�W���ӂ̏������l�������o�[�W���������

	return dstimg;
}




cv::Mat bilateralFilter(cv::Mat img, int sigma_x, int sigma_color)
{
	cv::Mat dstimg;

	return dstimg;
}

cv::Mat nonlocalmean(cv::Mat img)
{
	cv::Mat dstimg;

	return dstimg;
}

