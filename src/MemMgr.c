#include <stdlib.h>
#include <string.h>
#include "MemMgr.h"

void * MEM_MALLOC (size_t memSize)
{
    void *memRet;

    if ((memRet = malloc (memSize)) != NULL)
      {
       	memset (memRet, 0, memSize);
      }
    return memRet;
}
