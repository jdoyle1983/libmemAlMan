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

AllocUnit** Units = NULL;
unsigned long UnitCount;
unsigned long UnitId;

void(*mamThreadLock)() = NULL;
void(*mamThreadUnLock)() = NULL;

void mamLockStub()
{
}

void mamUnLockStub()
{
}

void memAlMan_Init();

void AllocUnit_Delete(AllocUnit* u)
{
	if(Units == NULL)
		memAlMan_Init();
		
	mamThreadLock();
	unsigned long Idx = 0;
	unsigned long i = 0;
	for(i = 0; i < UnitCount; i++)
		if(Units[i] != NULL && Units[i]->i == u->i)
			Idx = i;
	if(u->m != NULL)
		free(u->m);
	free(u);
	Units[Idx] = NULL;
	mamThreadUnLock();
};

AllocUnit* AllocUnit_GetById(unsigned long Id)
{
	if(Units == NULL)
		memAlMan_Init();
		
	AllocUnit* r = NULL;
	
	mamThreadLock();
	
	unsigned long i = 0;
	for(i = 0; i < UnitCount && r == NULL; i++)
		if(Units[i] != NULL && Units[i]->i == Id)
			r = Units[i];

	mamThreadUnLock();
	
	return r;
};

AllocUnit* AllocUnit_New()
{
	if(Units == NULL)
		memAlMan_Init();
		
	AllocUnit* r = NULL;
	r = (AllocUnit*)malloc(sizeof(AllocUnit));
	r->r = 1;
	r->s = 0;
	r->m = NULL;
	r->i = UnitId;
	UnitId++;
	
	mamThreadLock();
	
	bool found = false;
	unsigned i = 0;
	for(i = 0; i < UnitCount; i++)
	{
		if(Units[i] == NULL)
		{
			found = true;
			Units[i] = r;
		}
	}
	
	if(found == false)
	{
		UnitCount++;
		Units = (AllocUnit**)realloc(Units, sizeof(AllocUnit*) * UnitCount);
		Units[UnitCount - 1] = r;
	}
	
	mamThreadUnLock();
	
	return r;
};

EXPORT void memAlMan_EnableThreads(void(*mamLock)(), void(*mamUnLock)())
{
	if(Units == NULL)
		memAlMan_Init();
		
	if(mamLock == NULL)
		mamThreadLock = &mamLockStub;
	else
		mamThreadLock = mamLock;
		
	if(mamUnLock == NULL)
		mamThreadUnLock = &mamUnLockStub;
	else
		mamThreadUnLock = mamUnLock;
};

void memAlMan_Init()
{	
	mamThreadLock = &mamLockStub;
	mamThreadUnLock = &mamUnLockStub;
	
	UnitCount = 0;
	UnitId = 0;
	Units = (AllocUnit**)malloc(0);
	#ifdef DEBUG
		printf("mamDebug: memAlMan_Init (System Initialized)\n");
	#endif
};

EXPORT void memAlMan_Maintain()
{
	mamThreadLock();
	
	unsigned long largeId = 0;
	unsigned long usedCount = 0;
	unsigned long i = 0;
	for(i = 0; i < UnitCount; i++)
	{
		if(Units[i] != NULL)
			usedCount++;
			
		if(Units[i] != NULL && Units[i]->i >= largeId)
			largeId = Units[i]->i + 1;
	}
	UnitId = largeId;
	if(usedCount != UnitCount)
	{
		AllocUnit** newList = malloc(sizeof(AllocUnit*) * usedCount);
		unsigned long cId = 0;
		for(i = 0; i < UnitCount; i++)
		{
			if(Units[i] != NULL)
			{
				newList[cId] = Units[i];
				cId++;
			}
		}
		free(Units);
		Units = newList;
		UnitCount = usedCount;
	}
	
	mamThreadUnLock();
};

EXPORT void memAlMan_Cleanup()
{
	mamThreadLock();
	
	unsigned long i = 0;
	for(i = 0; i < UnitCount; i++)
		if(Units[i] != NULL)
			AllocUnit_Delete(Units[i]);
	free(Units);
	UnitCount = 0;
	UnitId = 0;
	Units = NULL;
	
	#ifdef DEBUG
		printf("mamDebug: memAlMan_Cleanup (System Cleaned Up)\n");
	#endif
	
	mamThreadUnLock();
};

EXPORT void memAlMan_ThreadLock()
{
	mamThreadLock();
};

EXPORT void memAlMan_ThreadUnLock()
{
	mamThreadUnLock();
};

