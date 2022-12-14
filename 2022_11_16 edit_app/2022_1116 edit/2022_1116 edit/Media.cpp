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
		   MessageBoxW(hDlg, LPCWSTR(L"setting��ʂ���܂���?")
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
	   hdrop = (HDROP)wParam; /* HDROP���擾 */

	   if (DragQueryFile(hdrop, 0, LPWSTR(buff), 256)) /* �ŏ��̃t�@�C�������擾 */
	   {
		   MessageBoxW(hDlg, LPCWSTR(L"setting��ʂ���܂���?")
			   , LPCWSTR(L"save"), MB_OK);
	   }

	   DragFinish(hdrop); /* �h���b�v�̏I������ */
	   return true;
   }

   HWND CreateAnimationCtrl(HWND hwndDlg, int nIDCtl, HINSTANCE hInstance)
   {
	   HWND hwndAnim = NULL;
	   RECT rc;
	   

	   hwndAnim = Animate_Create(hwndDlg, IDC_ANIMATE1,
		   WS_BORDER | WS_CHILD, hInstance);

	   (void)GetWindowRect(GetDlgItem(hwndDlg, nIDCtl), &rc);//nIDCtl�R���g���[����

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
         
                if(const auto pthis = reinterpret_cast<Media*>(GetWindowLongPtrW(hDlg, DWLP_USER)))//�����_����this���擾 DWLP_USER�g�����
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
                    SetWindowLongPtrW(hDlg, DWLP_USER, lParam);//�N���X���Z�b�g DWLP_USER�g�����
		   DragAcceptFiles(hDlg, TRUE);//�ǂ��̃_�C�A���O�{�b�N�X���w��Ȃ̂ł��̈ʒu

					//const auto hStatic = GetDlgItem(hDlg, IDC_CHECK1);//�n���h���擾
					//const auto pStaic = new Static(WNDPROC(GetWindowLongPtrW(hStatic, GWLP_WNDPROC)));//�N���X�̃A�h���X�擾

					//SetWindowLongPtrW(hStatic, GWLP_USERDATA, LONG_PTR(pStaic));//�X�^�e�B�b�N�n���h���ɃN���X�̃C���X�^���X���Z�b�g

					//SetWindowLongPtrW(hStatic, GWLP_WNDPROC, LONG_PTR(static_cast<WNDPROC>([](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept ->LRESULT
					//	{
					//		//�V�����E�B���h�E�v���V�[�W��

					//		switch (message)
					//		{
					//		case WM_COMMAND:

					//			switch (LOWORD(wParam))
					//			{
					//			case IDC_CHECK1:
					//				MessageBoxW(hWnd, LPCWSTR(L"setting��ʂ���܂���?")
					//					, LPCWSTR(L"save"), MB_OK);
					//				return true;

					//			default:
					//				return false;
					//			}

					//			return true;

					//		default:
					//			return false;
					//		}
					//		const auto pStaic = reinterpret_cast<Static*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));//new�����������Ă���
					//		const auto presult = reinterpret_cast<Static*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA))->WndProc(hWnd, message, wParam, lParam);//�O�̏ꏊ�͎����Ă���



					//		if (message == WM_NCDESTROY)
					//			delete pStaic;
					//		return presult;
					//	})));

		 
					
					return true;
                }
                else
                    return false;//�ŏ��̐���̃��b�Z�[�W����
               
            
              
              
         

              

         
        }
        ,/*_In_     LPARAM    dwInitParam   */LPARAM(this)
            );


}


