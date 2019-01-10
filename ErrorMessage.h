#pragma once


#define ERROR_TYPE_MESSAGEBOX
//#define ERROR_TYPE_ASSERT

#define ErrorMessage

#ifdef ERROR_TYPE_MESSAGEBOX
	#ifndef _WINUSER_
		#include <Windows.h>
	#endif
	#undef ErrorMessage
	#define ErrorMessage(message) ErrorMessageBoxA(message)
	inline void ErrorMessageBoxA(LPCSTR message) {
		MessageBoxA(NULL, message, "", MB_OK);
	}
#endif

#ifdef ERROR_TYPE_ASSERT
	#include <cassert>
	#undef ErrorMessage
	#define ErrorMessage(message) assert(!message)
#endif

