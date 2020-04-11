#pragma once

template <typename T>
Rank
partitionA(T* A, Rank lo, Rank hi) {
	swap(A[lo], A[lo + rand() % (hi - lo)]);
	hi--;
	T pivot = A[lo];
	while (lo < hi)
	{
		while ((lo < hi) && (pivot <= A[hi]))
			hi--;
		A[lo] = A[hi];
		while ((lo < hi) && (A[lo] <= pivot))
			lo++;
		A[hi] = A[lo];
	}	//assert: lo == hi
	A[lo] = pivot;
	return lo;
}

template <typename T>
Rank
partitionA1(T* A, Rank lo, Rank hi) {
	swap(A[lo], A[lo + rand() % (hi - lo)]);
	hi--;
	T pivot = A[lo];
	while (lo < hi)
	{
		while ((lo < hi) && (pivot <= A[hi]))
			hi--;
		A[lo] = A[hi];
		while ((lo < hi) && (A[lo] <= pivot))
			lo++;
		A[hi] = A[lo];
	}	//assert: lo == hi
	A[lo] = pivot;
	return lo;
}


template <typename T>
Rank
partitionB(T* A, Rank lo, Rank hi) {
	swap(A[lo], A[lo + rand() % (hi - lo)]);
	hi--;
	T pivot = A[lo];
	while (lo < hi)
	{
		while (lo < hi)
			if (pivot < A[hi])
				hi--;
			else
			{
				A[lo++] = A[hi]; break;
			}
		while (lo < hi)
			if (A[lo] < pivot)
				lo++;
			else
			{
				A[hi--] = A[lo]; break;
			}
	}	//assert: lo == hi
	A[lo] = pivot;
	return lo;
}

template <typename T>
Rank
partitionB1(T* A, Rank lo, Rank hi) {
	swap(A[lo], A[lo + rand() % (hi - lo)]);
	hi--;
	T pivot = A[lo];
	while (lo < hi)
	{
		while ((lo < hi) && (pivot < A[hi]))
			hi--;
		if(lo<hi)
			A[lo++] = A[hi];
		while ((lo < hi) && (A[lo] < pivot))
			lo++;
		if(lo<hi)
			A[hi--] = A[lo];
	}	//assert: lo == hi
	A[lo] = pivot;
	return lo;
}

template <typename T>
Rank
partitionC(T* A, Rank lo, Rank hi) {
	int mi = lo;
	return mi;
}
