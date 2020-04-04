/******************************************************************************************
 * Data Structures in C++
 * treat the bubble sort as the iteration of scan & swap
 * Gene.W
 * Vector
 * Copyright (c) 2018-. All rights reserved.
 ******************************************************************************************/

#pragma once

typedef	int Rank;	//秩
#define	DEFAULT_CAPACITY	3	//向量默认初始容量

template	<typename T>
class Vector
{
protected:
	Rank _size; int _capacity;	T *_elem;	//秩,容量和数据区
	void copyFrom (T const *A, Rank lo, Rank hi);	//copy the A[lo,hi)
	void expand();	//空间不足时扩容
	void shrink();	//填装因子过小时压缩
	bool bubble();	//scan & swap
	void bubblesort();	//
	Rank max(Rank lo, Rank hi);	//select the max from[lo,hi)
	void selectSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mid, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	Rank Partition(Rank lo, Rank hi);
	void quickSort(Rank lo, Rank hi);
	void heapSort(Rank lo, Rank hi);

public:
	//construct
	Vector(int c=DEFAULT_CAPACITY,int s=0, T v=0)		//capacity, scale, inital value	
	{_elem = new T[_capacity = c]; for(_size=0; _size<s; _elem[_size++]=v) ; }	//s<=c
	Vector(T const *A, Rank n){ copyFrom(A, 0, n);}	//copy the entire array
	Vector(T const *A, Rank lo, Rank hi){copyFrom(A, lo, hi); }
	Vector(Vector<T> const &T){ copyFrom(T._elem, 0, T._size); }	//copy the vector
	Vector(Vector<T> const &T, Rank lo, Rank hi){copyFrom(T._size, lo, hi); }

	//destruct
	~Vector() { delete [] _elem;}

	//read_only interface
	Rank size() const {return _size;}
	bool empty() const {return !_size;}
	int disordered() const;
	Rank find(T const &e) const { return find(e, 0, _size);}	//find e in disordered vector
	Rank find(T const &e, Rank lo, Rank hi) const ;
	Rank search(T const &e) const { return (0>=_size)?-1:search(e, 0, _size); }	//search e in a ordered vector
	Rank search(T const &e, Rank lo, Rank high) const;

	//write and read interface
	T& operator[] (Rank r) const;
	Vector<T> & operator= (Vector<T> const &);
	T remove(Rank r);
	int remove(Rank lo, Rank hi);	//delete the elements between [lo, hi)
	Rank insert(Rank r, T const &e);
	Rank insert(T const &e) { return insert(_size, e); }	//insert the last position default
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); }
	int deduplicate();		//dupe for disordered vector
	int uniquify();		//dupe for ordered vector

	//traverse
	void traverse( void(*)(T&));		//pointer to function , read_only or modify partially
	template <typename VST>
	void traverse (VST &);		//function object, modify globally
//private:

};

#include "vector_implementation.h"