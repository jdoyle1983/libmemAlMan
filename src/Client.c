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

#include <memAlMan.h>
#include <Internal.h>

EXPORT void* mamAlloc(unsigned long Size)
{
	AllocUnit* Unit = AllocUnit_New();
	
	Unit->Size = Size;
	Unit->Memory = malloc(Unit->Size);
	
	#ifdef DEBUG
		printf("mamDebug: mamAlloc (Id: %ld - Size: %ld)\n", Unit->Id, Unit->Size);
	#endif
	
	return (void*)Unit->Id;
};

EXPORT void mamCopy(void* mam, unsigned long Offset, void* Src, unsigned long Size)
{
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		memcpy(Unit->Memory + Offset, Src, Size);
		#ifdef DEBUG
			printf("mamDebug: mamCopy (Id: %ld) - SUCCESS\n", Unit->Id);
		#endif
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamCopy (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
};

EXPORT void* mamInherit(void* Src, unsigned long Size)
{
	AllocUnit* Unit = AllocUnit_New();
	
	Unit->Size = Size;
	Unit->Memory = Src;
	
	#ifdef DEBUG
		printf("mamDebug: mamInherit (Id: %ld - Size: %ld)\n", Unit->Id, Unit->Size);
	#endif
	
	return (void*)Unit->Id;
};

EXPORT void* mamRetain(void* mam)
{
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		Unit->RefCount++;
		#ifdef DEBUG
			printf("mamDebug: mamRetain (Id: %ld - RefCount: %ld) - SUCCESS\n", Unit->Id, Unit->RefCount);
		#endif
		return (void*)Unit->Id;
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRetain (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
	return NULL;
};

EXPORT void mamRelease(void* mam)
{
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		Unit->RefCount--;
		if(Unit->RefCount <= 0)
		{
			#ifdef DEBUG
				printf("mamDebug: mamRelease (Id: %ld - RefCount: %ld) - SUCCESS (Deleted)\n", Unit->Id, Unit->RefCount);
			#endif
			AllocUnit_Delete(Unit);
		}
		else
		{
			#ifdef DEBUG
				printf("mamDebug: mamRelease (Id: %ld - RefCount: %ld) - SUCCESS\n", Unit->Id, Unit->RefCount);
			#endif
		}
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRelease (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
};

EXPORT void mamRealloc(void* mam, unsigned long NewSize)
{
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		Unit->Memory = realloc(Unit->Memory, NewSize);
		Unit->Size = NewSize;
		
		#ifdef DEBUG
			printf("mamDebug: mamRealloc (Id: %ld - NewSize: %ld) - SUCCESS\n", Unit->Id, NewSize);
		#endif
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRealloc (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
};

EXPORT void* mamDuplicate(void* mam)
{
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		AllocUnit* NewUnit = AllocUnit_New();
		NewUnit->Size = Unit->Size;
		NewUnit->Memory = malloc(NewUnit->Size);
		memcpy(NewUnit->Memory, Unit->Memory, Unit->Size);
		
		#ifdef DEBUG
			printf("mamDebug: mamDuplicate (Id: %ld - New Id: %ld) - SUCCESS\n", Unit->Id, NewUnit->Id);
		#endif
		
		return (void*)NewUnit->Id;
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamDuplicate (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
	return NULL;
};

EXPORT void* mamRaw(void* mam)
{	
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		return Unit->Memory;
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRaw (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
	return NULL;
};

EXPORT unsigned long mamRawSize(void* mam)
{
	AllocUnit* Unit = AllocUnit_GetById((unsigned long)mam);
	if(Unit != NULL)
	{
		return Unit->Size;
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRawSize (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
	return 0;
};
