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



            //HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));


            //HGDIOBJ old_pen = SelectObject(item->hdc, pen);
            //HGDIOBJ old_brush = SelectObject(item->hdc, br);
            //RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 10, 10);
            FillRect(hdc, &rc, br);
            DeleteObject(br);
            //SelectObject(item->hdc, old_pen);
            //SelectObject(item->hdc, old_brush);
            //DeleteObject(pen);
            //DrawFrameControl(hdc, &rc, DFC_BUTTON, DFCS_BUTTONPUSH | ((state & CDIS_SELECTED) ? DFCS_PUSHED : 0)); // Draw text centered 
            //wchar_t text[128]; GetWindowText(item->hdr.hwndFrom, text, 128); SetBkMode(hdc, TRANSPARENT);
            //SetTextColor(hdc, RGB(255, 255, 255)); // white text 
            //DrawText(hdc, text, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            /*
            FillRect(hdc, &rc, br); 
            DeleteObject(br); // Draw themed button frame 
            DrawFrameControl(hdc, &rc, DFC_BUTTON, DFCS_BUTTONPUSH | ((state & CDIS_SELECTED) ? DFCS_PUSHED : 0)); // Draw text centered 
            wchar_t text[128]; GetWindowText(item->hdr.hwndFrom, text, 128); SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255)); // white text 
            DrawText(hdc, text, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE); */
            return CDRF_DODEFAULT; // do NOT let Windows overpaint


                /*
                COLORREF bg = RGB(0,255,255);
                if (item->uItemState & CDIS_SELECTED)
                {
                    bg = RGB(96, 0, 128);
                    
                }
                HBRUSH br = CreateSolidBrush(bg);
                HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));


                HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                HGDIOBJ old_brush = SelectObject(item->hdc, br);


                RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 10, 10);


                SelectObject(item->hdc, old_pen);
                SelectObject(item->hdc, old_brush);
                DeleteObject(pen);


                return CDRF_DODEFAULT;
                */
                
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
