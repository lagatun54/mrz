// �������� ������� ������ 921701 ���������� ��������� ���������
#pragma once
#include "CImg/CImg.h"
#include "matrix.h"
#include <iostream>
#include <random>



class ImageCompressor
{

private:

	cimg_library::CImg<double> image;
	cimg_library::CImg<double> resultImage;

	Matrix firstWeights;
	Matrix secondWeights;

	std::vector<Matrix> blocks;
	std::vector<Matrix> result;

	int n;
	int m;
	int p;

	int Cmax = 255;
	
	int W;
	int H;
	int N;
	int L;
	
	long double maxError;
	double adaptiveLearningStep;
	long double error;

	long double calculateCi(long  double);
	double CalculateUk(double);
	
	void normalizeWeights(Matrix&);

public:

	ImageCompressor(cimg_library::CImg<double>);

	void showImage();
	void setNetworkConfiguration();
	void imageToMatrix();
	
	void initializeWeights();
	void study();
	void matrixToImage();
	
	void putInResultCompressedImageMatrix();
	void showCompressedImage();
	void printCompressionRatio();
};

