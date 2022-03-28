#include <iostream>
#include <random>
#include <omp.h>
#include <vector>
#include <chrono>
void initMatrix(std::vector<std::vector<double>>& matrix)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> rg(1, 100);

	for (size_t i = 0; i < matrix.size(); ++i)
		for (size_t j = 0; j < matrix[i].size(); ++j)
			matrix[i][j] = rg(gen);
}
void printMatrix(const std::vector<std::vector<double>>& vector)
{
	for (size_t i = 0; i < vector.size(); ++i) {
		for (size_t j = 0; j < vector[i].size(); ++j)
			std::cout << vector[i][j] << " " << std::flush;

		std::cout << std::endl;
	}

	std::cout << std::endl;
}
std::vector<std::vector<double>> mulMatrix(const std::vector<std::vector<double>>& firstVector,
	const std::vector<std::vector<double>>& secondVector)
{
	const size_t n = secondVector.size();
	const size_t row = firstVector.size();
	const size_t column = secondVector.at(0).size();

	std::vector<std::vector<double>> result(row, std::vector<double>(column));

	#pragma omp parallel for num_threads(1)
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < column; ++j)
				for (int k = 0; k < n; ++k)
					result[i][j] += firstVector[i][k] * secondVector[k][j];

	return result;
}
int main()
{
	
	size_t row1;
	size_t  column1;
	std::cout << "Enter size of 1st matrix:\n";
	std::cin >> row1 >> column1;
	size_t  column2;
	std::cout << "Enter size of 2nd matrix:\n";
	std::cin >>  column2;
	std::vector<std::vector<double>> matrix1(row1, std::vector<double>(column1));
	std::vector<std::vector<double>> matrix2(column1, std::vector<double>(column2));
	initMatrix(matrix1);
	initMatrix(matrix2);
	//printMatrix(matrix1);
	//printMatrix(matrix2);
	auto begin = std::chrono::steady_clock::now();;
	auto buf = mulMatrix(matrix1, matrix2);
	auto end = std::chrono::steady_clock::now();;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout <<"Time:" << elapsed_ms.count()<<"milliseconds";
	std::cout << "\nPrint matrix?";
	bool flag=false;
	std::cin >> flag;
	if(flag)
	printMatrix(buf);
}

