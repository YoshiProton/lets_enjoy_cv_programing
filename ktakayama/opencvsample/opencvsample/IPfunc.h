#include "IPcommon.h"
#include "IPfilter.h"

class IPfunc
{
public:
	IPfunc();
	~IPfunc();

	// �O���[�X�P�[����
	static void grayscale(const cv::Mat image, cv::Mat out);

	// �T�C�Y�ύX(Nearest Neighbor)
	static void resizeNN(const cv::Mat image, cv::Mat out, const double scale);

	// HSV�̒l�Z�b�g
	static void valueSetHSV(cv::Mat out, int H, int S, int V);

	// �����o
	static void skinDetect(const cv::Mat image, cv::Mat out);
};
