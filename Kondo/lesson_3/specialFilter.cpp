#include "filter.h"


int getMedianVal(const int x, const int y, const cv::Mat img, const int ksize)
{
	int center = ksize * ksize / 2 + 1;
	int margin = ksize / 2;
	std::vector<int> vec;

	// �G�b�W��������
	for (int wy = 0; wy < ksize; wy++)
	{
		for (int wx = 0; wx < ksize; wx++)
		{
			int winx = getRestricted(x + wx - margin, 0, img.cols - 1);
			int winy = getRestricted(y + wy - margin, 0, img.rows - 1);
			vec.push_back(img.at<uchar>(winy, winx));
		}
	}
	std::sort(vec.begin(), vec.end());

	return vec[center];
}

cv::Mat medianFilter(const cv::Mat img, const int ksize)
{
	// �G�b�W�̏����͂��Ȃ��̂ŁA�I���W�i���摜���R�s�[
	cv::Mat dstimg = img.clone();
	int center = ksize*ksize / 2 + 1;

	// �����̊ȗ����̂��߁A�G�b�W���ӂ̏��������Ă��Ȃ��o�[�W����
	// �O���[�摜
	if (img.channels() == 1)
	{
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// (x,y)�𒆐S�Ƃ���̈�̒��Ԓn�̎擾
				dstimg.at<uchar>(y, x) = getMedianVal(x, y, img, ksize);
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
					// x,y�𒆐S�Ƃ������Ԓl�̌v�Z
					channels_dst[i].at<uchar>(y, x) = getMedianVal(x, y, channels[i], ksize);
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] �G�b�W���ӂ̏������l�������o�[�W���������

	return dstimg;
}




cv::Mat bilateralFilter(const cv::Mat img, const int ksize, const float sigma_xy, const float sigma_color)
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
		int margin = ksize / 2; // �G�b�W���ӂ̃}�[�W�������B
		cv::Mat reg = cv::Mat::zeros(ksize, ksize, CV_8UC1); // �̈�̊m��
		for (int y = margin; y < img.rows - margin; y++)
		{
			for (int x = margin; x < img.cols - margin; x++)
			{
				reg = img(cv::Rect(x - margin, y - margin, ksize, ksize)).clone();

				cv::Vec3b blval = bilateralCoreColor(reg, sigma_xy, sigma_color);
				for (int k = 0; k < 3; k++)
				{
					dstimg.at<cv::Vec3b>(y, x)[k] = blval[k];
				}
			}
		}
	}

	return dstimg;
}



float bilateralCore(cv::Mat reg, float sigma_xy, float sigma_color)
{
	float weight_sum = 0.0;			// �d�݂̘a
	float weightedcolor_sum = 0.0;	// �d�݂���������f�l�̘a
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


cv::Vec3f bilateralCoreColor(cv::Mat reg, float sigma_xy, float sigma_color)
{
	float weight_sum = 0.0;			// �d�݂̘a
	cv::Vec3f weightedcolor_sum = cv::Vec3f(0, 0, 0);	// �d�݂���������f�l�̘a
	float weight_xy = 0.0;			// ��ԕ����̏d��
	float weight_color = 0.0;		// �F��ԕ����̏d��
	float weight_ij = 0.0;			// ��ԁA�F��Ԃ̏d�݂̐�
	double r2 = 0;					// x^2 + y^2
	int rc2 = 0;					// �F��Ԃł̍��̂Q��
	int cx = reg.cols / 2 + 1;		// �̈�̒��S(x,y)
	int cy = cx;
	double inv_sigma_xy2 = 1 / (sigma_xy * sigma_xy);			// ��ԕ������U�̂Q��̋t��
	double inv_sigma_color2 = 1 / (sigma_color * sigma_color);	// �F��ԕ������U�̂Q��̋t��
	cv::Vec3b color_ij = 0;						//�l���ʒu�̉�f�l
	cv::Vec3b color_cnt = reg.at<cv::Vec3b>(cy, cx);	// ���S�̉�f�l
	cv::Vec3f weightedcolor_ij = cv::Vec3f(0, 0, 0);	// �d�݂���������f�l
	cv::Vec3f res_color = cv::Vec3f(0, 0, 0);		// �ŏI���ʉ�f

	for (int i = 0; i < reg.rows; i++)
	{
		for (int j = 0; j < reg.cols; j++)
		{
			// ��ԕ����̏d�݂̌v�Z
			r2 = (i - cx)* (i - cx) + (j - cy)*(j - cy);
			weight_xy = exp(-r2 * 0.5 * inv_sigma_xy2);

			// �F��ԕ����̉�f�l�̍��A�d�݂̌v�Z
			color_ij = reg.at<cv::Vec3b>(i, j);
			rc2 = colordist2(color_cnt, color_ij);
			weight_color = exp(-0.5 * rc2 * inv_sigma_color2);

			// ��ԕ����A�F��ԕ����̏d�݂̐�		 
			weight_ij = weight_xy * weight_color;
			weight_sum += weight_ij;

			// �d�݂̂���������f�l�̌v�Z
			weightedcolor_ij = color_ij * weight_ij;
			for (int k = 0; k < 3; k++)
			{
				weightedcolor_sum[k] += weightedcolor_ij[k];
			}
		}
	}
	res_color = weightedcolor_sum / weight_sum;

	return res_color;

}


// RGB��Ԃł̉�f�l�̍��̂Q����v�Z
int colordist2(cv::Vec3b color1, cv::Vec3b color2)
{
	float colordistance = 0.0;
	int dif_sum = 0;
	for (int i = 0; i < color1.channels; i++)
	{
		int difs = color1[i] - color2[i];
		dif_sum += difs*difs;
	}

	return colordistance;
}


cv::Mat nonlocalmean(cv::Mat img)
{
	cv::Mat dstimg;

	return dstimg;
}

