#include "GMatrix.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

GMatrix::GMatrix(std::vector<std::vector<double>> elements, int row_Size, int column_Size)
{
	if (row_Size != FROM_VECTOR)
	{
		Row_Size_ = row_Size;
	}else
	{
		Row_Size_ = elements[0].size();
	}

	if (column_Size != FROM_VECTOR)
	{
		Column_Size_ = column_Size;
	}else
	{
		Column_Size_ = elements.size();
	}

	Elements_.resize(elements.size());

	for (int i = 0; i < elements.size(); i++)
	{
		Elements_[i] = elements[i];

		// Resize child vectors because we want their size to equal Row_Size_.
		Elements_[i].resize(Row_Size_, 0.0);
	}

	// Resize parent vector because we want Elements_.size() to be the same as column_Size.
	Elements_.resize(Column_Size_);

	// If elements.size() is smaller than Row_Size_ then some of Elements_ rows will be empty --
	// and their size will not equal row_Col_Size, so resize the rows.
	for (int i = 0; i < Elements_.size(); i++)
	{
		if (Elements_[i].size() == 0)
		{
			Elements_[i].resize(Row_Size_, 0.0);
		}
	}
}

// Elements_ will produce an error if it gets accessed and it is empty, so increase its size and fill it with zeroes.
GMatrix::GMatrix()
{
	Row_Size_ = 2;
	Column_Size_ = 2;
	Elements_.emplace_back();
	Elements_.emplace_back();
	Elements_[0].resize(2);
	Elements_[1].resize(2);
	std::fill(Elements_[0].begin(), Elements_[0].end(), 0);
	std::fill(Elements_[1].begin(), Elements_[1].end(), 0);
}

GMatrix::~GMatrix()
{
}

std::vector<std::vector<double>> GMatrix::Random(int row_Size, int column_Size, double min, double max, bool use_Integers)
{
	// Create a random number generator.
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_real_distribution<double> dist(min, max); // distribution in range [min, max].
	
	// This lambda is needed because without it all columns in the random matrix would be the same.
	auto gen = [&dist, &rng, &use_Integers]() -> double {
		if (use_Integers == true)
		{
			return (int)dist(rng);
		}else
		{
			return dist(rng);
		}
	};

	std::vector<std::vector<double>> matrix;

	for (int i = 0; i < column_Size; i++)
	{
		matrix.emplace_back();
		matrix[i].resize(row_Size);

		std::generate(std::begin(matrix[i]), std::end(matrix[i]), gen);

		//std::fill();
	}

	return matrix;
}

 std::vector<std::vector<double>> GMatrix::Fill(int row_Size, int column_Size, double number)
 {
	 std::vector<std::vector<double>> matrix;

	 for (int i = 0; i < column_Size; i++)
	 {
		 matrix.emplace_back();
		 matrix[i].resize(row_Size);

		 std::fill(matrix[i].begin(), matrix[i].end(), number);
	 }

	 return matrix;
 }

 GMatrix GMatrix::Transpose()
{
	 GMatrix new_Matrix(GMatrix::Fill(Column_Size_, Row_Size_, 0));

	 for (int i = 0; i < Column_Size_; i++)
	 {
		 for (int j = 0; j < Row_Size_; j++)
		 {
			 new_Matrix.Elements_[j][i] = Elements_[i][j];
		 }
		 
	 }

	return new_Matrix;
}

bool GMatrix::Print(unsigned int precision)
{
	if (Elements_.size() == 0)
	{
		return true;
	}

	// Loop through the parent vector and its child vectors and print their contents.
	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			if (precision > 1)
			{
				std::cout << std::setprecision(precision);
				std::cout << Elements_[i][j] << "  ";
			}else
			{
				std::cout << std::round(Elements_[i][j]) << "  ";
			}
		}
		std::cout << "\n";
	}

	return false;
}

const GMatrix::Set_Size_Result& GMatrix::Set_Row_Column_Size(int row_Size, int column_Size, double value)
{
	int size_Before_resize = Elements_.size();
	Elements_.resize(column_Size);

	if (Row_Size_ != row_Size)
	{
		for (int i = 0; i < Elements_.size(); i++)
		{
			Elements_[i].resize(row_Size, value);
		}
	}

	// Tracks if any elements were deleted
	Set_Size_Result elements_Deleted;

	if (Column_Size_ > column_Size)
	{
		elements_Deleted.Columns_Deleted = true;
	}

	if (Row_Size_ > row_Size)
	{
		elements_Deleted.Rows_Deleted = true;
	}

	return elements_Deleted;
}

