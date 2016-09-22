// 平均化フィルタ
#include "filter.h"

//
// 値をmin:max内に、symmetricに戻す。
// 例：min=0のとき、-2 -> 2
//     max = 100のとき、101->99
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
// imgの(x,y)を中心とした、kernelとのコンボリーション 
//
int convolute(const int x, const int y,  const cv::Mat img, const cv::Mat kernel)
{
	float ave = 0.0;
	int ksize = kernel.cols;
	int margin = ksize / 2;
	// 小領域の計算
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


// 行列同士の積和を計算する。
// 様々なフィルタのコアの計算に利用
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
// 平均化フィルタ
//
cv::Mat averageFilter(const cv::Mat img, const int ksize)
{
	// 平均化フィルタのカーネル作成
	cv::Mat kernel = cv::Mat::ones(ksize, ksize, CV_32F);
	double area = ksize*ksize;
	double kernelaverage = 1.0f / area;
	kernel *= kernelaverage;

	// エッジの処理はしないので、オリジナル画像をコピー
	cv::Mat dstimg = img.clone();

	// 処理の簡略化のため、エッジ周辺の処理をしていないバージョン
	// グレー画像
	if (img.channels() == 1)
	{		
		// エッジ処理込み
		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// 積和した値を結果に。(int)で値の切り捨て
				dstimg.at<uchar>(y, x) = convolute(x, y, img, kernel);
			}
		}
	}
	else if (img.channels() == 3)
	{
		//（カラーの場合は各BGRに、grayimgへと同じ処理）
		// BGRに対して、grayへの処理を再帰呼び出ししてもよさそうだが、
		// x,yのfor分が余計になりそうなので、コアの処理をBGRのループにした。
		std::vector<cv::Mat> channels;
		std::vector<cv::Mat> channels_dst;
		cv::split(img, channels);
		channels_dst = channels; //ここも、エッジ処理をしていないので、元のコピー

		for (int y = 0; y < img.rows; y++)
		{
			for (int x = 0; x < img.cols; x++)
			{
				// channels毎に平均化処理
				for (int i = 0; i < channels.size(); i++)
				{
					channels_dst[i].at<uchar>(y, x) = convolute(x, y, channels[i], kernel);
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] エッジ周辺の処理も考慮したバージョンを作る

	return dstimg;
}

