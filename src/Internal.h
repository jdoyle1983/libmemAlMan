#ifndef __INTERNAL_H__
#define __INTERNAL_H__

#define bool short
#define true 1
#define false 0

typedef struct
{
	unsigned long Id;
	unsigned long RefCount;
	unsigned long Size;
	void* Memory;
} AllocUnit;

void AllocUnit_Delete(AllocUnit* u);
AllocUnit* AllocUnit_GetById(unsigned long Id);
AllocUnit* AllocUnit_New();

#endif