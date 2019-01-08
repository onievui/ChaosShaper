#include "ErrorMessage.h"


constexpr void ErrorMessage(const LPCWSTR message) {
	MessageBox(NULL, message, L"", MB_OK);
}
