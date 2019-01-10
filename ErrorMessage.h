#pragma once


#define ERROR_TYPE_MESSAGEBOX
//#define ERROR_TYPE_ASSERT

#ifdef ERROR_TYPE_MESSAGEBOX
#include <Windows.h>
#define ErrorMessage(message) ErrorMessageBoxA(message)
inline void ErrorMessageBoxA(LPCSTR message) {
	MessageBoxA(NULL, message, "", MB_OK);
}
#endif

#ifdef ERROR_TYPE_ASSERT
	#ifndef ERROR_TYPE_MESSAGEBOX
	#include <Windows.h>
	#endif
#include <cassert>
#define ErrorMessage(message) assert(!message)
#endif