const std::pair<int, int>& GMatrix::Dimensions()
{
	std::pair<int, int> dimensions;
	dimensions.first = Row_Size_;
	dimensions.second = Column_Size_;
	return dimensions;
}

std::vector<std::vector<double>> GMatrix::Get()
{
	return Elements_;
}

GMatrix GMatrix::Get_Row(int row)
{
	if (row > Row_Size_)
	{
		row = Row_Size_;
	}

	std::vector<std::vector<double>> vector;

	vector.push_back(Elements_[row]);
	GMatrix new_Matrix(vector);

	new_Matrix.Row_Size_ = Row_Size_;
	new_Matrix.Column_Size_ = 1;
	return new_Matrix;
}

GMatrix GMatrix::Get_Column(int column)
{
	if (column > Row_Size_)
	{
		column = Row_Size_;
	}

	GMatrix new_Matrix(GMatrix::Fill(1, Column_Size_, 0), 1, Column_Size_);
	for (int i = 0; i < Column_Size_; i++)
	{
		new_Matrix.Elements_[i][0] = Elements_[i][column];
	}

	new_Matrix.Row_Size_ = 1;
	new_Matrix.Column_Size_ = Column_Size_;
	return new_Matrix;
}

double GMatrix::Dot_Product(GMatrix& other_Matrix, int self_Index, int other_Index, bool self_Row, bool other_Row)
{
	GMatrix self_Size_Checker = self_Row ? Get_Row(0) : Get_Column(0);
	GMatrix other_Size_Checker = other_Row ? other_Matrix.Get_Row(0) : other_Matrix.Get_Column(0);

	int self_Size = self_Row ? self_Size_Checker.Row_Size_ : self_Size_Checker.Column_Size_;
	int other_Size = other_Row ? other_Size_Checker.Row_Size_ : other_Size_Checker.Column_Size_;

	if (self_Size == other_Size)
	{
		double prev_Product = 0.0;
		double self_Factor = 0.0;
		double other_Factor = 0.0;


		for (int i = 0; i < self_Size; i++)
		{
			if (self_Row == true)
			{
				self_Factor = Get_Row(self_Index).Elements_[0][i];
			}else
			{
				self_Factor = Get_Column(self_Index).Elements_[i][0];
			}

			if (other_Row == true)
			{
				other_Factor = other_Matrix.Get_Row(other_Index).Elements_[0][i];
			}else
			{
				other_Factor = other_Matrix.Get_Column(other_Index).Elements_[i][0];
			}

			prev_Product = (self_Factor * other_Factor) + prev_Product;
		}

		return prev_Product;
	}else
	{
		std::cerr << "ERROR!! Vectors need to have the same dimensions during a dot product operation! Vector sizes are: " +
			std::to_string(Row_Size_) + "x" + std::to_string(Column_Size_) + " and " +
			std::to_string(other_Matrix.Row_Size_) + "x" + std::to_string(other_Matrix.Column_Size_);

		throw std::invalid_argument("error");
	}

	return 0.0;
}


GMatrix GMatrix::operator+(const GMatrix& matrix)
{
	GMatrix new_Matrix = *this;
	if (Column_Size_ == matrix.Column_Size_ && Row_Size_ == matrix.Row_Size_)
	{
		for (int i = 0; i < Elements_.size(); i++)
		{
			for (int j = 0; j < Elements_[i].size(); j++)
			{
				new_Matrix.Elements_[i][j] += matrix.Elements_[i][j];
			}
		}

		return new_Matrix;
	}else
	{
		std::cerr << "ERROR!! Matrices need to have the same dimensions during matrix addition! Matrix sizes are: " +
			std::to_string(Row_Size_) + "x" + std::to_string(Column_Size_) + " and " +
			std::to_string(matrix.Row_Size_) + "x" + std::to_string(matrix.Column_Size_);

		throw std::invalid_argument("error");
	}

	return GMatrix();
}

GMatrix GMatrix::operator+=(const GMatrix& matrix)
{
	if (Column_Size_ == matrix.Column_Size_ && Row_Size_ == matrix.Row_Size_)
	{
		for (int i = 0; i < Elements_.size(); i++)
		{
			for (int j = 0; j < Elements_[i].size(); j++)
			{
				Elements_[i][j] += matrix.Elements_[i][j];
			}
		}

		return *this;
	}else
	{
		std::cerr << "ERROR!! Matrices need to have the same dimensions during matrix addition! Matrix sizes are: " +
			std::to_string(Row_Size_) + "x" + std::to_string(Column_Size_) + " and " +
			std::to_string(matrix.Row_Size_) + "x" + std::to_string(matrix.Column_Size_);

		throw std::invalid_argument("error");
	}

	return GMatrix();
}

