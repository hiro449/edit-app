#include "Static.h"
#include<tuple>

#include"resource.h"

Static::Static(WNDPROC wndproc) noexcept //�R���X�g�炭��
	: Pwndproc{ wndproc }
{

}

LRESULT Static::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	
	

	return CallWindowProcW//���ɖ߂�
	(
		 /*_In_ WNDPROC lpPrevWndFunc*/Pwndproc
		,/*_In_ HWND hWnd,			 */hWnd
		,/*_In_ UINT Msg,			 */message
		,/*_In_ WPARAM wParam,		 */wParam
		,/*_In_ LPARAM lParam		 */lParam
	);
}

