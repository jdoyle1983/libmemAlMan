/*

    libmemAlMan
    Copyright (C) 2013 Jason Doyle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact Information:

    Original Author: Jason Doyle (jdoyle1983@gmail.com)
	
*/

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

EXPORT void memAlMan_EnableThreads(void(*mamLock)(), void(*mamUnLock)());
EXPORT void memAlMan_Cleanup();
EXPORT void memAlMan_Maintain();
EXPORT void memAlMan_ThreadLock();
EXPORT void memAlMan_ThreadUnLock();

EXPORT void* mamAlloc(unsigned long Size);
EXPORT void mamCopy(void* mam, unsigned long Offset, void* Src, unsigned long Size);
EXPORT void* mamInherit(void* Src, unsigned long Size);
EXPORT void* mamRetain(void* mam);
EXPORT void mamRelease(void* mam);
EXPORT void mamRealloc(void* mam, unsigned long NewSize);
EXPORT void* mamDuplicate(void* mam);
EXPORT void* mamRaw(void* mam);
EXPORT unsigned long mamRawSize(void* mam);

//String Helper
#define mamStrLen(m) (strlen(mamRaw(m)))
#define mamStrCpy(m, s) (mamCopy(m, 0, s, (unsigned long)strlen(s) + 1))

//File IO Helper
#define mamFread(m, s, c, f) (fread(mamRaw(m), s, c, f))
#define mamFwrite(m, s, c, f) (fwrite(mamRaw(m), s, c, f))

//General Helper
#define mamCast(m, t) ((t)mamRaw(m))


#ifdef __cplusplus
}
#endif

#endif