#pragma once
#include "resource1.h"
#include <string>

class MyTable
{
public:
	void OpenTable(HWND, void fn_pick(HWND, const int, const bool), void fn_rm(HWND, const int));
	void AddShape(const char*, const int*);
	void CleanTable();
	void ReadFile(HWND, void fn_show(HDC, const std::string, const int*));
};
