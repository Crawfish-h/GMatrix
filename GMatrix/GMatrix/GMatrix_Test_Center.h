#pragma once
#include "GMatrix.h"

class GMatrix_Test_Center
{
public:
	static void Select_Test();

private:
	static GMatrix One_Matrix_From_Input();
	static GMatrix Two_Matrices_From_Input();

	static void Transpose();
	static void Print();
	static void Get_Row();
	static void Get_Column();
	static void Dot_Product();
	static void Add_Matrices();
	static void Add_Scalar_To_Matrix();
	static void Subtract_Matrices();
	static void Multiply_Matrices();
};


