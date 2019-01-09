#pragma once
#include <Windows.h>

#define ErrorMessage(message) ErrorMessageA(message)

inline void ErrorMessageA(const LPCWSTR message) {
	MessageBox(NULL, message, L"", MB_OK);
}

