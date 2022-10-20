#include <iostream>
#include <random>

#include "matrix.h"


Matrix::Matrix() : width(0), height(0) {

}

Matrix::Matrix(const Matrix &in) : data(in.data), width(in.width), height(in.height) {

}

Matrix::Matrix(std::vector<std::vector<double>> input) : data(input), height(input.size()), width(input[0].size()) {

}

void Matrix::setWidth(int Width) {
	width = Width;
}

void Matrix::setHeight(int Height) {
	height = Height;
}

int Matrix::getWidth() {
	return width;
}

int Matrix::getHeight() {
	return height;
}

void Matrix::setData(std::vector<std::vector<double>> Data) {
	data = Data;
	height = data.size();
	width = data[0].size();
}

std::vector<std::vector<double>> Matrix::getData() {
	return data;
}

Matrix Matrix::Transposition() {
	std::vector<std::vector<double>> out;
	out.resize(data[0].size());
	for (register int i = 0; i < data[0].size(); i++) {
		out[i].resize(data.size());
		for (register int j = 0; j < data.size(); j++) {
			out[i][j] = data[j][i];
		}
	}
	Matrix rez(out);
	return rez;
}

Matrix& Matrix::operator=(const Matrix& sec) {
	width = sec.width;
	height = sec.height;
	data = sec.data;
	return *this;
}

Matrix Matrix::operator+(const Matrix& sec) {
	Matrix Rez = *this;
	std::vector<std::vector<double>> rez;
	if (height == sec.height) {
		rez.resize(data.size());
		for (register auto i = 0; i < height; i++) {
			rez[i].resize(data[i].size());
			for (register auto j = 0; j < width; j++) {
				rez[i][j] = data[i][j] + sec.data[i][j];
			}
		}
	}
	else {
		std::cout << "Matrixs sizes are not equal" << std::endl;
		return *this;
	}
	Rez.data = rez;
	return Rez;
}

Matrix Matrix::operator+(const int& sec) {
	Matrix Rez = *this;
	std::vector<std::vector<double>> rez;
	rez.resize(data.size());
	for (auto i = 0; i < height; i++) {
		rez[i].resize(data[i].size());
		for (auto j = 0; j < width; j++) {
			rez[i][j] = data[i][j] + sec;
		}
	}
	Rez.data = rez;
	return Rez;
}

Matrix& Matrix::operator+=(const Matrix& sec) {
	if (height == sec.height) {
		for (auto i = 0; i < height; i++) {
			for (auto j = 0; j < width; j++) {
				data[i][j] += sec.data[i][j];
			}
		}
	}
	else {
		std::cout << "Matrixs sizes are not equal" << std::endl;
		return *this;
	}
	return *this;
}

Matrix& Matrix::operator+=(const int& sec) {
	for (auto i = 0; i < height; i++) {
		for (auto j = 0; j < width; j++) {
			data[i][j] += sec;
		}
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix& sec) {
	Matrix Rez = *this;
	std::vector<std::vector<double>> rez;
	if (height == sec.height) {
		rez.resize(data.size());
		for (register auto i = 0; i < height; i++) {
			rez[i].resize(data[i].size());
			for (register auto j = 0; j < width; j++) {
				rez[i][j] = data[i][j] - sec.data[i][j];
			}
		}
	}
	else {
		std::cout << "Matrixs sizes are not equal" << std::endl;
		return *this;
	}
	Rez.data = rez;
	return Rez;
}

Matrix Matrix::operator-(const int& sec) {
	Matrix Rez = *this;
	std::vector<std::vector<double>> rez;
	rez.resize(data.size());
	for (auto i = 0; i < height; i++) {
		rez[i].resize(data[i].size());
		for (auto j = 0; j < width; j++) {
			rez[i][j] = data[i][j] - sec;
		}
	}
	Rez.data = rez;
	return Rez;
}

Matrix& Matrix::operator-=(const Matrix& sec) {
	if (height == sec.height) {
		for (auto i = 0; i < height; i++) {
			for (auto j = 0; j < width; j++) {
				data[i][j] -= sec.data[i][j];
			}
		}
	}
	else {
		std::cout << "Matrixs sizes are not equal" << std::endl;
		return *this;
	}
	return *this;
}

Matrix& Matrix::operator-=(const int& sec) {
	for (auto i = 0; i < height; i++) {
		for (auto j = 0; j < width; j++) {
			data[i][j] -= sec;
		}
	}
	return *this;
}

bool Matrix::operator==(const Matrix& sec) {
	if (width == sec.width && height == sec.height) {
		for (auto i = 0; i < height; i++) {
			for (auto j = 0; j < width; j++) {
				if (data[i][j] != sec.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}

Matrix Matrix::operator*(const Matrix& sec) {
	std::vector<std::vector<double>> rez;
	if (width == sec.height) {
		rez.resize(height);
		for (register int i = 0; i < height; i++) {
			rez[i].resize(sec.width);
			for (register int j = 0; j < sec.width; j++) {
				rez[i][j] = 0;
				for (register int k = 0; k < width; k++) {
					rez[i][j] += data[i][k] * sec.data[k][j];
				}
			}
		}
		
	}
	else
		std::cout << "NULL" << std::endl;
	Matrix Rez(rez);
	return Rez;
}

void Matrix::toInput() {
	std::vector<std::vector<double>> temp;
	temp.resize(1);
	for (register auto i = data.begin(); i != data.end(); i++) {
		for (register auto j = i->begin(); j != i->end(); j++) {
			temp[0].emplace_back(*j);
		}
	}
	data = temp;
	width = data[0].size();
	height = 1;
}

Matrix Matrix::operator*(const double& k) {
	for (register auto i = data.begin(); i != data.end(); i++) {
		for (register auto j = i->begin(); j != i->end(); j++) {
			*j *= k;
		}
	}
	Matrix rez(data);
	return rez;
}

double Matrix::square() {
	double rez = 0;
	for (auto i : data) {
		for (auto j : i) {
			rez += pow(j, 2);
		}
	}
	return 0.5 * rez;
}

void Matrix::print() {
	for (int i = 0; i < data.size(); i++) {
		
		for (int j = 0; j < data[i].size(); j++) {
			std::cout << data[i][j] << std::endl;
		}
		std::cout << std::endl;
	}
}

double Matrix::calculateMultiplicationWithTransposed() {
	double result = 0;
	size_t size = std::max(width, height);


	for (size_t e = 0; e < size; ++e) {
		double element = 0;
		if (height == 1) {

			element = data[0][e];
		}
		else
			element = data[e][0];

		result += element * element;
	
	}

	return result;
}

