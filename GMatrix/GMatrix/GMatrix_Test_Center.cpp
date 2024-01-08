#include "GMatrix_Test_Center.h"
#include <iostream>
#include <string>

void GMatrix_Test_Center::Select_Test()
{
	std::cout << "Press 1 to test the transpose function.\n2 for Print.\n3 for Get_Row.\n4 for Get_Column.\n5 for Dot_Product.\n6 for adding matrices.\n" <<
		"7 for adding scalars to matrices.\n8 for subtracting matrices.\n9 for multiplying matrices.\n\n";

	int input = 1;
	std::cout << "Enter test number: ";
	std::cin >> input;
	std::cout << "\n\n";

	switch (input)
	{
	case 1:
		Transpose();
		break;
	case 2:
		Print();
		break;
	case 3:
		Get_Row();
		break;
	case 4:
		Get_Column();
		break;
	case 5:
		Dot_Product();
		break;
	case 6:
		Add_Matrices();
		break;
	case 7:
		Add_Scalar_To_Matrix();
		break;
	case 8:
		Subtract_Matrices();
		break;
	case 9:
		Multiply_Matrices();
		break;
	default:
		Transpose();
		break;
	}

	std::cout << "\n\nDo you want to exit this program? (y/n)";

	std::string input_String = "";
	std::cin >> input_String;

	if (input_String == "y" || input_String == "Y")
	{
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		Select_Test();
	}

}

GMatrix GMatrix_Test_Center::One_Matrix_From_Input()
{
	int row_Input = 2;
	int column_Input = 3;
	int matrix_Values = 3;

	std::cout << "Enter matrix row size: ";
	std::cin >> row_Input;

	std::cout << "\nEnter matrix colmun size: ";
	std::cin >> column_Input;

	std::cout << "\nEnter matrix values (enter 8675 for random values): ";
	std::cin >> matrix_Values;

	std::cout << "\n";

	GMatrix matrix;

	if (matrix_Values == 8675)
	{
		GMatrix temp_Matrix(GMatrix::Random(row_Input, column_Input, -100, 100, true));
		matrix = temp_Matrix;
	}else
	{
		GMatrix temp_Matrix(GMatrix::Fill(row_Input, column_Input, matrix_Values));
		matrix = temp_Matrix;
	}

	return matrix;
}

GMatrix GMatrix_Test_Center::Two_Matrices_From_Input()
{
	GMatrix m;
	return m;
}

void GMatrix_Test_Center::Transpose()
{
	One_Matrix_From_Input().Transpose().Print();
}

void GMatrix_Test_Center::Print()
{
	One_Matrix_From_Input().Print();
}

void GMatrix_Test_Center::Get_Row()
{
	std::cout << "if inputed matrix's amount of rows is greater than one, only the first row will be converted and printed.\n\n";
	One_Matrix_From_Input().Get_Row(0).Print();
}

void GMatrix_Test_Center::Get_Column()
{
	std::cout << "if inputed matrix's amount of columns is greater than one, only the first column will be converted and printed.\n\n";
	One_Matrix_From_Input().Get_Column(0).Print();
}

void GMatrix_Test_Center::Dot_Product()
{
	std::cout << "if inputed matrices' amount of columns is greater than one, only the first columns will be used.\n" <<
		"Matricies need to have the same column size if the Dot_Product function row arguments are left unchanged.\n\n";

	std::cout << "First vector:\n";
	GMatrix matrix_One = One_Matrix_From_Input();

	std::cout << "Second vector:\n";
	GMatrix matrix_Two = One_Matrix_From_Input();

	std::cout << "Dot Product: " << matrix_One.Dot_Product(matrix_Two, 0, 0) << "\n\n";
}

void GMatrix_Test_Center::Add_Matrices()
{
	std::cout << "If matrices are not the same size, then an error will occur.\n\n";

	std::cout << "First matrix:\n";
	GMatrix matrix_One = One_Matrix_From_Input();

	std::cout << "Second matrix:\n";
	GMatrix matrix_Two = One_Matrix_From_Input();

	GMatrix matrix_Sum = matrix_One + matrix_Two;

	matrix_Sum.Print();
}

void GMatrix_Test_Center::Add_Scalar_To_Matrix()
{
	std::cout << "Enter a matrix:\n";
	GMatrix matrix = One_Matrix_From_Input();

	int input = 0;

	std::cout << "Enter a scalar:\n";
	std::cin >> input;

	std::cout << "\n\n";

	matrix += input;
	matrix.Print();
}

void GMatrix_Test_Center::Subtract_Matrices()
{
	std::cout << "If matrices are not the same size, then an error will occur.\n\n";

	std::cout << "First matrix:\n";
	GMatrix matrix_One = One_Matrix_From_Input();

	std::cout << "Second matrix:\n";
	GMatrix matrix_Two = One_Matrix_From_Input();

	GMatrix matrix_Sum = matrix_One - matrix_Two;

	matrix_Sum.Print();
}

void GMatrix_Test_Center::Multiply_Matrices()
{
	std::cout << "If matrix 1's row size does not equal matrix 2's column size, then an error will occur.\n\n";

	std::cout << "First matrix:\n";
	GMatrix matrix_One = One_Matrix_From_Input();

	std::cout << "Second matrix:\n";
	GMatrix matrix_Two = One_Matrix_From_Input();

	GMatrix matrix_Product = matrix_One * matrix_Two;

	matrix_Product.Print();
}
