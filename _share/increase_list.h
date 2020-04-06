#pragma once

template <typename T>
void increase(List<T>& L) {
	L.traverse(Increase<T>());
}
