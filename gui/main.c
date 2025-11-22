#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include <commctrl.h>

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;

        if (dis->CtlID == IDC_BUTTON2) {
            BOOL pressed = (dis->itemState & ODS_SELECTED) != 0;
            BOOL focused = (dis->itemState & ODS_FOCUS) != 0;

            /* Colors */
            COLORREF normalColor = RGB(128, 0, 128);   /* purple */
            COLORREF pressColor = RGB(80, 0, 80);     /* darker purple */

            /* Fill background */
            HBRUSH hBrush = CreateSolidBrush(pressed ? pressColor : normalColor);
            FillRect(dis->hDC, &dis->rcItem, hBrush);
            DeleteObject(hBrush);

            /* Draw a border */
            HPEN hPen = CreatePen(PS_SOLID, 2, pressed ? RGB(40, 0, 40) : RGB(200, 0, 200));
            HGDIOBJ oldPen = SelectObject(dis->hDC, hPen);
            HGDIOBJ oldBrush = SelectObject(dis->hDC, GetStockObject(NULL_BRUSH));
            Rectangle(dis->hDC, dis->rcItem.left, dis->rcItem.top,
                dis->rcItem.right, dis->rcItem.bottom);
            /* restore */
            SelectObject(dis->hDC, oldBrush);
            SelectObject(dis->hDC, oldPen);
            DeleteObject(hPen);

            /* Draw text (use wide API since your literals are L"...") */
            WCHAR text[256] = { 0 };
            GetWindowTextW(dis->hwndItem, text, ARRAYSIZE(text));

            SetBkMode(dis->hDC, TRANSPARENT);
            SetTextColor(dis->hDC, RGB(255, 255, 255));

            RECT rcText = dis->rcItem;
            /* simple pressed offset for "click" feel */
            if (pressed) {
                OffsetRect(&rcText, 1, 1);
            }

            DrawTextW(dis->hDC, text, -1, &rcText,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            /* Focus rectangle (optional) */
            if (focused) {
                RECT rcFocus = dis->rcItem;
                InflateRect(&rcFocus, -4, -4);
                DrawFocusRect(dis->hDC, &rcFocus);
            }

            /* Indicate we handled drawing */
            return TRUE;
        }
        break;
    }
    case WM_INITDIALOG: {
        
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

        HWND hList = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Option 1");
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Option 2");
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Option 3");
        // Optionally select the first item
        SendMessage(hCombo, CB_SETCURSEL, 0, 0);
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case IDC_BUTTON2: {
            //MessageBox(hwnd, L"Klick!", L"Info", MB_OK);
            SetDlgItemText(hwnd, IDC_STATIC1, L"Button wurde 2!");
            break;
        }
        case IDC_BUTTON1: {
            //MessageBox(hwnd, L"Klick!", L"Info", MB_OK);
            SetDlgItemText(hwnd, IDC_STATIC1, L"Button wurde 1!");
        }
                        break;
        }
        break;
    }
    case WM_CLOSE: {
        EndDialog(hwnd, 0);
        break;
    }
    default:
        return (INT_PTR)FALSE;
    }
    return (INT_PTR)TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // DialogBox gibt einen INT_PTR zurück, WinMain erwartet int. Wir casten es.
    return (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}