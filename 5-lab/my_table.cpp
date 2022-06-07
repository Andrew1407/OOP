#include "framework.h"
#include "my_table.h"
#include <fstream>

static const std::string fileWrite = "shapes.txt";			//writefile name
static const std::string fileRead = "shapesRead.txt";			//readfile name

static int Index = 0;
static std::string ShapeList[106];
static HWND hWnd_nomodal;
static HINSTANCE hInst;
static INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
static const char* str_elements[5] = { ": ", " x1: ", " y1: ", " x2: ", " y2: " };
static bool isCreated = true;

//Callbacks, args
static void (*PickShape)(HWND, const int, const bool);
static void (*RemoveShape)(HWND, const int);
static HWND hMain;
static bool isPicked = false;
static int prevEl = -1;

void MyTable::OpenTable(HWND hWnd_MAIN, void fn_pick(HWND, const int, const bool), void fn_rm(HWND, const int))
{
	PickShape = fn_pick;
	RemoveShape = fn_rm;
	hMain = hWnd_MAIN;

	hWnd_nomodal = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SHAPES_TABLE), 0, DlgProc);
	ShowWindow(hWnd_nomodal, SW_SHOW);
}

static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SetWindowText(hWnd, "Список фігур");
		for (int i = 0; i < Index; i++)
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, LPARAM(ShapeList[i].c_str()));
		return 1;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CLOSE:
		{
			DestroyWindow(hWnd);
		}
		break;
		case ID_RM_SHAPE:
		{
			int el_picked = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
			
			if (el_picked != -1)
			{
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_DELETESTRING, el_picked, 0);
				RemoveShape(hMain, el_picked);
				for (int i = el_picked + 1; i < Index; i++)
					ShapeList[i - 1] = ShapeList[i];
				Index--;

				//Avoiding wrong pick
				if (prevEl == el_picked && isPicked) PickShape(hMain, -1, 0);

				//REWRITE FILE
				std::ofstream out;
				out.open(fileWrite);
				out << "";
				out.close();
				out.open(fileWrite, std::ios::app);
				if (out.is_open())
					for (int i = 0; i < Index; i++) out << ShapeList[i] << std::endl;
				out.close();
			}
		} 
		break;
		case ID_PICK_SAHPE:
		{
			int el_picked = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0);

			if (el_picked != -1)
			{
				if (prevEl != el_picked && prevEl != -1) isPicked = !isPicked;
				if (isPicked && prevEl != el_picked && prevEl != -1) isPicked = !isPicked;

				PickShape(hMain, el_picked, isPicked);
				isPicked = !isPicked;
				prevEl = el_picked;
			}
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	}
	return 0;
}

void MyTable::AddShape(const char* str, const int* coords)
{
	std::string data = str;
	data += str_elements[0];
	for (int i = 0; i < 4; i++)
		if (coords[i] != -1)
			data += str_elements[i + 1] + std::to_string(coords[i]) + ";";


	ShapeList[Index] = data.c_str();
	SendDlgItemMessage(hWnd_nomodal, IDC_LIST1, LB_ADDSTRING, 0, LPARAM(ShapeList[Index++].c_str()));

	//WRITE FILE
	setlocale(LC_ALL, "Rus");
	std::ofstream out;
	isCreated ? out.open(fileWrite) : out.open(fileWrite, std::ios::app);
	if(isCreated) isCreated = false;
	if (out.is_open()) out << data << std::endl;
	out.close();
}

void MyTable::CleanTable()
{
	
	if (!SendDlgItemMessage(hWnd_nomodal, IDC_LIST1, LB_GETCOUNT, 0, 0)) return;	//if list is empty

	while(SendDlgItemMessage(hWnd_nomodal, IDC_LIST1, LB_GETCOUNT, 0, 0))
		SendMessage(GetDlgItem(hWnd_nomodal, IDC_LIST1), LB_DELETESTRING, --Index, 0);

 
	prevEl = -1;
	isPicked = false;
	PickShape(hMain, -1, isPicked);

	//CLEAN FILE
	std::ofstream out;
	out.open(fileWrite);
	if (isCreated) isCreated = false;
	if (out.is_open()) out << "";
	out.close();
}

void MyTable::ReadFile(HWND hWnd, void fn_show(HDC, const std::string, const int*))
{
	while (SendDlgItemMessage(hWnd_nomodal, IDC_LIST1, LB_GETCOUNT, 0, 0))
		SendMessage(GetDlgItem(hWnd_nomodal, IDC_LIST1), LB_DELETESTRING, --Index, 0);

	if (hMain)
	{
		prevEl = -1;
		isPicked = false;
		PickShape(hMain, -1, isPicked);
	}

	std::ifstream fin;
	setlocale(LC_ALL, "Rus");
	fin.open(fileRead);
	if (fin.is_open())
	{
		std::string data;

		while (!fin.eof())
		{
			data = "";
			std::getline(fin, data);
			if (data.length()) ShapeList[Index++] = data;
		}
	}
	fin.close();

	InvalidateRect(hWnd, 0, 1);
	HDC hdc = GetDC(hWnd);

	
	int idx_str = 0;

	//fill table and area
	for (int i = 0; i < Index; i++)
	{
		const std::string str = ShapeList[i];
		int coords[4] = { 0, 0, 0, 0 };
		std::string shapeType = "";
		SendDlgItemMessage(hWnd_nomodal, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)str.c_str());

		for (idx_str = 0; str[idx_str] != ':'; idx_str++) shapeType += str[idx_str];

		idx_str++;
		for (int u = 0; u < 4; u++)
		{
			if (shapeType == "Точка" && u > 1)
			{
				coords[2] = coords[0];
				coords[3] = coords[1];
				break;
			}

			for (idx_str; str[idx_str] != ':'; idx_str++);
			idx_str++;
			std::string coords_str = "";
			for (idx_str; str[idx_str] != ';'; idx_str++) coords_str += str[idx_str];
			idx_str++;
			coords[u] = std::stoi(coords_str);
		}
		fn_show(hdc, shapeType, coords);
	}
	ReleaseDC(hWnd, hdc);
}
