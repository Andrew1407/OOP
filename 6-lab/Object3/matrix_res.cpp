#include "framework.h"
#include <string>
#include "matrix_res.h"

static void getMatrixWithoutRowAndCol(float**, int, int, int, float**);
static float Determinant(float**, int);

long GetTextFromClipboard(HWND hWnd, char* dest, long maxsize) 
{
	HGLOBAL hglb; 
	LPTSTR lptstr; 
	long size, res;

	res = 0; 
	if (!IsClipboardFormatAvailable(CF_TEXT)) return 0; 
	if (!OpenClipboard(hWnd)) return 0; 
	hglb = GetClipboardData(CF_TEXT); 
	if (hglb != NULL) 
	{ 
		lptstr = (char*)GlobalLock(hglb);
		if (lptstr != NULL) 
		{ 
			size = strlen(lptstr);       
			if (size > maxsize) 
			{ 
				lptstr[maxsize] = 0;
				size = strlen(lptstr); 
			}       
			strcpy_s(dest, 300, lptstr);
			res = size;
			GlobalUnlock(hglb);
		} 
	} 
	CloseClipboard(); 
	return res;
}

float GetMatrixDet(const char* char_buff, const int buff_len, const int size)
{
	float** Matrix = new float* [size];
	for (int i = 0; i < size; i++) Matrix[i] = new float[size];

	std::string buff = char_buff;
	int strCounter = 0;
	std::string el = "";

	for (int i = 0; i < size; i++)
	{
		for (int u = 0; u < size; u++)
		{
			el = "";
			for (strCounter; buff[strCounter] != ' '; strCounter++)
			{
				el += buff[strCounter];
			}
			strCounter += 2;				//to avoid spacing
			Matrix[i][u] = std::stof(el);
		}
	}
	
	const float det = Determinant(Matrix, size);

	for (int i = 0; i < size; i++) delete[] Matrix[i];
	delete[] Matrix;

	return det;
}

float Determinant(float** matrix, int size) {
	float det = 0;
	int degree = 1;

	switch (size)
	{
	case 1:
		return matrix[0][0];
	case 2:
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	default:
		{
			float** newMatrix = new float* [size - 1];
			for (int i = 0; i < size - 1; i++) {
			newMatrix[i] = new float[size - 1];
			}

			for (int j = 0; j < size; j++) {
				getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

				det = det + (degree * matrix[0][j] * Determinant(newMatrix, size - 1));
				degree = -degree;
			}

			for (int i = 0; i < size - 1; i++) {
				delete[] newMatrix[i];
			}
			delete[] newMatrix;
		}
	}

	return det;
}

void getMatrixWithoutRowAndCol(float** matrix, int size, int row, int col, float** newMatrix) {
	int offsetRow = 0; 
	int offsetCol = 0; 
	for (int i = 0; i < size - 1; i++) {

		if (i == row) {
			offsetRow = 1;
		}

		offsetCol = 0; 
		for (int j = 0; j < size - 1; j++) {
			if (j == col) {
				offsetCol = 1;
			}

			newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
		}
	}
}
