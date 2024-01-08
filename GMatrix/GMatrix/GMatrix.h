#pragma once
#include <vector>
#include <string> 

class GMatrix
{
public:
#define FROM_VECTOR -928

	GMatrix(std::vector<std::vector<double>> elements, int row_Size = FROM_VECTOR, int column_Size = FROM_VECTOR);
	GMatrix();
	~GMatrix();

	// Classes used for returned from functions.
	class Set_Size_Result
	{
	public:
		friend GMatrix;

		bool Rows_Deleted;
		bool Columns_Deleted;
	private:
		Set_Size_Result() { Rows_Deleted = false; Columns_Deleted = false; }
	};


	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Utillity function that fills a maxtrix (2d vector) with rows --
	// and collumns of row_Size and column_Size with random numbers in a range of min to max.
	static std::vector<std::vector<double>> Random(int row_Size, int column_Size, double min, double max, bool use_Integers = false);

	// Utillity function that fills a maxtrix (2d vector) with rows --
	// and collumns of row_Size and column_Size with the argument "number".
	static std::vector<std::vector<double>> Fill(int row_Size, int column_Size, double number);

	GMatrix Transpose();

	// Returns true if this GMatrix is completely empty. Precision limits the amount of decimals that are shown.
	bool Print(unsigned int precision = 0);

	// Set_Size_Result.Rows_Deleted will be true if elements of columns were deleted.
	// Set_Size_Result.Columns_Deleted will be true if elements of rows were deleted.
	// The argument, "double value", determines the value that fills the child vector's --
	// new elements when they get resized.
	const Set_Size_Result& Set_Row_Column_Size(int row_Size, int column_Size, double value);

	// First is rows, second is columns.
	const std::pair<int, int>& Dimensions();

	// Returns the Elements_ vector by value.
	std::vector<std::vector<double>> Get();

	// Returns a row of the Elements_ vector by value.
	GMatrix Get_Row(int row);

	// Returns a column of the Elements_ vector by value.
	GMatrix Get_Column(int column);

	double Dot_Product(GMatrix& other_Matrix, int self_Index, int other_Index, bool self_Row = false, bool other_Row = false);

//----------------- Matrix Operations ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.

	GMatrix operator+(const GMatrix& matrix);
	GMatrix operator+=(const GMatrix& matrix);

	GMatrix operator+(int scalar);
	GMatrix operator+=(int scalar);

	GMatrix operator-(const GMatrix& matrix);
	GMatrix operator-=(const GMatrix& matrix);

	GMatrix operator-(int scalar);
	GMatrix operator-=(int scalar);

	GMatrix operator*(GMatrix& matrix);
	GMatrix operator*(int scalar);
	GMatrix operator*=(int scalar);

	/*GMatrix operator=(const GMatrix& matrix)*/;

	const std::vector<double>& operator[](const int index)const;

private:
	std::vector<std::vector<double>> Elements_;
	// Not the total size of the actual matrix but the size of each row and column.

	// Originally had one variable that controlled the size of both columns and rows but that was changed.
	int Row_Size_; // The size of the child vectors of Elements_.
	int Column_Size_; // The size of Elements_ (the parent vector). 
};

