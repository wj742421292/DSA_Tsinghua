#pragma once

template <typename T>
void permute(Vector<T>& V) {
	for (int i = V.size(); i > 0; i--)	//随机置乱向量
		swap(V[i - 1], V[rand() % i]);	//随机交换
}
