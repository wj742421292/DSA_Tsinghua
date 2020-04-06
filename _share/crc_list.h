#pragma once

#include "..\list\list.h"

template <typename T>
void crc(List<T>& L) {	//添加列表元素总和
	T crc = 0;
	L.traverse(Crc<T>(crc));	//以crc为基本操作进行遍历
	printf("CRC=");
	print(crc);
	printf("\n");
}
