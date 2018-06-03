
#pragma once

#include "list.h"

template <typename T>
struct Crc{
	T &c;
	Crc(T &crc) :c(crc){}
	virtual void operator()(T &e){ c += e; }
};

template <typename T>
void 
crc(List<T> &L)	//所以元素之和
{
	T crc = 0;
	L.traverse(Crc<T>(crc));	//以crc为基本操作进行遍历
	printf("CRC =");
	print(crc);
	printf("\n");
}