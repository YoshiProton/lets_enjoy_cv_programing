#include "IPcommon.h"

class IPfilter
{
private:
	static void filter(const cv::Mat image, cv::Mat out, cv::Mat filter);

public:
	IPfilter();
	~IPfilter();

	// ���ω��t�B���^
	static void average(const cv::Mat image, cv::Mat out, const int size);
	static void average(const cv::Mat image, cv::Mat out);

	// �K�E�V�A���t�B���^
	static void gaussian(const cv::Mat image, cv::Mat out, const float sigma, const int size);
	static void gaussian(const cv::Mat image, cv::Mat out, const float sigma);
	static void gaussian(const cv::Mat image, cv::Mat out);

	// �K�E�V�A���t�B���^(�p�X�J��)
	static void gaussian_pascal(const cv::Mat image, cv::Mat out, const int size);
	static void gaussian_pascal(const cv::Mat image, cv::Mat out);

	// �v�����[�E�B�b�g�t�B���^(��)
	static void prewitt_x(const cv::Mat image, cv::Mat out);
	// �v�����[�E�B�b�g�t�B���^(�c)
	static void prewitt_y(const cv::Mat image, cv::Mat out);

	// �\�[�x���t�B���^(��)
	static void sobel_x(const cv::Mat image, cv::Mat out);
	// �\�[�x���t�B���^(�c)
	static void sobel_y(const cv::Mat image, cv::Mat out);

	// ���v���V�A���t�B���^
	static void laplacian(const cv::Mat image, cv::Mat out);

	// �N�s���t�B���^
	static void sharpening(const cv::Mat image, cv::Mat out, const float scale);
	static void sharpening(const cv::Mat image, cv::Mat out);

	// ���f�B�A���t�B���^
	static void median(const cv::Mat image, cv::Mat out, int size);
	static void median(const cv::Mat image, cv::Mat out);

	// �o�C���e�����t�B���^
	static void bilateral(const cv::Mat image, cv::Mat out, const int size, const float sigma1, const float sigma2);
	static void bilateral(const cv::Mat image, cv::Mat out);
	static void bilateral(const cv::Mat image, cv::Mat out, const int size, const float sigma1, const float sigma2, const int loop);

	// �m�����[�J���~�[���t�B���^
	static void nonlocalmean(const cv::Mat image, cv::Mat out, const int size1, const int size2, const float sigma);
	static void nonlocalmean(const cv::Mat image, cv::Mat out);
	static void nonlocalmean(const cv::Mat image, cv::Mat out, const int size1, const int size2, const float sigma, const int loop);
};
