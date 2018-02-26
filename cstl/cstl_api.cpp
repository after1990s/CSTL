#include "cstl_api.h"


void* __cdecl operator new(size_t bytes)
{
    void* p = DYNCALL(HeapAlloc(DYNCALL(GetProcessHeap()), HEAP_ZERO_MEMORY, bytes));

    if (NULL == p)
    {
        dbg_assert(FALSE);
    }

    return p;
}
void* __cdecl operator new[](size_t bytes)
{
    void* p = DYNCALL(HeapAlloc(DYNCALL(GetProcessHeap()), HEAP_ZERO_MEMORY, bytes));

    if (NULL == p)
    {
        dbg_assert(FALSE);
    }

    return p;
}
void __cdecl operator delete(void *p)
{
    if (!DYNCALL(HeapFree(DYNCALL(GetProcessHeap()), 0, p)))
    {
        dbg_assert(FALSE);
    }
}

void __cdecl operator delete[](void *p)
{
    if (!DYNCALL(HeapFree(DYNCALL(GetProcessHeap()), 0, p)))
    {
        dbg_assert(FALSE);
    }
}
/*
void* _cdecl operator new(size_t, void* where)
{
    return where;
}*/
//
//#ifdef _DEBUG
//inline void __cdecl dbg_assert(bool x)
//{
//    if (!x) {
//        char msg[512] = { 0 };
//        wsprintfA(msg, "file %s, line %d", __FILE__, __LINE__);
//        MessageBoxA(NULL, msg, __FILE__, MB_OK);
//    }
//}
//#else
//
//#endif