#pragma once
#include <Windows.h>

inline void ErrorMessage(const LPCWSTR message) {
	MessageBox(NULL, message, L"", MB_OK);
}