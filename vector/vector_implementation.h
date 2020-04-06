#pragma once


#include "../_share/release.h"
#include "../_share/util.h"

//read_only interface begin

//disordered
template < typename T>
int
Vector<T>::disordered() const
{
	//返回逆序对个数
	int n = 0;
	for (int i = 1; i < _size; ++i)
	{
		if (_elem[i - 1] > _elem[i])
			n++;
	}
	return n;	//向量有序当且仅当n = 0
}

//find
template <typename T>
Rank
Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
	while ((lo<hi--) && (e != _elem[hi]));
	return hi;
}


//search
template<typename T>
Rank
Vector<T>::search(T const &e, Rank lo, Rank hi) const
{
	return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

//read_only interface end

//read&write

template <typename T>
T& 
Vector<T>::operator[] (Rank r) const
{
	return _elem[r];	//assert 0<r<_size
}

template <typename T>
Vector<T> &
Vector<T>::operator= (Vector<T> const &V)
{
	if (_elem) delete[] _elem;	//delete the old
	copyFrom(V._elem, 0, V.size());
	return *this;	//??
}

template <typename T>
T
Vector<T>::remove(Rank r)	//delete the element of rank r, 0<=r<=size
{
	T e = _elem[r];	//backup the deleted element
	remove(r, r + 1);
	return e;
}


template <typename T>
int 
Vector<T>::remove(Rank lo, Rank hi)	//remove Interval
{
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();	//shrink if necessary
	return hi - lo;
}

template <typename T>
Rank
Vector<T>::insert(Rank r, T const& e)	//insert e at rank r, assert 0<=r<=size
{
	expand();	//expand if necessary
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r;
}

template <typename T>
void
Vector<T>::sort(Rank lo, Rank hi)	//vector interval sort
{
	switch (rand() % 5) {
	case 1: bubbleSort(lo, hi); break;
	case 2: selectSort(lo, hi); break;
	case 3: mergeSort(lo, hi); break;
	case 4: heapSort(lo, hi); break;
	case 5: quickSort(lo, hi); break;
	}
}

template <typename T>
void
Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
		swap(V[i], V[rand() % i]);	//swap V[i-1] and V[0,i)
}

template <typename T>
int
Vector<T>::deduplicate()	//delete the duped element of unsorted vector
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;

}

template <typename T>
int
Vector<T>::uniquify()	//delete the duped element of sorted vector
{
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i;
	shrink();
	return j - i;
}

//bubble
template <typename T>
bool
Vector<T>::bubble(Rank lo, Rank hi)
{
	bool ordered = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1]>_elem[lo])
		{
			ordered = false;
			swap(_elem[lo - 1], elem[lo]);
		}
	}
	return ordered;
}

//bubblesort
template <typename T>
void
Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (lo < (hi = bubble(lo, hi)));
}


//selection sort	o(n^2)
template <typename T>
void
Vector<T>::selectSort(Rank lo, Rank hi)
{
	whille(lo < --hi)
	{
		swap(_elem[max(lo, hi)], _elem[hi]);
	}
}


template <typename T>
Rank
Vector<T>::max(Rank lo, Rank hi)
{
	Rank max = hi;
	while (lo < hi--)
	{
		if (_elem[hi] > _elem[max])
			max = hi;
	}

	return max;
}


//vector_constructor_by_copying
//copyFrom

template <typename T>
void
Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)	//copy the elem of A[lo, hi) to _elem[lo,hi)
		_elem[_size++] = A[lo++];
}


//expand
template <typename T>
void
expand()
{
	if (_size < _capacity) return;	//there is no need to expand
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T *oldelem = _elem;
	_elem = new T[_capacity << 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];

	delete[] oldelem;
}

//shirink
//以25%为界
template <typename T>
void
Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1) return;	//不小于默认容量
	if (_size << 2 > _capacity)	return;	//规模超过25%, 不缩小
	T *oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i<_size; i++)
		_elem[i] = oldElem[i];

	delete[] oldElem;
}

template <typename T>
void
Vector<T>::traverse(void (*visit) (T&))	//fuction pointer
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T> template <typename VST>	//function object
void
Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}