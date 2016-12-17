#include <TextDetector.hpp>

using namespace std;
using namespace cv;

Mat TextDetector::detectText(const Mat &image){
  // calc image channels
  {
    // RGB

    // HSI

    // Delta
  }

  // extract ERs

  // calc connected component

  // labeling

  // vectorlization

  return Mat();
}

Mat TextDetector::mser(const Mat &image){
  RNG rng(12345);

  Mat grayImage;
  cvtColor(image, grayImage, CV_BGR2GRAY);

  resize(grayImage, grayImage, Size(), 2.0, 2.0, INTER_CUBIC);

  vector<vector<cv::Point> > contours = calcContours(grayImage);

  sort(contours.begin(),
       contours.end(),
       [](const vector<Point>& a, const vector<Point>& b){return contourArea(a) < contourArea(b);}
       );

  // remove tiny contour
  auto it = remove_if(contours.begin(),
  		      contours.end(),
  		      [](const vector<Point>& a) -> bool{
  			return contourArea(a) <= 1;});
  contours.erase(it, contours.end());
  std::cout << contours.size() << std::endl;

  // remove huge contour

  std::vector<std::vector<std::vector<cv::Point> > > nearContours(0);
  std::vector<bool> scanFlag(contours.size(), false);
      
  for( int i = 0; i < contours.size(); i++)
    {
      if (std::count(scanFlag.begin(), scanFlag.end(), false) == 0)
	break;

      if(scanFlag[i])
	continue;

      scanFlag[i] = true;

      std::vector<std::vector<cv::Point> > nearContour(0);
      
      vector<Point> cont = contours[i];

      Point2f mc = calcCenterPoint(cont);

      // for debug
      {
	std::cout << i << std::endl;
	std::cout << contourArea(cont) << std::endl;
	std::cout << mc << std::endl;
      }

      nearContour.push_back(cont);

      Mat drawing = Mat::zeros(grayImage.size(), CV_8UC3);
      image.copyTo(drawing);

      resize(drawing, drawing, Size(), 2.0, 2.0, INTER_CUBIC);

      // collect near contours
      for (int j = 0; j < contours.size(); j++){
	if (scanFlag[j])
	  continue;
	
	std::vector<cv::Point> contObj = contours[j];
	Point2f centerObj = calcCenterPoint(contObj);

	Point2f diff = mc - centerObj;

	double res = cv::norm(diff);

	if (res < 10){
	  nearContour.push_back(contObj);
	  scanFlag[j] = true;
	  
	  // for debug
	  {	
	    Scalar color = Scalar(rng.uniform(0, 255),
				  rng.uniform(0,255),
				  rng.uniform(0,255));
	    Scalar pointcolor = Scalar(0, 255, 0);
	    drawContours(drawing, contours, j, color, 2, 8);
	    circle(drawing, mc, 5, pointcolor, 3);
	  }
	}
      }

      if (nearContour.size() < 5)
	continue;

      nearContours.push_back(nearContour);
      std::cout << nearContour.size() << std::endl;

      vector<Rect> boundRect( nearContour.size() );
      vector<vector<Point> > contours_poly(contours.size());
      vector<Point2f>center( contours.size() );
      vector<float>radius( contours.size() );

      
      for( int i = 0; i < nearContour.size(); i++ ){
	approxPolyDP( Mat(nearContour[i]), contours_poly[i], 3, true );
	boundRect[i] = boundingRect( Mat(contours_poly[i]) );
	minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );

	Scalar color = Scalar(rng.uniform(0, 255),
			      rng.uniform(0,255),
			      rng.uniform(0,255));
	Scalar pointcolor = Scalar(0, 255, 0);
	
	rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );

	Mat roi = 
      }

      imshow("grey image", drawing);
      waitKey(1);
    }

  std::cout << nearContours.size() << std::endl;  
  imshow("image", grayImage);
  waitKey(0);

  return Mat();
}

vector<vector<cv::Point> > TextDetector::calcContours(const cv::Mat &grayImage){
  vector<vector<cv::Point> > contours;  
  Mat canny_output;

  vector<Vec4i> hierarchy;
  vector<vector<Point> > contour;

  RNG rng(12345);  

  if(grayImage.channels() != 1){
    cout << "grayImage chennel count must be 1" << endl;
    exit(-1);
  }

  for(int i = 0; i < 256; i += 5){
    std::cout << i << std::endl;
    Mat dst;
    Mat dstInv;

    threshold(grayImage,
	      dst, i,
	      max_BINARY_value, 1);

    //    imshow("dst", dst);
    
    threshold(grayImage,
	      dstInv, i,
	      max_BINARY_value, 0);

    // imshow("dst inv", dstInv);
    // waitKey(0);

    if(cv::countNonZero(dst) == 0)
      continue;
    if(cv::countNonZero(dstInv) == 0)
      continue;
    
    std::vector<std::vector<Point> > contour;

    Canny(dst, canny_output, thresh, thresh * 2, 3);

    // imshow("canny", canny_output);
    // waitKey(0);
    
    findContours(canny_output, contour, hierarchy,
		 CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    contours.insert(contours.end(), contour.begin(), contour.end());

    Canny(dstInv, canny_output, thresh, thresh * 2, 3);
    findContours(canny_output, contour, hierarchy,
		 CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    contours.insert(contours.end(), contour.begin(), contour.end());
  }

  for (int i = 0; i < contours.size(); i++){
    // // for debug
    // {
    //   Mat drawing;
    //   Scalar color = Scalar(rng.uniform(0, 255),
    // 			    rng.uniform(0,255),
    // 			    rng.uniform(0,255));
    //   drawContours(drawing, contours, i, color, 2, 8);
    //   imshow("grey image", drawing);
    //   waitKey(0);
    // }
  }

  return contours;
}

Point2f TextDetector::calcCenterPoint(vector<Point> cont){
  Moments mu = moments(cont);
  Point2f mc = Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

  return mc;
}
