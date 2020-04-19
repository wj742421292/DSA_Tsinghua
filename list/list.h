#pragma once

#include "listNode.h"

template < typename T>
class List {
private:
	int	_size;
	ListNodePosi(T) header;	//头哨兵
	ListNodePosi(T) trailer;	//尾哨兵

protected:
	void init();	//初始化
	int clear();	//清除所有节点
	void copyNode(ListNodePosi(T) p, int n);		//复制链表中从位置p开始的n项
	void merge(ListNodePosi(T) &, int, List<T>&, ListNodePosi(T), int);
	void mergeSort(ListNodePosi(T) &, int);	//对从位置p开始的连续n个节点归并排序
	void selectSort(ListNodePosi(T), int);
	void insertSort(ListNodePosi(T), int);

public:
	//constructor
	List() { init(); }	//dewfault constructor
	List(List<T> const &L);	//copy constructor
	List(List<T> const &L, Rank r, int n);	//复制链表第r项开始的n项
	List(ListNodePosi(T) p, int n);	//从链表位置p开始复制n项

	~List();

	//Read-Only interface
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;	//重载, 支持寻秩访问(低效)
	ListNodePosi(T) first() const { return header->succ; }	//首节点位置
	ListNodePosi(T) last() const { return trailer->pred; }	//末节点位置
	//判断位置p是否合法
	bool valid(ListNodePosi(T) p)
	{	return p && (trailer != p) && (header != p);	}
	int disordered() const;
	//无序查找
	ListNodePosi(T) find(T const &e) const
	{	return find(e, _size, trailer);	}
	//无序区间查找
	ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;
	//有序查找
	ListNodePosi(T) search(T const &e) const
	{	return search(e, _size, trailer);	}
	//有序区间查找
	ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);	//在从p开始的n个节点找出最大
	ListNodePosi(T) selectMax(){ return selectMax(header->succ, _size); }	//整体最大

	//Write-Enable
	ListNodePosi(T) insertAsFirst(T const &e);
	ListNodePosi(T) insertAsLast(T const &e);
	ListNodePosi(T) insertPred(ListNodePosi(T) p, T const &e);	//将e作为p的前驱插入
	ListNodePosi(T) insertSucc(ListNodePosi(T) p, T const &e);	//将e作为p的后继插入
	T remove(ListNodePosi(T) p);	//删除p处节点并返回
	void merge(List<T> &L) { merge(first(), size, L, L.first(), L._size); }	//???
	void sort(ListNodePosi(T) p, int n);	//区间排序
	void sort() { sort(first(), _size); }
	int deduplicate();
	int uniquify();	//有序去重
	void reverse();

	//traverse
	void traverse(void(*visit) (T&));

	template <typename VST>
	void traverse(VST &);

};	//List

#include "List_implementation.h"