// ���ω��t�B���^
#include "filter.h"

//
// �l��min:max���ɁAsymmetric�ɖ߂��B
// ��Fmin=0�̂Ƃ��A-2 -> 2
//     max = 100�̂Ƃ��A101->99
int getRestricted(const int in, const int min, const int max)
{
	if (in < min)
	{
		return -(in - min);
	}
	else if (in > max)
	{
		return (2 * max - in);
	}
	else
	{
		return in;
	}
}

//
// img��(x,y)�𒆐S�Ƃ����Akernel�Ƃ̃R���{���[�V���� 
//
int convolute(const int x, const int y,  const cv::Mat img, const cv::Mat kernel)
{
	float ave = 0.0;
	int ksize = kernel.cols;
	int margin = ksize / 2;
	// ���̈�̌v�Z
	for (int wy = 0; wy < ksize; wy++)
	{
		for (int wx = 0; wx < ksize; wx++)
		{
			float kernelv = kernel.at<float>(wy, wx);
			int winx = getRestricted(x + wx - margin, 0, img.cols - 1);
			int winy = getRestricted(y + wy - margin, 0, img.rows - 1);
			int winval = img.at<uchar>(winy, winx);
			ave += kernelv * winval;
		}
	}
	return (int)ave;
}


// �s�񓯎m�̐Ϙa���v�Z����B
// �l�X�ȃt�B���^�̃R�A�̌v�Z�ɗ��p
float multSumMat(const cv::Mat kernel, const cv::Mat trg)
{
	float mulsum = 0.0;
	int size = kernel.cols;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mulsum += trg.at<uchar>(j, i) * kernel.at<float>(j, i);
	return mulsum;
}


//
// ���ω��t�B���^
//
cv::Mat averageFilter(const cv::Mat img, const int ksize)
{
	// ���ω��t�B���^�̃J�[�l���쐬
	cv::Mat kernel = cv::Mat::ones(ksize, ksize, CV_32F);
	double area = ksize*ksize;
	double kernelaverage = 1.0f / area;
	kernel *= kernelaverage;

	// �G�b�W�̏����͂��Ȃ��̂ŁA�I���W�i���摜���R�s�[
	cv::Mat dstimg = img.clone();

	// �����̊ȗ����̂��߁A�G�b�W���ӂ̏��������Ă��Ȃ��o�[�W����
	// �O���[�摜
	if (img.channels() == 1)
	{		
		// �G�b�W��������
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// �Ϙa�����l�����ʂɁB(int)�Œl�̐؂�̂�
				dstimg.at<uchar>(y, x) = convolute(x, y, img, kernel);
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

		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// channels���ɕ��ω�����
				for (int i = 0; i < channels.size(); i++)
				{
					channels_dst[i].at<uchar>(y, x) = convolute(x, y, channels[i], kernel);
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] �G�b�W���ӂ̏������l�������o�[�W���������

	return dstimg;
}

