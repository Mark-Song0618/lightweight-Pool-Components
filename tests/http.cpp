#include "http.h"
#include <iostream>

HttpConn::HttpConn(MemPool<HttpConn>* memPool)
	: _memPool(memPool) {}

void*
HttpConn::operator new (size_t size, MemPool<HttpConn>* pool)
{
	//std::cout << "alloc from memPool" << std::endl;
	return pool->alloc();
}

void
HttpConn::operator delete(void* ptr)
{
	HttpConn* con = (HttpConn*)ptr;
	if (con->_memPool) {
		//	std::cout << "free in memPool" << std::endl;
		con->_memPool->free(con);
		con->~HttpConn();
	}
	else {
		::operator delete(con);
	}
}

void
HttpConn::run()
{
	std::cout << "Hello, Mark" << std::endl;
}
