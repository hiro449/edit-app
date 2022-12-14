#pragma once

#include"dialog.h"

class Media
{
public:
	 
	template<WORD id> INT_PTR HandleCommand(HWND hDlg, WORD word, HWND hCtrl) noexcept;

	template<unsigned message> INT_PTR HandleMessage(HWND hDlg, WPARAM wParam, LPARAM lParam) noexcept;

	INT_PTR  MediaBoxParamW(HWND hWndParent, HINSTANCE hInstance) noexcept;

	
};


