#define MemoryHandler
#include "CommonHeader.h"

void Memory_Set();
void_ptr Memory_malloc(short size);
void Memory_free(void_ptr address);