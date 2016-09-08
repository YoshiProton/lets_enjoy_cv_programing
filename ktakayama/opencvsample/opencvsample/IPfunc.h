#include "IPcommon.h"
#include "IPfilter.h"
#include "IPinterpolation.h"

class IPfunc
{
public:
	IPfunc();
	~IPfunc();

	// グレースケール化
	static void grayscale(const cv::Mat image, cv::Mat out);

	// HSVの値セット
	static void valueSetHSV(cv::Mat out, int H, int S, int V);

	// 肌検出
	static void skinDetect(const cv::Mat image, cv::Mat out);
};
