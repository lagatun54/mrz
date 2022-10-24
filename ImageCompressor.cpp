#include "ImageCompressor.h"
#include <fstream>


ImageCompressor::ImageCompressor(cimg_library::CImg<double> image) {
	this->image = image;
	W = image.width();
	H = image.height();

	n = 8;
	m = 8;
	p = 48;

	adaptiveLearningStep = 0.00001;
	maxError = 1000;
	error = 0;
}

void ImageCompressor::showImage() {
	image.display("Image");
}


void ImageCompressor::setNetworkConfiguration() {
	
	std::cout << "m: ";
	std::cin >> m;

	std::cout << "n: ";
	std::cin >> n;

	std::cout << "p: ";
	std::cin >> p;

	std::cout << "Max error: ";
	std::cin >> maxError;

	std::cout << std::endl;

	L = H / n * W / m;
	N = n * m * 3;
}

void ImageCompressor::imageToMatrix() {
    std::string resulting = "resultDeltaY.txt";
    std::cout << result.size();
    std::fstream fout;
    fout.open(resulting,std::ios::in | std::ios::out);

	for (int i = 0; i < W; i += m) {

		for (int j = 0; j < H; j += n) {

			std::vector<std::vector<double>> block;

			for (auto i_pixel = j; i_pixel < j + n; i_pixel++) {

				for (auto j_pixel = i; j_pixel < i + m; j_pixel++) {

					std::vector<double> pixel;
					for (auto t = 0; t < 3; t++) {

						pixel.emplace_back(calculateCi(image(j_pixel, i_pixel, 0, t)));
                        fout << double (image(j_pixel, i_pixel, 0, t)) << ' ';
					}
					block.emplace_back(pixel);
				}
			}
			blocks.emplace_back(Matrix(block));
		}
	}

	this->L = blocks.size();
}

long double ImageCompressor::calculateCi(long double Cijk) {
	return (2 * Cijk) / Cmax - 1;
}


void ImageCompressor::initializeWeights() {

	std::random_device randomDevice;
	std::mt19937 engine(randomDevice());
	std::uniform_real_distribution<> distribution(0,1);

	std::vector<std::vector<double>> data;
	for (auto j = 0; j < N; j++) {
		std::vector<double> weights;
		for (auto i = 0; i < p; i++) {

			double w = distribution(engine);

			weights.emplace_back(w);
	
		}
		data.emplace_back(weights);
	}
	firstWeights.setData(data);

	secondWeights = firstWeights.Transposition();

}

void ImageCompressor::study() {
	
	Matrix deltaX;
    int iterationNumber = 0;


    do {

		for (auto block : blocks) {

			block.toInput();
			int blockSize = n * m;


			Matrix y, xp;
			y = block * firstWeights;
			xp = y * secondWeights;

			deltaX = xp - block;

			adaptiveLearningStep = 1.0 / double(blockSize * blockSize + y.calculateMultiplicationWithTransposed());

			Matrix ytmdx = y.Transposition() * deltaX;


            ytmdx = ytmdx * adaptiveLearningStep;
			secondWeights -= ytmdx;

			adaptiveLearningStep = 1.0 / double(blockSize * blockSize + block.calculateMultiplicationWithTransposed());

			Matrix xtmdxmswt = block.Transposition() * (deltaX * secondWeights.Transposition());
			xtmdxmswt = xtmdxmswt * adaptiveLearningStep;
			firstWeights -= xtmdxmswt;
		}
		

		error = 0;
		for (auto block : blocks) {
			
			block.toInput();
			double blockError = 0;
			
			for (size_t e = 0; e < block.getWidth(); ++e) {
				std::vector<std::vector<double>> data = deltaX.getData();
				blockError += data[0][e] * data[0][e];
			}
			
			error += blockError;
		}

		normalizeWeights(firstWeights);
		normalizeWeights(secondWeights);

		iterationNumber++;

		std::cout << "Iteration: " << iterationNumber << std::endl;
		std::cout << "Error: " << error << std::endl << std::endl;

	} while (error > maxError);
}

void ImageCompressor::matrixToImage() {

	cimg_library::CImg<double> image(W, H, 1, 3);
    std::string resulting = "result.txt";
	std::cout << result.size();
    std::fstream fout;
    fout.open(resulting,std::ios::in | std::ios::out);

	for (int i = 0, q = 0; i < W; i += m) {
		for (int j = 0; j < H; j += n, q++) {
			std::vector<std::vector<double>> res;
			res = result[q].getData();
			for (auto k = j, w = 0; k < j + n; k++) {
 				for (auto o = i; o < i + m; o++) {
					for (auto t = 0; t < 3; t++, w++) {
                        fout << CalculateUk(res[0][w]) << ' ';
						image(o, k, 0, t) = CalculateUk(res[0][w]);
					}
				}
			}
		}
	}

	resultImage = image;
	resultImage.save("result.bmp");
}

double ImageCompressor::CalculateUk(double Xi) {
	double result = Cmax * (Xi + 1) / 2;
	if (result < 0) {
		result = 0;
	}
	else if (result > 255) {
		result = 255;
	}

	return result;
}

void ImageCompressor::putInResultCompressedImageMatrix() {

	for (auto block : blocks) {
		Matrix y, z;
		block.toInput();
		y = block * firstWeights;
		z = y * secondWeights;
		result.emplace_back(z);
	}

}

void ImageCompressor::showCompressedImage() {
}

void ImageCompressor::printCompressionRatio() {
	double Z = double(N * L) / double((N + L) * p + 2);
	std::cout << "Compression ratio (Z): " << Z << std::endl;
}

void ImageCompressor::normalizeWeights(Matrix& weights) {

	std::vector<std::vector<double>> W = weights.getData();

	for (int i = 0; i < W.size(); i++) {
		
		double value = 0;
		for (int j = 0; j < W[0].size(); j++) {
			value += W[i][j] * W[i][j];
		}
		
		value = sqrt(value);
		for (int j = 0; j < W[0].size(); j++) {
			W[i][j] /= value;
		}
	}

	weights.setData(W);
}