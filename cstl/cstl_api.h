#pragma once
#ifndef __CSTL_API
#define __CSTL_API
#include <Windows.h>
#define DYNCALL(x) x
#define DBG_ASSERT(x) x
void* __cdecl operator new(size_t bytes);
void* __cdecl operator new[](size_t bytes);

void* _cdecl operator new(size_t, void* where);
void  __cdecl operator delete(void *p);
void  __cdecl operator delete[](void *p);
#endif