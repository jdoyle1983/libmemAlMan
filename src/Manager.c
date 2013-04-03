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

void AllocUnit_Delete(AllocUnit* u)
{
	mamThreadLock();
	unsigned long Idx = 0;
	unsigned long i = 0;
	for(i = 0; i < UnitCount; i++)
		if(Units[i] != NULL && Units[i]->Id == u->Id)
			Idx = i;
	if(u->Memory != NULL)
		free(u->Memory);
	free(u);
	Units[Idx] = NULL;
	mamThreadUnLock();
};

AllocUnit* AllocUnit_GetById(unsigned long Id)
{
	AllocUnit* r = NULL;
	
	mamThreadLock();
	
	unsigned long i = 0;
	for(i = 0; i < UnitCount && r == NULL; i++)
		if(Units[i] != NULL && Units[i]->Id == Id)
			r = Units[i];

	mamThreadUnLock();
	
	return r;
};

AllocUnit* AllocUnit_New()
{
	AllocUnit* r = NULL;
	r = (AllocUnit*)malloc(sizeof(AllocUnit));
	r->RefCount = 1;
	r->Size = 0;
	r->Memory = NULL;
	r->Id = UnitId;
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

EXPORT void memAlMan_Init(void(*mamLock)(), void(*mamUnLock)())
{
	if(mamLock == NULL)
		mamThreadLock = &mamLockStub;
	else
		mamThreadLock = mamLock;
		
	if(mamUnLock == NULL)
		mamThreadUnLock = &mamUnLockStub;
	else
		mamThreadUnLock = mamUnLock;
		
	UnitCount = 0;
	UnitId = 0;
	Units = (AllocUnit**)malloc(0);
	#ifdef DEBUG
		printf("mamDebug: memAlMan_Init (System Initialized)\n");
	#endif
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

