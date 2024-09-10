#include "Matrix.hpp"
MatrixManager::MatrixManager()
{
	set_matrixes_size(1, 1); //считаю матрицы размером 1х1 не созданными
}

MatrixManager::~MatrixManager()
{

}

int MatrixManager::get_random_int(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void MatrixManager::set_matrixes_size(int length, int width)
{
	m_matrix_1.resize(width);
	m_matrix_2.resize(width);
	m_intersection_matrix.resize(width);

	for (size_t i = 0; i < m_matrix_1.size(); i++)
	{
		m_matrix_1.at(i).resize(length);
		m_matrix_2.at(i).resize(length);
		m_intersection_matrix.at(i).resize(length);
	}
}

bool MatrixManager::is_created()
{
	if (m_matrix_1.size() > 1 and m_matrix_1.at(0).size() > 1)
		return true;
	else return false;
}

void MatrixManager::set_matrixes_numbers(int min, int max)
{
	for (size_t i = 0; i < m_matrix_1.size(); i++) //не имеет значения, ширину какой матрицы брать, тк они равны
	{
		for (size_t j = 0; j < m_matrix_1.at(0).size(); j++) //тоже самое
		{
			m_matrix_1.at(i).at(j) = get_random_int(min, max); //лень писать функционал по выбору диапозона чисел матрицы
			m_matrix_2.at(i).at(j) = get_random_int(min, max);
		}
	}
}

void MatrixManager::print_matrixes()
{
	if (is_created())
	{
		std::cout << std::string(m_matrix_1.at(0).size() * 8, '-')  << std::endl;

		for (size_t i = 0; i < m_matrix_1.size(); i++)
		{
			for (size_t j = 0; j < m_matrix_1.at(0).size(); j++)
			{
				if (m_matrix_1.at(i).at(j) >= 0)					//тк интервал чисел (-10, 10), эта проверка дает нам 
					std::cout << " ";								//количество символов числа для нормального отображения
				std::cout << m_matrix_1.at(i).at(j) << " ";			//матриц
			}

			std::cout << "\t\t";

			for (size_t j = 0; j < m_matrix_2.at(0).size(); j++)
			{
				if (m_matrix_2.at(i).at(j) >= 0)
					std::cout << " ";
				std::cout << m_matrix_2.at(i).at(j) << " ";
			}

			std::cout << std::endl;

		}
		std::cout << std::string(m_matrix_1.at(0).size() * 8, '-') << std::endl;
	}
	else
		std::cout << std::string(30, '-') << std::endl << "\n   Матрицы не созданы!!!\n\n" << std::string(30, '-') << std::endl;
}

Matrix operator&(const Matrix& matrix_1, const Matrix& matrix_2) //лень писать проверки на совпадение размеров матриц
{
	Matrix temp_intersection_matrix;
	temp_intersection_matrix.resize(matrix_1.size());
	for (size_t i = 0; i < temp_intersection_matrix.size(); i++)
		temp_intersection_matrix.at(i).resize(matrix_1.at(0).size());

	for (size_t i = 0; i < matrix_1.size(); i++)
	{
		for (size_t j = 0; j < matrix_1.at(0).size(); j++)
		{
			if (matrix_1.at(i).at(j) == matrix_2.at(i).at(j))
			{
				//std::string temp = std::to_string(matrix_1.at(i).at(j)); //этот приём взял на stackoverflow (по непонятным причинам выводит '-' вместо чисел)
				//char const* temp_char = temp.c_str();
				//temp_intersection_matrix.at(i).at(j) = *temp_char;

				temp_intersection_matrix.at(i).at(j) = matrix_1.at(i).at(j);

			}
			else temp_intersection_matrix.at(i).at(j) = -10; //интервал чисел в матрице [-9; 9], так что -10 - отсутствие пересечения
		}
	}
	return temp_intersection_matrix;
}

void MatrixManager::find_intersections()
{
	m_intersection_matrix = m_matrix_1 & m_matrix_2;
}

int MatrixManager::count_intersections()
{
	int counter = 0;

	for (size_t i = 0; i < m_intersection_matrix.size(); i++)
	{
		for (size_t j = 0; j < m_intersection_matrix.at(0).size(); j++)
		{
			if (m_intersection_matrix.at(i).at(j) != -10)
				counter++;
		}
	}
	return counter;
}

void MatrixManager::print_intersections()
{
	for (size_t i = 0; i < m_intersection_matrix.size(); i++)
	{
		std::cout << "\t\t\t";

		for (size_t j = 0; j < m_intersection_matrix.at(0).size(); j++)
		{
			if (m_intersection_matrix.at(i).at(j) == -10)
				std::cout << " * ";
			else
			{
				if (m_intersection_matrix.at(i).at(j) >= 0)
					std::cout << " ";
				std::cout << m_intersection_matrix.at(i).at(j) << " ";
			}
		}
		std::cout << std::endl;
	}
}

void MatrixManager::loop()
{
	int answer{};
	do
	{
		print_matrixes();
		std::cout
			<< "1) Я хочу создать матрицы!\n"
			<< "2) Я хочу найти пересечения матриц!\n"
			<< "3) Я хочу выйти!\n\n"
			<< "Выбор: ";
		std::cin >> answer;

		switch (answer)
		{
		case(CREATE_MATRIX):
			system("cls");

			int length, width;
			std::cout << "Введи количество столбиков и строк матриц через пробел: ";
			std::cin >> length >> width;

			set_matrixes_size(length, width);
			set_matrixes_numbers(-9, 9);		//лень прописывать функционал по выбору интервала чисел

			std::cout << "Были созданы матрицы " << length << 'x' << width << ", заполненные\n случайными числами!\n\n";
			system("pause");
			system("cls");
			break;

		case(INTERSECTION):
			system("cls");
			if (is_created())
			{
				find_intersections();
				print_matrixes();


				if (count_intersections())
					print_intersections();
				else
					std::cout << "Пересечения не найдены!\n";

				system("pause");
				system("cls");
			}

			else
			{
				std::cout << "Матрицы не созданы!\n\n";
				system("pause");
				system("cls");
			}
			break;

		case(EXIT):
			break;

		default:
			system("cls");
			std::cout << "Неверный номер!\n";
			system("pause");
			system("cls");
			break;
		}
	} while (answer != EXIT);
}

void MatrixManager::run()
{
	setlocale(0, "");
	srand(time(0));

	loop();
}