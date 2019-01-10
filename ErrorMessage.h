#pragma once
#include <Windows.h>

#define ErrorMessage(message) ErrorMessageA(message)

inline void ErrorMessageA(LPCSTR message) {
	MessageBoxA(NULL, message, "", MB_OK);
}

