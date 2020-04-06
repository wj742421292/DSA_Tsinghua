#pragma once

template <typename T>
void double(Vector<T>& V) {
	V.traverse(Double<T>());
}
