#include "DXUtil.h"

std::wstring ConcatString(LPCTSTR & target, LPCTSTR source)
{
	std::wstring concatString(target);
	concatString = concatString + source;
	return concatString;
}

bool IsError(HRESULT hr, LPCTSTR msg)
{
	// 오류 있으면 메시지 보여주는 메시지 창
	if (hr < 0)
	{
		MessageBox(NULL, msg, TEXT("오류"), MB_OK);
		return true;
	}

	return false;
}
