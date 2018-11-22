#ifndef __MEM_MGR_H
#define __MEM_MGR_H

void *MEM_MALLOC (size_t memSize);
#define MEM_XMALLOC(X) malloc(X)

#define MEM_FREE(X) do{\
	if(X) \
		free(X);\
	X=NULL;\
}while(0)

#endif /* __MEM_MGR_H */
