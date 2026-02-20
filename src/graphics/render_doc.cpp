#include "render_doc.hpp"
#include <windows.h>

BF_BEGIN_NAMESPACE

bool IsRenderDocAttached()
{
	HMODULE module = GetModuleHandle(L"renderdoc.dll");
	return module != nullptr;
}

BF_END_NAMESPACE
