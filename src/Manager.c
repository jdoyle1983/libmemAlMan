#include <memAlMan.h>
#include <Internal.h>

AllocUnit** Units = NULL;
unsigned long UnitCount;
unsigned long UnitId;

void AllocUnit_Delete(AllocUnit* u)
{
	unsigned long Idx = 0;
	unsigned long i = 0;
	for(i = 0; i < UnitCount; i++)
		if(Units[i] != NULL && Units[i]->Id == u->Id)
			Idx = i;
	if(u->Memory != NULL)
		free(u->Memory);
	free(u);
	Units[Idx] = NULL;
};

AllocUnit* AllocUnit_GetById(unsigned long Id)
{
	unsigned long i = 0;
	for(i = 0; i < UnitCount; i++)
		if(Units[i] != NULL && Units[i]->Id == Id)
			return Units[i];
	return NULL;
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
	
	return r;
};

EXPORT void memAlMan_Init()
{
	UnitCount = 0;
	UnitId = 0;
	Units = (AllocUnit**)malloc(0);
	#ifdef DEBUG
		printf("mamDebug: memAlMan_Init (System Initialized)\n");
	#endif
};

EXPORT void memAlMan_Cleanup()
{
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
};

