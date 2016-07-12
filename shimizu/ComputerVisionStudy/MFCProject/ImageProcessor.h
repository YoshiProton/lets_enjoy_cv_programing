#pragma once

#include <string> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


enum ProcessMethod { None, FullOpenCV, HalfOpenCV, FullScratch };

class CImageProcessor
{
protected:
	ProcessMethod processMethod;
	std::string filePath;

public:
	CImageProcessor();
	~CImageProcessor();

	void SetProcessMethod(ProcessMethod);
	virtual void Execute(std::string) = 0;
};

