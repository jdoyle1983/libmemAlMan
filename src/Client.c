#include <memAlMan.h>
#include <Internal.h>

EXPORT void* mamAlloc(unsigned long Size)
{
	AllocUnit* u = AllocUnit_New();
	u->Size = Size;
	u->Memory = malloc(u->Size);
	#ifdef DEBUG
		printf("mamDebug: mamAlloc (Id: %ld - Size: %ld)\n", u->Id, u->Size);
	#endif
	return (unsigned long)u->Id;
};

EXPORT void mamCopy(void* mam, unsigned long Offset, void* Src, unsigned long Size)
{
	AllocUnit* u = AllocUnit_GetById((unsigned long)mam);
	if(u != NULL)
	{
		memcpy(u->Memory + Offset, Src, Size);
		#ifdef DEBUG
			printf("mamDebug: mamCopy (Id: %ld) - SUCCESS\n", u->Id);
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
		u->RefCount++;
		#ifdef DEBUG
			printf("mamDebug: mamRetain (Id: %ld - RefCount: %ld) - SUCCESS\n", u->Id, u->RefCount);
		#endif
		return u->Id;
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
		u->RefCount--;
		if(u->RefCount <= 0)
		{
			#ifdef DEBUG
				printf("mamDebug: mamRelease (Id: %ld - RefCount: %ld) - SUCCESS (Deleted)\n", u->Id, u->RefCount);
			#endif
			AllocUnit_Delete(u);
		}
		else
		{
			#ifdef DEBUG
				printf("mamDebug: mamRelease (Id: %ld - RefCount: %ld) - SUCCESS\n", u->Id, u->RefCount);
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
		u->Memory = realloc(u->Memory, NewSize);
		u->Size = NewSize;
		
		#ifdef DEBUG
			printf("mamDebug: mamRealloc (Id: %ld - NewSize: %ld) - SUCCESS\n", u->Id, NewSize);
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
		un->Size = u->Size;
		un->Memory = malloc(un->Size);
		memcpy(un->Memory, u->Memory, u->Size);
		
		#ifdef DEBUG
			printf("mamDebug: mamDuplicate (Id: %ld - New Id: %ld) - SUCCESS\n", u->Id, un->Id);
		#endif
		
		return un->Id;
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
		return u->Memory;
	}
	else
	{
		#ifdef DEBUG
			printf("mamDebug: mamRow (Id: %ld) - FAILED (Not Found)\n", (unsigned long)mam);
		#endif
	}
	return NULL;
};
