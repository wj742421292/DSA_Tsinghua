/******************************************************************************************
 * Data Structures in C++
 * treat the bubble sort as the iteration of scan & swap
 * Gene.W
 * Improved the possibility to avoid the time complecity of o(n^2)
 * Copyright (c) 2018-. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T>
Rank
bubbleFast(T* A, Rank lo, Rank hi) {
    Rank last = lo; //���Ҳ������Գ�ʼ��Ϊ[lo-1, lo]
    while (++lo < hi) {
        if (A[lo - 1] > A[lo]) {
            last = lo;
            swap(A[lo - 1], A[lo]);
        }
    }
    return last;
}
//bubble
template <typename T>
bool
bubbleSlow(T* A, Rank lo, Rank hi)
{
	bool ordered = true;
	while (++lo < hi)
	{
		if (A[lo - 1]>A[lo])
		{
			ordered = false;
			swap(A[lo - 1], A[lo]);
		}
	}
	return ordered;
}
