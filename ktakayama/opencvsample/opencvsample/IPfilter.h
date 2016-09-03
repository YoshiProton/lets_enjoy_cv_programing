#include "IPcommon.h"

class IPfilter
{
private:
	static void filter(const cv::Mat image, cv::Mat out, cv::Mat filter);

public:
	IPfilter();
	~IPfilter();

	// 平均化フィルタ
	static void average(const cv::Mat image, cv::Mat out, const int size);
	static void average(const cv::Mat image, cv::Mat out);

	// ガウシアンフィルタ
	static void gaussian(const cv::Mat image, cv::Mat out, const float sigma, const int size);
	static void gaussian(const cv::Mat image, cv::Mat out, const float sigma);
	static void gaussian(const cv::Mat image, cv::Mat out);

	// ガウシアンフィルタ(パスカル)
	static void gaussian_pascal(const cv::Mat image, cv::Mat out, const int size);
	static void gaussian_pascal(const cv::Mat image, cv::Mat out);

	// プリューウィットフィルタ(横)
	static void prewitt_x(const cv::Mat image, cv::Mat out);
	// プリューウィットフィルタ(縦)
	static void prewitt_y(const cv::Mat image, cv::Mat out);

	// ソーベルフィルタ(横)
	static void sobel_x(const cv::Mat image, cv::Mat out);
	// ソーベルフィルタ(縦)
	static void sobel_y(const cv::Mat image, cv::Mat out);

	// ラプラシアンフィルタ
	static void laplacian(const cv::Mat image, cv::Mat out);

	// 鮮鋭化フィルタ
	static void sharpening(const cv::Mat image, cv::Mat out, const float scale);
	static void sharpening(const cv::Mat image, cv::Mat out);

	// メディアンフィルタ
	static void median(const cv::Mat image, cv::Mat out, int size);
	static void median(const cv::Mat image, cv::Mat out);

	// バイラテラルフィルタ
	static void bilateral(const cv::Mat image, cv::Mat out, const int size, const float sigma1, const float sigma2);
	static void bilateral(const cv::Mat image, cv::Mat out);
	static void bilateral(const cv::Mat image, cv::Mat out, const int size, const float sigma1, const float sigma2, const int loop);

	// ノンローカルミーンフィルタ
	static void nonlocalmean(const cv::Mat image, cv::Mat out, const int size1, const int size2, const float sigma);
	static void nonlocalmean(const cv::Mat image, cv::Mat out);
	static void nonlocalmean(const cv::Mat image, cv::Mat out, const int size1, const int size2, const float sigma, const int loop);
};
