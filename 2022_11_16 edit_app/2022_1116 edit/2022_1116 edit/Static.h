#pragma once
#include<windows.h>
#include<CommCtrl.h>

class Static {

	WNDPROC Pwndproc;
public:
	Static(WNDPROC wndproc) noexcept;

	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;

};