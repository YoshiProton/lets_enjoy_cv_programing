#include "IPcommon.h"
#include "IPfilter.h"
#include "IPinterpolation.h"

class IPfunc
{
public:
	IPfunc();
	~IPfunc();

	// �O���[�X�P�[����
	static void grayscale(const cv::Mat image, cv::Mat out);

	// HSV�̒l�Z�b�g
	static void valueSetHSV(cv::Mat out, int H, int S, int V);

	// �����o
	static void skinDetect(const cv::Mat image, cv::Mat out);
};
