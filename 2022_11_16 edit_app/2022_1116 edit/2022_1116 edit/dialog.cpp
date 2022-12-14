#include"dialog.h"


INT_PTR Dialogbox::DialogBoxParamW(HWND hWndParent) noexcept
{

    return ::DialogBoxParamW(
         /*_In_opt_ HINSTANCE hInstance,    */nullptr
        ,/*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
        ,/*_In_opt_ HWND      hWndParent,   */nullptr
        ,/*_In_opt_ DLGPROC   lpDialogFunc, */[](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) noexcept ->INT_PTR
        {
            switch (message)
            {

            case WM_INITDIALOG:

                return true;

            case WM_COMMAND:


                switch (LOWORD(wParam))
                {
                case IDOK:

                    return true;

                case IDCANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return true;


                default:
                    return false;
                }

                return true;

            case WM_DESTROY:
                EndDialog(hDlg, WM_DESTROY);
                return true;


            default:
                return false;
            }
        }
        ,/*_In_     LPARAM    dwInitParam   */LPARAM(this)
            );

	
}
