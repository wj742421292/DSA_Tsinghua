
#pragma once

#include <stdio.h>

template <typename T>
static void
print(T *x)
{
	x ? print(*x) : printf("<NULL>");
}

template <typename T>
static void
print(T &x)
{
	UniPrint::p(x);
}

template <typename T>
static void
print(const T &x)	//for stack
{
	UniPrint::p(x);
}

static void
print(char *x)
{
	printf("%s", x ? x : "<NULL>");
}

static void
print(const char *x)
{
	printf("%s", x ? x : "<NULL>");
}


class UniPrint{
public:
	static void p(int);
	static void p(float);
	static void p(double);
	static void p(char);
	//static void p(int);

	template <typename T>
	static void p(T &);	//向量链表等支持遍历的结构
	template <typename T>
	static void p(T *s)	//所有指针统一转为引用
	{
		s ? p(*s) : print("<NULL>");
	}
};

#include "print_implem.h"