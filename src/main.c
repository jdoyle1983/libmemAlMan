#include <memAlMan.h>

void Lock()
{
}

void UnLock()
{
}

int main(int argc, char* argv[])
{
	int i = 0;
	
	void* setA = mamAlloc(1000);
	for(i = 0; i < 10; i++)
		setA = mamRetain(setA);
	void* setB = mamAlloc(65536);
	for(i = 0;i  < 10; i++)
		setB = mamRetain(setB);
	mamRealloc(setA, 3500);	
	void* setC = mamDuplicate(setB);
	char* src = (char*)malloc(sizeof(char) * 100);
	strcpy(src, "Test 1");
	mamStrCpy(setC, src);
	void* setD = mamDuplicate(setC);
	mamStrCpy(setD, "Test Number 2");
	
	printf("Val1 (%d): %s\n", mamStrLen(setC), mamCast(setC, char*));
	printf("Val2 (%d): %s\n", mamStrLen(setD), mamCast(setD, char*));
	
	void* set1 = mamAlloc(1000);
	void* set2 = mamRetain(set1);
	void* set3 = mamRetain(set2);
	void* set4 = mamAlloc(200);
	void* set5 = mamRetain(set4);
	
	for(i = 0; i < 11; i++)
	{
		mamRelease(setA);
		mamRelease(setB);
	}
	
	mamRelease(set5);
	mamRelease(set4);
	mamRelease(set3);
	mamRelease(set2);
	mamRelease(set1);
	mamRelease(setC);
	mamRelease(setD);

	memAlMan_Cleanup();
	
	free(src);
	
	return 0;
};