
#pragma once

#include <typeinfo.h>

template <typename T>
void
UniPrint::p(T &s)
{
	printf("%s[%d]*%d:\n", typeid(s).name(), &s, s.size());
	s.traverse(print);
	printf("\n");
}