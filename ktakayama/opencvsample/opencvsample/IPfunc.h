#include "IPcommon.h"
#include "IPfilter.h"

class IPfunc
{
public:
	IPfunc();
	~IPfunc();

	// グレースケール化
	static void grayscale(const cv::Mat image, cv::Mat out);

	// サイズ変更(Nearest Neighbor)
	static void resizeNN(const cv::Mat image, cv::Mat out, const double scale);

	// HSVの値セット
	static void valueSetHSV(cv::Mat out, int H, int S, int V);

	// 肌検出
	static void skinDetect(const cv::Mat image, cv::Mat out);
};
