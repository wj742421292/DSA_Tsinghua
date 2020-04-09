#pragma once

template <typename T>
void
UniPrint::p(T &s)
{
	printf("%s[%d]*%d:\n", typeid(s).name(), (int)&s, s.size());
	s.traverse(print);
	printf("\n");
}