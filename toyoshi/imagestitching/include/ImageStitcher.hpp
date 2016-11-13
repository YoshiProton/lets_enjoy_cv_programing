#ifndef __IMAGE_STICHER_HPP__
#define __IMAGE_STICHER_HPP__

#include <opencv2/opencv.hpp>


class ImageStitcher{
public:
  cv::Mat stitch(const cv::Mat* images);

private:
  const uint ransacTrial = 1000;
  
  cv::Mat descriptFeatures(const cv::Mat &image, std::vector<cv::KeyPoint> &corners);
  std::vector<cv::DMatch> calcSiftMatch(const cv::Mat *descriptors);
  cv::Mat createEquationA(std::vector<cv::DMatch> DMatch,
			  const std::vector<cv::KeyPoint> *corners);
  cv::Mat createEquationb(std::vector<cv::DMatch> dmatch,
			   const cv::vector<cv::KeyPoint> *corners);
  cv::Mat solveEquation(const cv::Mat &A, const cv::Mat &b);
  cv::Mat selectRows(const cv::Mat &src, const std::vector<int> &rand_array);
  template <typename T> std::vector<T> selectVector(const std::vector<T> &src,
						    const std::vector<int> &index);
  cv::Mat solve(const std::vector<cv::DMatch> &origDmatch,
		const std::vector<cv::KeyPoint> *corners);


};

#endif
