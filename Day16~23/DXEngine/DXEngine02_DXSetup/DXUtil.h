#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")		//프로젝트 설정에서 링커->입력->종속성에 추가한것과 같음
#pragma comment(lib, "d3dcompiler.lib")

namespace Memory
{
	template <class T> void SafeRelease(T& t)
	{
		if (t)
		{
			t->Release();
			t = NULL;
		}
	}

	template <class T> void SafeDelete(T& t)
	{
		if (t)
		{
			delete t;
			t = NULL;
		}
	}

	// 배열 메모리 해제용.
	template <class T> void SafeDeleteArray(T& t)
	{
		if (t)
		{
			delete[] t;
			t = NULL;
		}
	}
}