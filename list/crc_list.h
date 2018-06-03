
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
crc(List<T> &L)	//����Ԫ��֮��
{
	T crc = 0;
	L.traverse(Crc<T>(crc));	//��crcΪ�����������б���
	printf("CRC =");
	print(crc);
	printf("\n");
}