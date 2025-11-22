#include <windows.h>
#include <windowsx.h>   // <-- REQUIRED for GET_X_LPARAM / GET_Y_LPARAM
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "msimg32.lib")
#include "purple2.h"
void SubclassMakePurple2(HWND dlg, int btnId)
{
    HWND h = GetDlgItem(dlg, btnId);
    if (h)
        SetWindowSubclass(h, PurpleButtonSubclassProc, btnId, 0);
    //SetWindowSubclass(hBtn, PurpleButtonSubclassProc, (UINT_PTR)btnId, 0);

}

LRESULT CALLBACK PurpleButtonSubclassProc2(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR id, DWORD_PTR ref)
{
    static BOOL hover = FALSE;
    static BOOL pressed = FALSE;

    switch (msg)
    {
    case WM_NCDESTROY:
        RemoveWindowSubclass(hwnd, PurpleButtonSubclassProc2, id);
        break;

    case WM_MOUSEMOVE:
    {
        TRACKMOUSEEVENT t = { sizeof(t), TME_LEAVE, hwnd, 0 };
        TrackMouseEvent(&t);

        if (!hover) {
            hover = TRUE;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }

    case WM_MOUSELEAVE:
        hover = FALSE;
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_LBUTTONDOWN:
        pressed = TRUE;
        SetCapture(hwnd);
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_LBUTTONUP:
        if (pressed) {
            pressed = FALSE;
            ReleaseCapture();
            InvalidateRect(hwnd, NULL, TRUE);

            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            RECT rc;
            GetClientRect(hwnd, &rc);

            if (PtInRect(&rc, pt)) {
                HWND parent = GetParent(hwnd);
                SendMessage(parent, WM_COMMAND,
                    MAKEWPARAM(id, BN_CLICKED), (LPARAM)hwnd);
            }
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Let Windows draw the normal button first
        DefSubclassProc(hwnd, WM_PAINT, wParam, lParam);

        // Draw our purple background
        RECT rc;
        GetClientRect(hwnd, &rc);

        COLORREF color = RGB(128, 0, 128);     // normal purple
        if (hover)   color = RGB(150, 0, 150); // hover color
        if (pressed) color = RGB(80, 0, 80);   // pressed color

        HBRUSH br = CreateSolidBrush(color);
        FillRect(hdc, &rc, br);
        DeleteObject(br);

        EndPaint(hwnd, &ps);
        return 0;
    }
    }

    return DefSubclassProc(hwnd, msg, wParam, lParam);
}
