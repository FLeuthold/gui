
#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include <commctrl.h>
#include <richedit.h> 
#pragma comment(lib, "comctl32.lib")
//#define ID_BTN 1054
int gret = 0;

LRESULT CALLBACK ButtonSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
    UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg) {
    case WM_ERASEBKGND:
        // tell Windows we handled background erase (we draw it ourselves)
        return 1;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // First: draw purple background ourselves every paint
        RECT rc;
        GetClientRect(hwnd, &rc);
        HBRUSH hBrush = CreateSolidBrush(RGB(180, 100, 200)); // purple
        FillRect(hdc, &rc, hBrush);
        DeleteObject(hBrush);

        // Then ask default proc to draw the themed borders/visuals
        // Pass the hdc so theme renderer paints into our DC
        DefSubclassProc(hwnd, WM_PAINT, (WPARAM)hdc, (LPARAM)&ps);

        // Finally draw the text on top (so it's visible)
        wchar_t text[128];
        GetWindowText(hwnd, text, (int)_countof(text));
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 255, 255));
        DrawText(hdc, text, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_NCDESTROY:
        // remove subclass when control is destroyed
        RemoveWindowSubclass(hwnd, ButtonSubclassProc, uIdSubclass);
        break;
    }

    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_CREATE: {
        // create a normal pushbutton (themed)
        HWND hBtn = CreateWindowExW(0, L"BUTTON", L"Purple",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
            20, 20, 120, 30, wnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);

        // attach subclass (requires comctl32 and InitCommonControlsEx)
        SetWindowSubclass(hBtn, ButtonSubclassProc, 1, 0);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(wnd, msg, wp, lp);
}

// Die Callback Funktion
// INT_PTR CALLBACK ist der korrekte Typ für 64-Bit Windows DialogProcs
INT_PTR CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {

    case WM_INITDIALOG: {
        HWND hBtn = GetDlgItem(hwnd, IDC_MYBUTTON);
        //SetWindowSubclass(hBtn, ButtonSubclassProc, 1, 0);
    
        HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Option 1");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Option 2");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"Option 3");


        HWND hComboEx = GetDlgItem(hwnd, IDC_COMBOBOXEX1);

        COMBOBOXEXITEM cbei;
        ZeroMemory(&cbei, sizeof(COMBOBOXEXITEM));
        cbei.mask = CBEIF_TEXT;   // we’re only setting text for now
        cbei.iItem = -1;          // append at end
        cbei.pszText = L"Option 1";
        SendMessage(hComboEx, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

        cbei.pszText = L"Option 2";
        SendMessage(hComboEx, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

        cbei.pszText = L"Option 3";
        SendMessage(hComboEx, CBEM_INSERTITEM, 0, (LPARAM)&cbei);

        // Select first item
        SendMessage(hComboEx, CB_SETCURSEL, 0, 0);
        /*HWND hCombo22 = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(hCombo22, CB_ADDSTRING, 0, (LPARAM)L"Option 1");
        SendMessage(hCombo22, CB_ADDSTRING, 0, (LPARAM)L"Option 2");
        SendMessage(hCombo22, CB_ADDSTRING, 0, (LPARAM)L"Option 3");*/

        HWND hList = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Option 1");
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Option 2");
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Option 3");
        // Optionally select the first item
        SendMessage(hCombo, CB_SETCURSEL, 0, 0);
        return (INT_PTR)TRUE;
    }
    case WM_CTLCOLORBTN: {
        HDC hdcBtn = (HDC)wParam;
        SetBkMode(hdcBtn, TRANSPARENT);
        SetTextColor(hdcBtn, RGB(150, 150, 220));
        return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
    }
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON1: {
            MessageBox(hwnd, L"Klick!", L"Info", MB_OK);
            SetDlgItemText(hwnd, IDC_STATIC1, L"Button wurde geklickt!");
        }
                           break;
        case IDC_MYBUTTON: {
            if (gret == 0) {
                SetDlgItemText(hwnd, IDC_STATIC1, L"Button wurde");
                gret = 1;
            } else {
                SetDlgItemText(hwnd, IDC_STATIC1, L"Button wurde gret");
                gret = 0;
            }
            
        }
                        break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;

    default:
        return (INT_PTR)FALSE;
    }
    return (INT_PTR)TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 2. Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES; // or ICC_STANDARD_CLASSES, ICC_USEREX_CLASSES, etc.
    InitCommonControlsEx(&icex);
    // DialogBox gibt einen INT_PTR zurück, WinMain erwartet int. Wir casten es.
    return (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}