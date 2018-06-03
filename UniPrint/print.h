
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
	static void p(T &);	//���������֧�ֱ����Ľṹ
	template <typename T>
	static void p(T *s)	//����ָ��ͳһתΪ����
	{
		s ? p(*s) : print("<NULL>");
	}
};

#include "print_implem.h"