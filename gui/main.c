// Source - https://stackoverflow.com/a/18773514
// Posted by FrogTheFrog
// Retrieved 2025-11-22, License - CC BY-SA 3.0

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

#include <Windows.h>
#include <Commctrl.h>
#include "resource.h"


LRESULT CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
    case WM_NOTIFY:
    {
        LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)lParam;
        if (item->hdr.idFrom == IDC_BUTTON2 && item->hdr.code == NM_CUSTOMDRAW)
        {

            HDC hdc = item->hdc;
            RECT rc = item->rc;
            UINT state = item->uItemState;
            COLORREF normal = RGB(0, 255, 255); // purple 
            COLORREF hover = RGB(0, 255, 160); // lighter 
            COLORREF pressed = RGB(96, 0, 128); // darker 
            COLORREF bg; 
            if (state & CDIS_SELECTED) bg = pressed; 
            else if (state & CDIS_HOT) bg = hover; 
            else bg = normal; 

            HBRUSH br = CreateSolidBrush(bg);
            FillRect(hdc, &rc, br);
            DeleteObject(br);
            return CDRF_DODEFAULT;
                
        }
        break;
    case WM_CTLCOLORBTN: //In order to make those edges invisble when we use RoundRect(),
    {                //we make the color of our button's background match window's background
        return (LRESULT)GetSysColorBrush(COLOR_WINDOW + 1);
    }
    break;
    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        return 0;
    }
    break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
