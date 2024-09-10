#pragma once
#include "includes.hpp"

class MatrixManager
{
private:
	Matrix m_matrix_1;
	Matrix m_matrix_2;
	
	Matrix m_intersection_matrix; //матрица, в которой выводятся перечечения числовых матриц( * - отсутствие пересечения)

	enum Menu
	{
		CREATE_MATRIX = 1,
		INTERSECTION,
		EXIT
	};

public:
	MatrixManager();
	~MatrixManager();

	int get_random_int(int min, int max);
	void set_matrixes_size(int length, int width);
	void set_matrixes_numbers(int min, int max);

	void print_matrixes();

	bool is_created();

	friend Matrix operator&(const Matrix& matrix_1, const Matrix& matrix_2); //не является методом класса
	void find_intersections();
	int count_intersections();
	void print_intersections();

	void loop(); //основная диалоговая петля

	void run(); //точка входа
	
};