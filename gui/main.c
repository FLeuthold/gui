#include <windows.h>
#include <stdio.h>
#include "resource.h"

// Die Callback Funktion
// INT_PTR CALLBACK ist der korrekte Typ für 64-Bit Windows DialogProcs
INT_PTR CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {

    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

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