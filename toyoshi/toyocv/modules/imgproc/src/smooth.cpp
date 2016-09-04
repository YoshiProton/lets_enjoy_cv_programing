#include "../include/imgproc.hpp"

using namespace cv;

namespace toyocv{
  double calcKernelOutput(const Mat &src,
			  const Mat &kernel, const int &w, const int &h,
			  const int &margineWidth, const int &margineHeight,			  
			  const int &kernelElemCount)
  {
    double output = 0;

    Mat subMat = src(Rect(w - margineWidth, h - margineHeight, kernel.cols, kernel.rows));
    Mat mulKernel = subMat.mul(kernel);

    output += (double)sum(mulKernel)[0];
    return output / kernelElemCount;
  }

  double calcKernelOutputAtEdge(const Mat &src,
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
    Mat mulKernel = subMat.mul(kernel(kernelRoi));

    output += (double)sum(mulKernel)[0] / (kernelRoi.width * kernelRoi.height);

    return output;
  }

  bool isEdge(int w, int h, const int &imageWidth, const int &imageHeight, const int &margineWidth, const int &margineHeight)
  {
    w -= margineWidth + 1;
    h -= margineHeight + 1;
    
    if (w < 0 || w + margineWidth * 2 > imageWidth - 2)
      return true;

    if (h < 0 || h + margineHeight * 2 > imageHeight - 2)
      return true;

    return false;
  }

  void blur(InputArray _src, OutputArray _dst,
	    Size ksize, Point anchor, int borderType){
    int stype = _src.type();
    int dcn = _src.channels();
    int depth = CV_MAT_DEPTH(stype);
    
    Mat src, dst;
    src = _src.getMat();

    Size sz = src.size();

    _dst.create(sz, CV_MAKETYPE(depth, dcn));
    dst = _dst.getMat();

    int imageWidth = src.rows;
    int imageHeight = src.cols;

    Mat kernel = Mat::ones(ksize, CV_8UC1);

    Mat srcChannels[3];
    split(src, srcChannels);

    int margineWidth = kernel.cols / 2;
    int margineHeight = kernel.rows / 2;
    double kernelElemCount = (double)(kernel.cols * kernel.rows);
    
    for(int ch = 0; ch < dcn; ++ch){
      for(int x = 0; x < imageWidth; ++x){
	for(int y = 0; y < imageHeight; ++y){

	  if (isEdge(x, y, imageWidth, imageHeight, margineWidth, margineWidth)){
	    dst.at<Vec3b>(y, x).val[ch]
	      = calcKernelOutputAtEdge(srcChannels[ch],
				       kernel, x, y,
				       imageWidth, imageHeight,
				       margineWidth, margineHeight);
	  }else{
	    dst.at<Vec3b>(y, x).val[ch]
	      = calcKernelOutput(srcChannels[ch],
				 kernel, x, y,
				 margineWidth, margineHeight,				 
				 kernelElemCount);
	  }
	}
      }
    }
  }
}
