#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include <commctrl.h>

// Die Callback Funktion
// INT_PTR CALLBACK ist der korrekte Typ für 64-Bit Windows DialogProcs
INT_PTR CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {

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

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BUTTON1: {
            //char buffer[256];
            //char message[300];
            MessageBox(hwnd, L"Klick!", L"Info", MB_OK);
            // Liest Text aus dem Edit-Feld
            //GetDlgItemText(hwnd, IDC_INPUT_TEXT, buffer, 256);
            //message = "testable";
            /*if (strlen(buffer) > 0) {
                sprintf_s(message, 300, "Hallo, %s!", buffer);
            }
            else {
                sprintf_s(message, 300, "Hallo, Fremder!");
            }*/

            // Setzt Text im Label
            SetDlgItemText(hwnd, IDC_STATIC1, L"Button wurde geklickt!");
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
    // DialogBox gibt einen INT_PTR zurück, WinMain erwartet int. Wir casten es.
    return (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}