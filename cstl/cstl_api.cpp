#include "cstl_api.h"


void* __cdecl operator new(size_t bytes)
{
    void* p = DYNCALL(HeapAlloc(DYNCALL(GetProcessHeap()), HEAP_ZERO_MEMORY, bytes));

    if (NULL == p)
    {
        DBG_ASSERT(FALSE);
    }

    return p;
}
void* __cdecl operator new[](size_t bytes)
{
    void* p = DYNCALL(HeapAlloc(DYNCALL(GetProcessHeap()), HEAP_ZERO_MEMORY, bytes));

    if (NULL == p)
    {
        DBG_ASSERT(FALSE);
    }

    return p;
}
void __cdecl operator delete(void *p)
{
    if (!DYNCALL(HeapFree(DYNCALL(GetProcessHeap()), 0, p)))
    {
        DBG_ASSERT(FALSE);
    }
}

void __cdecl operator delete[](void *p)
{
    if (!DYNCALL(HeapFree(DYNCALL(GetProcessHeap()), 0, p)))
    {
        DBG_ASSERT(FALSE);
    }
}

void* _cdecl operator new(size_t, void* where)
{
    return where;
}