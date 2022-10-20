//  �������� ������� ������ 921701 ���������� ��������� ���������
#include <vector>

class Matrix
{
private:
	
	int width;
	int height;
	std::vector<std::vector<double>> data;

public:

	Matrix();
	Matrix(const Matrix&);
	Matrix(std::vector<std::vector<double>>);

	void setWidth(int);
	void setHeight(int);

	int getWidth();
	int getHeight();

	void setData(std::vector<std::vector<double>>);

	std::vector<std::vector<double>> getData();
	
	Matrix Transposition();

	void toInput();
	double square();

	Matrix operator+(const Matrix& sec);
	Matrix operator+(const int& sec);
	Matrix& operator+=(const Matrix& sec);
	Matrix& operator+=(const int& sec);

	Matrix operator-(const Matrix& sec);
	Matrix operator-(const int& sec);
	Matrix& operator-=(const Matrix& sec);
	Matrix& operator-=(const int& sec);

	Matrix& operator=(const Matrix& sec);

	bool operator==(const Matrix& sec);

	Matrix operator*(const Matrix& sec);
	Matrix operator*(const double&);

	void print();

	double calculateMultiplicationWithTransposed();
};

