
#pragma once

#include "list.h"

template <typename T>
struct Increase{
	virtual void operator()(T &e){ e++; }
};

template <typename T>
void
increase(List<T> &L)
{
	L.traverse(Increase<T>());
}
