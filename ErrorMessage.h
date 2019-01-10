#pragma once


#define ERROR_TYPE_MESSAGEBOX
//#define ERROR_TYPE_ASSERT

#define ErrorMessage

#ifdef ERROR_TYPE_MESSAGEBOX
	#include <Windows.h>
	#undef ErrorMessage
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
	#undef ErrorMessage
	#define ErrorMessage(message) assert(!message)
#endif


