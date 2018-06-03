
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
checkOrder(List<T> &L)	//判断链表是否整体有序
{
	int unsorted = 0;
	L.traverse(CheckOrder<T>(unsorted, L.first()->data));	//遍历
	if (unsorted > 0)
		printf("Unsorted with %d adjacent disordered pair(s)\n", unsorted);
	else
		printf("Sorted\n");
}