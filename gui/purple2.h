#pragma once
#include <windows.h>
#include <windowsx.h>   // <-- REQUIRED for GET_X_LPARAM / GET_Y_LPARAM
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "msimg32.lib")
#include "resource.h"

LRESULT CALLBACK PurpleButtonSubclassProc(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam,
    UINT_PTR id, DWORD_PTR ref);