GMatrix GMatrix::operator+(int scalar)
{
	GMatrix new_Matrix = *this;

	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			new_Matrix.Elements_[i][j] += scalar;
		}
	}

	return new_Matrix;
}

GMatrix GMatrix::operator+=(int scalar)
{
	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			Elements_[i][j] += scalar;
		}
	}

	return *this;
}

GMatrix GMatrix::operator-(const GMatrix& matrix)
{
	GMatrix new_Matrix = *this;
	if (Column_Size_ == matrix.Column_Size_ && Row_Size_ == matrix.Row_Size_)
	{
		for (int i = 0; i < Elements_.size(); i++)
		{
			for (int j = 0; j < Elements_[i].size(); j++)
			{
				new_Matrix.Elements_[i][j] -= matrix.Elements_[i][j];
			}
		}

		return new_Matrix;
	}else
	{
		std::cerr << "ERROR!! Matrices need to have the same dimensions during matrix subtraction! Matrix sizes are: " +
			std::to_string(Row_Size_) + "x" + std::to_string(Column_Size_) + " and " +
			std::to_string(matrix.Row_Size_) + "x" + std::to_string(matrix.Column_Size_);

		throw std::invalid_argument("error");
	}

	return GMatrix();
}

GMatrix GMatrix::operator-=(const GMatrix& matrix)
{
	if (Column_Size_ == matrix.Column_Size_ && Row_Size_ == matrix.Row_Size_)
	{
		for (int i = 0; i < Elements_.size(); i++)
		{
			for (int j = 0; j < Elements_[i].size(); j++)
			{
				Elements_[i][j] -= matrix.Elements_[i][j];
			}
		}

		return *this;
	}else
	{
		std::cerr << "ERROR!! Matrices need to have the same dimensions during matrix subtraction! Matrix sizes are: " +
			std::to_string(Row_Size_) + "x" + std::to_string(Column_Size_) + " and " +
			std::to_string(matrix.Row_Size_) + "x" + std::to_string(matrix.Column_Size_);

		throw std::invalid_argument("error");
	}

	return GMatrix();
}

GMatrix GMatrix::operator-(int scalar)
{
	GMatrix new_Matrix = *this;

	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			new_Matrix.Elements_[i][j] -= scalar;
		}
	}

	return new_Matrix;
}

GMatrix GMatrix::operator-=(int scalar)
{
	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			Elements_[i][j] -= scalar;
		}
	}

	return *this;
}

GMatrix GMatrix::operator*(GMatrix& matrix)
{
	GMatrix new_Matrix(GMatrix::Fill(matrix.Row_Size_, Column_Size_, 0.0));

	if (Row_Size_ == matrix.Column_Size_)
	{
		for (int i = 0; i < Column_Size_; i++)
		{
			for (int j = 0; j < matrix.Row_Size_; j++)
			{
				new_Matrix.Elements_[i][j] = Dot_Product(matrix, i, j, true, false);
			}
		}

		return new_Matrix;
	}else
	{
		std::cerr << "ERROR!! matrix factor 1 needs to have the size of its rows equal to matrix factor 2's column size during matrix multiplication! Matrix sizes are: " +
			std::to_string(Row_Size_) + "x" + std::to_string(Column_Size_) + " and " +
			std::to_string(matrix.Row_Size_) + "x" + std::to_string(matrix.Column_Size_);

		throw std::invalid_argument("error");
	}

	

	return GMatrix();
}

GMatrix GMatrix::operator*(int scalar)
{
	GMatrix new_Matrix = *this;

	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			new_Matrix.Elements_[i][j] *= scalar;
		}
	}

	return new_Matrix;
}

GMatrix GMatrix::operator*=(int scalar)
{
	for (int i = 0; i < Elements_.size(); i++)
	{
		for (int j = 0; j < Elements_[i].size(); j++)
		{
			Elements_[i][j] *= scalar;
		}
	}

	return *this;
}

const std::vector<double>& GMatrix::operator[](const int index)const
{
	return Elements_[index];
}

//GMatrix GMatrix::operator=(const GMatrix& matrix)
//{
//
//}