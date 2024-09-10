#include "Matrix.hpp"
MatrixManager::MatrixManager()
{
	set_matrixes_size(1, 1); //������ ������� �������� 1�1 �� ����������
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
	for (size_t i = 0; i < m_matrix_1.size(); i++) //�� ����� ��������, ������ ����� ������� �����, �� ��� �����
	{
		for (size_t j = 0; j < m_matrix_1.at(0).size(); j++) //���� �����
		{
			m_matrix_1.at(i).at(j) = get_random_int(min, max); //���� ������ ���������� �� ������ ��������� ����� �������
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
				if (m_matrix_1.at(i).at(j) >= 0)					//�� �������� ����� (-10, 10), ��� �������� ���� ��� 
					std::cout << " ";								//���������� �������� ����� ��� ����������� �����������
				std::cout << m_matrix_1.at(i).at(j) << " ";			//������
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
		std::cout << std::string(30, '-') << std::endl << "\n   ������� �� �������!!!\n\n" << std::string(30, '-') << std::endl;
}

Matrix operator&(const Matrix& matrix_1, const Matrix& matrix_2) //���� ������ �������� �� ���������� �������� ������
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
				//std::string temp = std::to_string(matrix_1.at(i).at(j)); //���� ���� ���� �� stackoverflow (�� ���������� �������� ������� '-' ������ �����)
				//char const* temp_char = temp.c_str();
				//temp_intersection_matrix.at(i).at(j) = *temp_char;

				temp_intersection_matrix.at(i).at(j) = matrix_1.at(i).at(j);

			}
			else temp_intersection_matrix.at(i).at(j) = -10; //�������� ����� � ������� [-9; 9], ��� ��� -10 - ���������� �����������
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
			<< "1) � ���� ������� �������!\n"
			<< "2) � ���� ����� ����������� ������!\n"
			<< "3) � ���� �����!\n\n"
			<< "�����: ";
		std::cin >> answer;

		switch (answer)
		{
		case(CREATE_MATRIX):
			system("cls");

			int length, width;
			std::cout << "����� ���������� ��������� � ����� ������ ����� ������: ";
			std::cin >> length >> width;

			set_matrixes_size(length, width);
			set_matrixes_numbers(-9, 9);		//���� ����������� ���������� �� ������ ��������� �����

			std::cout << "���� ������� ������� " << length << 'x' << width << ", �����������\n ���������� �������!\n\n";
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
					std::cout << "����������� �� �������!\n";

				system("pause");
				system("cls");
			}

			else
			{
				std::cout << "������� �� �������!\n\n";
				system("pause");
				system("cls");
			}
			break;

		case(EXIT):
			break;

		default:
			system("cls");
			std::cout << "�������� �����!\n";
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