#pragma once
#ifndef __CSTL_API
#define __CSTL_API
#include <Windows.h>
#define DYNCALL(x) x
#ifdef _DEBUG
#define dbg_assert(x) \
if (!(x)) {\
    char msg[512] = { 0 };\
    wsprintfA(msg, "file %s, line %d", __FILE__, __LINE__);\
    MessageBoxA(NULL, msg, __FILE__, MB_OK);\
    }\

#else
#define dbg_assert(x) if(x) { x=x;}
#endif
void* __cdecl operator new(size_t bytes);
void* __cdecl operator new[](size_t bytes);
//void* __cdecl operator new(size_t, void* where);
void  __cdecl operator delete(void *p);
void  __cdecl operator delete[](void *p);
#endif