#ifndef __MEMALMAN_H__
#define __MEMALMAN_H__

#include <stdio.h>
#include <malloc.h>
#include <memory.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WINDLL
#define EXPORT __declspec( dllexport )
#else
#define EXPORT
#endif


EXPORT void memAlMan_Init(void(*mamLock)(), void(*mamUnLock)());
EXPORT void memAlMan_Cleanup();
EXPORT void memAlMan_ThreadLock();
EXPORT void memAlMan_ThreadUnLock();

EXPORT void* mamAlloc(unsigned long Size);
EXPORT void mamCopy(void* mam, unsigned long Offset, void* Src, unsigned long Size);
EXPORT void* mamRetain(void* mam);
EXPORT void mamRelease(void* mam);
EXPORT void mamRealloc(void* mam, unsigned long NewSize);
EXPORT void* mamDuplicate(void* mam);
EXPORT void* mamRaw(void* mam);

#define mamStrLen(m) (strlen(mamRaw(m)))
#define mamStrCpy(m, s) (mamCopy(m, 0, s, (unsigned long)strlen(s) + 1))
#define mamCast(m, t) ((t)mamRaw(m))

#ifdef __cplusplus
}
#endif

#endif