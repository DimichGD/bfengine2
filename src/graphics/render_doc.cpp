#include "render_doc.hpp"
#include <windows.h>

BF_BEGIN_NAMESPACE

bool IsRenderDocAttached()
{
	HMODULE module_handle = GetModuleHandle(L"renderdoc.dll");
	return module_handle != nullptr;
}

BF_END_NAMESPACE
