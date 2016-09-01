// ���ω��t�B���^
#include "filter.h"


// �s�񓯎m�̐Ϙa���v�Z����B
// �l�X�ȃt�B���^�̃R�A�̌v�Z�ɗ��p
float multSumMat(cv::Mat kernel, cv::Mat trg)
{
	float mulsum = 0.0;
	int size = kernel.cols;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mulsum += trg.at<uchar>(j, i) * kernel.at<float>(j, i);
	return mulsum;
}

//


cv::Mat averageFilter(cv::Mat img, int size)
{
	// ���ω��t�B���^�̃J�[�l���쐬
	cv::Mat kernel = cv::Mat::ones(size, size, CV_32F);
	double area = size*size;
	double kernelaverage = 1.0f / area;
	kernel *= kernelaverage;

	// �G�b�W�̏����͂��Ȃ��̂ŁA�I���W�i���摜���R�s�[
	cv::Mat dstimg = img.clone();

	// �����̊ȗ����̂��߁A�G�b�W���ӂ̏��������Ă��Ȃ��o�[�W����
	// �O���[�摜
	if (img.channels() == 1)
	{
		int margin = size / 2; // �G�b�W���ӂ̃}�[�W�������B
		cv::Mat reg;
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
			{
				// (size x size)�̗̈�̉摜��kernel�̗v�f���m�̐ς��v�Z
				reg = img(cv::Rect(x - margin, y - margin, size, size)).clone();
				float ave = multSumMat(kernel, reg);
				// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
				dstimg.at<uchar>(y, x) = (int)ave;
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

		int margin = size / 2; // �������Ȃ��G�b�W���ӂ̃}�[�W���B
		cv::Mat reg;
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
			{
				// channels���ɕ��ω�����
				for (int i = 0; i < channels.size(); i++)
				{
					// (size x size)�̗̈�̉摜��kernel�̗v�f���m�̐ς��v�Z
					reg = channels[i](cv::Rect(x - margin, y - margin, size, size)).clone();
					float ave = multSumMat(kernel, reg);
					// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
					channels_dst[i].at<uchar>(y, x) = (int)ave;
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] �G�b�W���ӂ̏������l�������o�[�W���������

	return dstimg;
}

