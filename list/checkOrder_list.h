
#pragma once

#include "list.h"

template <typename T>
struct CheckOrder{
	T pred;
	int &u;
	CheckOrder(int &unsorted, T &first) :u(unsorted), pred(first){};
	virtual void operator() (T &e){ if (pred > e) u++; pred = e; }
};


template <typename T>
void
checkOrder(List<T> &L)	//�ж������Ƿ���������
{
	int unsorted = 0;
	L.traverse(CheckOrder<T>(unsorted, L.first()->data));	//����
	if (unsorted > 0)
		printf("Unsorted with %d adjacent disordered pair(s)\n", unsorted);
	else
		printf("Sorted\n");
}