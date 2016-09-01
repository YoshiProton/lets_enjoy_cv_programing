// 平均化フィルタ
#include "filter.h"


// 行列同士の積和を計算する。
// 様々なフィルタのコアの計算に利用
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
	// 平均化フィルタのカーネル作成
	cv::Mat kernel = cv::Mat::ones(size, size, CV_32F);
	double area = size*size;
	double kernelaverage = 1.0f / area;
	kernel *= kernelaverage;

	// エッジの処理はしないので、オリジナル画像をコピー
	cv::Mat dstimg = img.clone();

	// 処理の簡略化のため、エッジ周辺の処理をしていないバージョン
	// グレー画像
	if (img.channels() == 1)
	{
		int margin = size / 2; // エッジ周辺のマージンを取る。
		cv::Mat reg;
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
			{
				// (size x size)の領域の画像とkernelの要素同士の積を計算
				reg = img(cv::Rect(x - margin, y - margin, size, size)).clone();
				float ave = multSumMat(kernel, reg);
				// 積和した値を結果に。(int)で値の切り捨て
				dstimg.at<uchar>(y, x) = (int)ave;
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

		int margin = size / 2; // 処理しないエッジ周辺のマージン。
		cv::Mat reg;
		for (int x = margin; x < img.rows - margin; x++)
		{
			for (int y = margin; y < img.cols - margin; y++)
			{
				// channels毎に平均化処理
				for (int i = 0; i < channels.size(); i++)
				{
					// (size x size)の領域の画像とkernelの要素同士の積を計算
					reg = channels[i](cv::Rect(x - margin, y - margin, size, size)).clone();
					float ave = multSumMat(kernel, reg);
					// 積和した値を結果に。(int)で値の切り捨て
					channels_dst[i].at<uchar>(y, x) = (int)ave;
				}
			}
		}
		cv::merge(channels_dst, dstimg);
	}
	// [TO DO] エッジ周辺の処理も考慮したバージョンを作る

	return dstimg;
}

