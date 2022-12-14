#include "Media.h"

#include "Static.h"
#include"resource.h"


   static bool setting_switch = false;



   template<> INT_PTR Media::HandleCommand<IDOK>(HWND hDlg, WORD wHiword, HWND hCtrl) noexcept
   {
	   if (setting_switch == false) {
		   Dialogbox d;
		   setting_switch = true;
		   d.DialogBoxParamW(nullptr);
	   }
	   else if (setting_switch == true)
	   {
		   MessageBoxW(hDlg, LPCWSTR(L"setting画面を閉じますか?")
			   , LPCWSTR(L"save"), MB_OK);
	   }


	   return true;
   }

   template<> INT_PTR Media::HandleCommand<IDCANCEL>(HWND hDlg, WORD wHiword, HWND hCtrl) noexcept
   {
	  
	   EndDialog(hDlg, IDCANCEL);
	   return true;
   }



   template<> INT_PTR Media::HandleMessage<WM_COMMAND>(HWND hDlg, WPARAM wParam, LPARAM lParam) noexcept
{




	switch (LOWORD(wParam))
	{
	
  #define dis(id) case id: return HandleCommand<id>(hDlg, HIWORD(wParam), HWND(lParam));
  
  	    dis(IDOK)
		dis(IDCANCEL)
	


  #undef dis
		



	default:
		return false;//switch
	}

}

   template<> INT_PTR Media::HandleMessage<WM_DROPFILES>(HWND hDlg, WPARAM wParam, LPARAM lParam) noexcept
   {
	   TCHAR buff[200];
	   HDROP hdrop;
	   hdrop = (HDROP)wParam; /* HDROPを取得 */

	   if (DragQueryFile(hdrop, 0, LPWSTR(buff), 256)) /* 最初のファイル名を取得 */
	   {
		   MessageBoxW(hDlg, LPCWSTR(L"setting画面を閉じますか?")
			   , LPCWSTR(L"save"), MB_OK);
	   }

	   DragFinish(hdrop); /* ドロップの終了処理 */
	   return true;
   }

   HWND CreateAnimationCtrl(HWND hwndDlg, int nIDCtl, HINSTANCE hInstance)
   {
	   HWND hwndAnim = NULL;
	   RECT rc;
	   

	   hwndAnim = Animate_Create(hwndDlg, IDC_ANIMATE1,
		   WS_BORDER | WS_CHILD, hInstance);

	   (void)GetWindowRect(GetDlgItem(hwndDlg, nIDCtl), &rc);//nIDCtlコントロール名

	   POINT pt;
	   pt.x = rc.left;
	   pt.y = rc.bottom;
	   ScreenToClient(hwndDlg, &pt);

	   SetWindowPos(hwndAnim, 0, pt.x, pt.y + 20,
		   1000, 1000,
		   SWP_NOZORDER | SWP_DRAWFRAME);

	   // Open the AVI clip, and show the animation control.
	   Animate_Open(hwndAnim, "SEARCH.AVI");
	   ShowWindow(hwndAnim, SW_SHOW);

	   return hwndAnim;
   }

   void DoAnimation(HWND hwndAnim, int nAction)
   {
	   int const PLAYIT = 1, STOPIT = 2, CLOSEIT = 3;
	   switch (nAction) {
	   case PLAYIT:
		   // Play the clip continuously starting with the 
		   // first frame. 
		   Animate_Play(hwndAnim, 0, -1, -1);
		   break;

	   case STOPIT:
		   Animate_Stop(hwndAnim);
		   break;

	   case CLOSEIT:
		   Animate_Close(hwndAnim);
		   break;

	   default:
		   break;
	   }
   }

INT_PTR Media::MediaBoxParamW(HWND hWndParent, HINSTANCE hInstance) noexcept
{
 
   return DialogBoxParamW(
        /*_In_opt_ HINSTANCE hInstance,    */nullptr
       ,/*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG2)
       ,/*_In_opt_ HWND      hWndParent,   */nullptr
       ,/*_In_opt_ DLGPROC   lpDialogFunc, */[](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) noexcept ->INT_PTR
       {
         
                if(const auto pthis = reinterpret_cast<Media*>(GetWindowLongPtrW(hDlg, DWLP_USER)))//ラムダ式→thisを取得 DWLP_USER拡張情報
                {

					switch (message)
					{

						
#define dis(id) case id: return pthis->HandleMessage<id>(hDlg,  wParam,  lParam);

						dis(WM_COMMAND)
						dis(WM_DROPFILES)
#undef dis
							
					default:
						return false;
					}
					

                } else if(message == WM_INITDIALOG)
                {
                    SetWindowLongPtrW(hDlg, DWLP_USER, lParam);//クラスをセット DWLP_USER拡張情報
		   DragAcceptFiles(hDlg, TRUE);//どこのダイアログボックスか指定なのでこの位置

					//const auto hStatic = GetDlgItem(hDlg, IDC_CHECK1);//ハンドル取得
					//const auto pStaic = new Static(WNDPROC(GetWindowLongPtrW(hStatic, GWLP_WNDPROC)));//クラスのアドレス取得

					//SetWindowLongPtrW(hStatic, GWLP_USERDATA, LONG_PTR(pStaic));//スタティックハンドルにクラスのインスタンスをセット

					//SetWindowLongPtrW(hStatic, GWLP_WNDPROC, LONG_PTR(static_cast<WNDPROC>([](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept ->LRESULT
					//	{
					//		//新しいウィンドウプロシージャ

					//		switch (message)
					//		{
					//		case WM_COMMAND:

					//			switch (LOWORD(wParam))
					//			{
					//			case IDC_CHECK1:
					//				MessageBoxW(hWnd, LPCWSTR(L"setting画面を閉じますか?")
					//					, LPCWSTR(L"save"), MB_OK);
					//				return true;

					//			default:
					//				return false;
					//			}

					//			return true;

					//		default:
					//			return false;
					//		}
					//		const auto pStaic = reinterpret_cast<Static*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));//newしたやつを取ってきた
					//		const auto presult = reinterpret_cast<Static*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))->WndProc(hWnd, message, wParam, lParam);//前の場所は持っていく



					//		if (message == WM_NCDESTROY)
					//			delete pStaic;
					//		return presult;
					//	})));

		 
					
					return true;
                }
                else
                    return false;//最初の数回のメッセージ処理
               
            
              
              
         

              

         
        }
        ,/*_In_     LPARAM    dwInitParam   */LPARAM(this)
            );


}


