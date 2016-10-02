#ifndef __FILTER_HPP_
#define __FILTER_HPP_

#include "../include/imgproc.hpp"

namespace toyocv{
  class FilterBase{
  public:
    void apply(cv::InputArray _src, cv::OutputArray _dst, const int & ddepth=-1);
    void setKernel(cv::Mat &kerel_);
    
  private:
    cv::Mat kernel;

    double calcKernelOutput(const cv::Mat &src,
			    const cv::Mat &kernel, const int &w, const int &h,
			    const int &margineWidth, const int &margineHeight,			  
			    const int &kernelElemCount);

    double calcKernelOutputAtEdge(const cv::Mat &src,
				  const cv::Mat &kernel, int w, int h,
				  const int &imageWidth, const int &imageHeight,
				  const int &margineWidth, const int &margineHeight);

    bool isEdge(int w, int h,
		const int &imageWidth,
		const int &imageHeight,
		const int &margineWidth,
		const int &margineHeight);
  };

}

#endif
