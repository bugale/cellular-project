#include "CommonHeader.h"

unsigned char xdata MemoryHandler_mempool[0x1];

void Memory_Set()
{
	init_mempool(&MemoryHandler_mempool, sizeof(MemoryHandler_mempool));
}
void_ptr Memory_malloc(short size)
{
	return (void_ptr)malloc(size);
}
void Memory_free(void_ptr address)
{
	free(address);
}