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
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
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
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
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




cv::Mat bilateralFilter(cv::Mat img, int ksize, float sigma_xy, float sigma_color)
{
	// �G�b�W�̏����͂��Ȃ��̂ŁA�I���W�i���摜���R�s�[
	cv::Mat dstimg = img.clone();

	// �����̊ȗ����̂��߁A�G�b�W���ӂ̏��������Ă��Ȃ��o�[�W����
	// �O���[�摜
	if (img.channels() == 1)
	{
		int margin = ksize / 2; // �G�b�W���ӂ̃}�[�W�������B
		cv::Mat reg = cv::Mat::zeros(ksize, ksize, CV_8UC1); // �̈�̊m��
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();

				float blval = bilateralCore(reg, sigma_xy, sigma_color);
				dstimg.at<uchar>(y, x) = (int)blval;
			}
		}
	}
	else if (img.channels() == 3)
	{
		// �J���[�Ή�
	}


	return dstimg;
}

float bilateralCore(cv::Mat reg, float sigma_xy, float sigma_color)
{
	float weight_sum = 0.0;			// �d�݂̘a
	float weightedcolor_sum = 0.0;	//�d�݂���������f�l�̘a
	float weight_xy = 0.0;			// ��ԕ����̏d��
	float weight_color = 0.0;		// �F��ԕ����̏d��
	float weight_ij = 0.0;			// ��ԁA�F��Ԃ̏d�݂̐�
	double r2 = 0;					// x^2 + y^2
	int rc2 = 0;					// �F��Ԃł̍��̂Q��
	int cx = reg.cols / 2 + 1;		// �̈�̒��S(x,y)
	int cy = cx;
	double inv_sigma_xy2 = 1 / (sigma_xy * sigma_xy);			// ��ԕ������U�̂Q��̋t��
	double inv_sigma_color2 = 1 / (sigma_color * sigma_color);	// �F��ԕ������U�̂Q��̋t��
	int color_ij = 0;						//�l���ʒu�̉�f�l
	int color_cnt = reg.at<uchar>(cy, cx);	// ���S�̉�f�l
	float weightedcolor_ij = 0.0;			// �d�݂���������f�l
	float res_color = 0.0;		// �ŏI���ʉ�f
	 
	for (int i = 0; i < reg.rows; i++)
	{
		for (int j = 0; j < reg.cols; j++)
		{
			// ��ԕ����̏d�݂̌v�Z
			r2 = (i - cx)* (i - cx) + (j - cy)*(j - cy);
			weight_xy = exp(-r2 * 0.5 * inv_sigma_xy2);
			// �F��ԕ����̉�f�l�̍��A�d�݂̌v�Z
			color_ij = reg.at<uchar>(i, j);
			rc2 = (color_ij - color_cnt) * (color_ij - color_cnt);
			weight_color = exp(-0.5 * rc2 * inv_sigma_color2);
			// ��ԕ����A�F��ԕ����̏d�݂̐�
			weight_ij = weight_xy * weight_color;			
			weight_sum += weight_ij;
			// �d�݂̂���������f�l�̌v�Z
			weightedcolor_ij = color_ij * weight_ij;
			weightedcolor_sum += weightedcolor_ij;
		}
	}
	res_color = weightedcolor_sum / weight_sum;

	return res_color;
}



cv::Mat nonlocalmean(cv::Mat img)
{
	cv::Mat dstimg;

	return dstimg;
}

