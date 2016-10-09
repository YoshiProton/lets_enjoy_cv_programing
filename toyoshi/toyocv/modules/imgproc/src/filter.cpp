#include "filter.hpp"

using namespace cv;

namespace toyocv{
  Mat FilterBase::diffTypeMul(const Mat &a, const Mat &b){
    int aDepth = a.depth();
    int bDepth = b.depth();

    try{
    
      if(aDepth == bDepth){
	return a.mul(b);
      }

      if(aDepth < bDepth){
	Mat c;
	a.convertTo(c, bDepth);

	return c.mul(b);
      }

      Mat c;
      b.convertTo(c, aDepth);
      return b.mul(c);
    }catch(...){
      std::cout << "dead in diffTypeMul" << std::endl;
    }
  }
  
  double FilterBase::calcKernelOutput(const Mat &src,
				      const Mat &kernel, const int &w, const int &h,
				      const int &margineWidth, const int &margineHeight,
				      const double &kernelElemCount)
  {
    double output = 0;

    try{
      Mat subMat = src(Rect(w - margineWidth, h - margineHeight, kernel.cols, kernel.rows));
    
      Mat mulKernel = diffTypeMul(subMat, kernel);

      output += (double)sum(mulKernel)[0];
      return output / kernelElemCount;
    }catch(...){
      std::cout << "dead in calcKernelOutput" << std::endl;
    }
  }

  double FilterBase::calcKernelOutputAtEdge(const Mat &src,
					    const Mat &kernel, int w, int h,
					    const int &imageWidth, const int &imageHeight,
					    const int &margineWidth, const int &margineHeight)
  {
    double output = 0;

    int roiWidth = kernel.cols;
    int roiHeight = kernel.rows;

    Rect kernelRoi = Rect(0, 0, kernel.cols, kernel.rows);

    w -= margineWidth;
    h -= margineHeight;

    if (w < 0){
      roiWidth += w;
      kernelRoi.width += w;
      kernelRoi.x -= w;
      w = 0;
    }
    if (h < 0){
      roiHeight += h;
      kernelRoi.height += h;
      kernelRoi.y -= h;
      h = 0;
    }

    if (w + margineWidth * 2 > imageWidth - 2){
      int diff = w + 2 * margineWidth + 1 - imageWidth + 1;
      roiWidth -= diff;
      kernelRoi.width -= diff;
    }
    if (h + margineHeight * 2 > imageHeight - 2){
      int diff = h + 2 * margineHeight + 1 - imageHeight + 1;
      roiHeight -= diff;
      kernelRoi.height -= diff;
    }
    Mat subMat = src(Rect(w, h, roiWidth, roiHeight));
    Mat mulKernel = diffTypeMul(subMat, kernel(kernelRoi));  //subMat.mul(kernel(kernelRoi));

    output += (double)sum(mulKernel)[0] / (kernelRoi.width * kernelRoi.height);

    return output;
  }

  bool FilterBase::isEdge(int w, int h, const int &imageWidth, const int &imageHeight, const int &margineWidth, const int &margineHeight)
  {
    w -= margineWidth + 1;
    h -= margineHeight + 1;
    
    if (w < 0 || w + margineWidth * 2 > imageWidth - 2)
      return true;

    if (h < 0 || h + margineHeight * 2 > imageHeight - 2)
      return true;

    return false;
  }

  void FilterBase::apply(cv::InputArray _src, cv::OutputArray _dst, const int &ddepth){
    int stype = _src.type();
    int dcn = _src.channels();
    int depth = CV_MAT_DEPTH(stype);

    if (0 <= ddepth)
      depth = ddepth;

    Mat src, dst;
    src = _src.getMat();

    Size sz = src.size();

    _dst.create(sz, CV_MAKETYPE(depth, dcn));
    dst = _dst.getMat();

    int imageWidth = src.rows;
    int imageHeight = src.cols;

    Mat srcChannels[3];
    split(src, srcChannels);

    int margineWidth = kernel.cols / 2;
    int margineHeight = kernel.rows / 2;
    double kernelElemCount = (double)(kernel.cols * kernel.rows);

    for(int ch = 0; ch < dcn; ++ch){
      for(int y = 0; y < imageHeight; ++y){
	Vec3d  *ptr = dst.ptr<Vec3d>(y);
	for(int x = 0; x < imageWidth; ++x){
	  if (isEdge(x, y, imageWidth, imageHeight, margineWidth, margineWidth)){
	    ptr[x][ch]
	      = calcKernelOutputAtEdge(srcChannels[ch],
				       kernel, x, y,
				       imageWidth, imageHeight,
				       margineWidth, margineHeight);
	  }else{
	    ptr[x][ch]
	      = calcKernelOutput(srcChannels[ch],
				 kernel, x, y,
				 margineWidth, margineHeight,				 
				 kernelElemCount);
	  }
	}
      }
    }
  }

  void FilterBase::setKernel(cv::Mat &kernel_){
    kernel = kernel_;
  }
}

