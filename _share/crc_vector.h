#pragma once

#include "..\vector\vector.h"

template <typename T>
void crc(Vector<T>& V) {
	T crc = 0;
	V.traverse(Crc<T>(crc));	//以crc为基本操作遍历

	printf("CRC=");
	print(crc);
	printf("\n");
}
