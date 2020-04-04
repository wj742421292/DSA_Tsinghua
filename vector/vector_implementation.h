#pragma once



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
Vector<T>::find(T const &e, Rank lo, Rank hi)
{
	while ((lo<hi--) && (e != _elem[hi]));
	return hi;
}


//search
template<typename T>
Rank
Vector<T>::search(T const &e, Rank lo, Rank hi)
{
	;	//to be done
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
Vecctor<T>::remove(Rank r)
{
	remove
}


template <typename T>
int 
Vector<T>::remove(Rank lo, Rank hi)
{
	while ()
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
Vector<T>::bubblesort()
{
	while (!bubble(lo, hi--);)
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