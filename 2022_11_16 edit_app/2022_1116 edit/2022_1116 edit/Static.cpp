#include "Static.h"
#include<tuple>

#include"resource.h"

Static::Static(WNDPROC wndproc) noexcept //ƒRƒ“ƒXƒg‚ç‚­‘½
	: Pwndproc{ wndproc }
{

}

LRESULT Static::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	
	

	return CallWindowProcW//Œ³‚É–ß‚·
	(
		 /*_In_ WNDPROC lpPrevWndFunc*/Pwndproc
		,/*_In_ HWND hWnd,			 */hWnd
		,/*_In_ UINT Msg,			 */message
		,/*_In_ WPARAM wParam,		 */wParam
		,/*_In_ LPARAM lParam		 */lParam
	);
}

