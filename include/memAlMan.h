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

/*
	Enable system wide thread locking / unlocking mechanism.
	Your application must implement the locking system, and
	libmemAlMan will call it as necessary.
	mamLock: The method that will be called when attempting to get a lock
	mamUnLock: The method that will be called when releasing a lock
*/
EXPORT void memAlMan_EnableThreads(void(*mamLock)(), void(*mamUnLock)());

/*
	Free up all system memory, this should be called on application
	exit.
*/
EXPORT void memAlMan_Cleanup();

/*
	Clean up internal memAlMan data, this should be called occasionally
	in a long running application to prevent memory usage creep.
*/
EXPORT void memAlMan_Maintain();

/*
	Call the system implemented locking mechanism
*/
EXPORT void memAlMan_ThreadLock();

/*
	Call the system implemented unlocking mechanism
*/
EXPORT void memAlMan_ThreadUnLock();

/*
	Allocate a new block of managed system memory
	Size: The size of the memory block in bytes
	Returns: A managed memory block
*/
EXPORT void* mamAlloc(unsigned long Size);

/*
	Copy raw data into a managed memory block
	mam: Managed memory to copy data into
	Offset: Offset in the source data to start copying
	Src: Src raw memory buffer
	Size: Size of the data to copy
*/
EXPORT void mamCopy(void* mam, unsigned long Offset, void* Src, unsigned long Size);

/*
	Bring an existing raw memory block under Memory management.
	Src: The raw memory block to inherit
	Size: The size of the raw memory block
	Returns: A managed memory block that is now in control of the raw memory buffer
*/
EXPORT void* mamInherit(void* Src, unsigned long Size);

/*
	Grab a reference to a managed memory block, increments the ref counter
	mam: A managed memory block
	Returns: A reference to the managed memory block
*/
EXPORT void* mamRetain(void* mam);

/*
	Free a reference to a managed memory block, decrementing the ref counter.
	If the ref counter < 1 than the raw memory is freed.
	mam: A managed memory block
*/
EXPORT void mamRelease(void* mam);

/*
	Resize a managed memory block
	mam: Existing managed memory block
	NewSize: The new size of the managed memory block
*/
EXPORT void mamRealloc(void* mam, unsigned long NewSize);

/*
	Copy a managed memory block, including the raw memory into
	a new managed memory block
	mam: Existing managed memory block
	Returns: A new copy of the original managed memory block
*/
EXPORT void* mamDuplicate(void* mam);

/*
	Get a pointer to the raw memory buffer that a managed
	memory block is controlling.
	mam: Existing managed memory block
	Returns: Raw memory buffer
*/
EXPORT void* mamRaw(void* mam);

/*
	Get the actual raw size of a managed memory block
	mam: Existing managed memory block
	Returns: The raw memory size
*/
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