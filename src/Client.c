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
	AllocUnit* u = AllocUnit_New();
	u->s = Size;
	u->m = malloc(u->s);
	#ifdef DEBUG
		printf("mamDebug: mamAlloc (Id: %ld - Size: %ld)\n", u->i, u->s);
	#endif
	return (unsigned long)u->i;
};

EXPORT void mamCopy(void* mam, unsigned long Offset, void* Src, unsigned long Size)
{
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		memcpy(u->m + Offset, Src, Size);
		#ifdef DEBUG
			printf("mamDebug: mamCopy (Id: %ld) - SUCCESS\n", u->i);
		#endif
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamCopy (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
};

EXPORT void* mamRetain(void* mam)
{
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		u->r++;
		#ifdef DEBUG
			printf("mamDebug: mamRetain (Id: %ld - RefCount: %ld) - SUCCESS\n", u->i, u->r);
		#endif
		return u->i;
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
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		u->r--;
		if(u->r <= 0)
		{
			#ifdef DEBUG
				printf("mamDebug: mamRelease (Id: %ld - RefCount: %ld) - SUCCESS (Deleted)\n", u->i, u->r);
			#endif
			AllocUnit_Delete(u);
		}
		else
		{
			#ifdef DEBUG
				printf("mamDebug: mamRelease (Id: %ld - RefCount: %ld) - SUCCESS\n", u->i, u->r);
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
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		u->m = realloc(u->m, NewSize);
		u->s = NewSize;
		
		#ifdef DEBUG
			printf("mamDebug: mamRealloc (Id: %ld - NewSize: %ld) - SUCCESS\n", u->i, NewSize);
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
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		AllocUnit* un = AllocUnit_New();
		un->s = u->s;
		un->m = malloc(un->s);
		memcpy(un->m, u->m, u->s);
		
		#ifdef DEBUG
			printf("mamDebug: mamDuplicate (Id: %ld - New Id: %ld) - SUCCESS\n", u->i, un->i);
		#endif
		
		return un->i;
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
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		return u->m;
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
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		return u->s;
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRawSize (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
	return 0;
};
