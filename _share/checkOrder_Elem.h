#pragma once

template <typename T>
struct CheckOrder {	//function object: 判断一个T类对象是否局部有序
	T pred; 
	int& u;
	CheckOrder(int& unsorted, T& first) :pred(first), u(unsorted) {}
	virtual void operator()(T& e) { if (pred > e) u++; pred = e; }
};
