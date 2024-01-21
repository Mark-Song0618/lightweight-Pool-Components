#pragma once

#include "memPool.h"

class HttpConn {
public:
	HttpConn(MemPool<HttpConn>* memPool);

	void* operator new (size_t, MemPool<HttpConn>*);

	void operator delete(void*);

	void run();

private:
	MemPool<HttpConn>* _memPool;
};