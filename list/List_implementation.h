#pragma once

#include "../_share/release.h"
#include "../_share/util.h"
#include "List_insert.h"
#include "List_reverse.h"
#include "../_share/crc_list.h"
#include "../_share/checkOrder_list.h"
#include "../_share/increase_list.h"
#include "listNode.h"

//initialize
template <typename T>
void
List<T>::init()
{
	header = new ListNode < T > ;	//创建头哨兵
	trailer = new ListNode < T > ;//创建尾哨兵
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;	//规模
}

//clear
template <typename T>
int
List<T>::clear()
{
	int oldSize = _size;
	while (_size > 0)
	{
		remove(header->succ);	//反复删除首节点
	}
	return oldSize;
}

// copy
template <typename T>
void
List<T>::copyNode(ListNodePosi(T) p, int n)
{
	init();	//创建头尾哨兵并初始化
	while (n--)
	{
		insertAsLast(p->data);	//作为末节点插入
		p = p->succ;	//取下一节点
	}
}

//有序链表归并, 当前链表自p起的n个元素 与 链表L自q的m个元素归并
template <typename T>
void
List<T>::merge(ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m)
{
	//assert this.valid(p)&& rank(p)+n<=size && this.sorted(p,n) p合法且其后n个节点均在链表中, 且有序
	//assert L.valid(q) && rank(q)+m<=L._size && L.sorted(q,m)

	ListNodePosi(T) pp = p->pred;	//前驱或header
	while (m>0)	//q仍在区间中
		if ((n > 0) && p->data <= q->data)
		{
			if (q == (p = p->succ))	//p归入合并后的链表, 并替换为其直接后继
				break;
			n--;
		}
		else //p已出界或 q数值小
		{
			insertPred(p, L.remove((q = q->succ)->pred));	//q转移至p之前
			m--;
		}
	p = pp->succ;	//确定的归并后的新起点

}

//有序链表归并, 当前链表自p起的n个元素 与 链表L自q的m个元素归并
template <typename T>
void
List<T>::mergeSort(ListNodePosi(T) &p, int n)
{
	//assert valid(p) && rank(p) + n <=_size
	//printf("\tMerge Sort [%3d]\n", n);
	if (n < 2) return;
	int m = n >> 1;	//以中点为界
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)
		q = q->succ;	//均分链表
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);	//归并
	
}//排序后, p依然指向新起点

//选择排序, 对起始于p的n个元素排序
template <typename T>
void
List<T>::selectSort(ListNodePosi(T) p, int n)
{
	//assert valid(p) && rank(p)+n <= _size
	//printf("Selection Sort.. \n");
	ListNodePosi(T) head = p->head;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->succ;
	while (1 < n) {
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertPred(tail, remove(max));
		//swp(tail->pred->data, selectMax(head->succ.n)->data);
		tail = tail->pred;
		n--;
	}
}

//插入排序, 对起始于p的n个元素排序
template <typename T>
void
List<T>::insertSort(ListNodePosi(T) p, int n)
{
	//assert valid(p) && rank(p)+n <= _size
	//printf("Insertion Sort.. \n");
	for (int r = 0; r < n; r++) {
		insertPred(search(p->data, r, p), p->data);	//search the proper position to insert
		p = p->succ;
		remove(p->pred);
	}
}

/***********************************************************************
***********************                          *********************** 
***********************     构造析构函数         ***********************
***********************                          ***********************	
************************************************************************/

template <typename T>
List<T>::List(List<T> const &L)	//整体复制
{
	copyNode(L.first(), _size);
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNode(p, n);
}

template <typename T>
List<T>::List(List<T> const &L, Rank r, int n)
{
	//copyNode(L[r], n);
	ListNodePosi(T) p = L.first();
	while (0 < r--)	p = p->succ;
	copyNode(p, n);
}

template <typename T>
List<T>::~List()
{
	//清空链表, 释放头尾哨兵
	clear();
	delete header;
	delete trailer;
}


/***********************************************************************
***********************                          *********************** 
***********************     可读可写接口         ***********************
***********************                          ***********************	
************************************************************************/


//remove
template <typename T>
T
List<T>::remove(ListNodePosi(T) p)
{	//删除有效节点p, 并返回其值
	T e = p->data;	//备份该节点数据, 假设类型T可直接赋值
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T>
void
List<T>::sort(ListNodePosi(T) p, int n)	//区间排序
{
	switch (rand() % 3)
	{
	case 1:
		insertSort(p, n) break;
	case 2:
		selectSort(p, n) break;
	default:
		mergeSort(p, n); break;
	}
}

template <typename T>
int
List<T>::deduplicate()
{
	//if (_size < 2)	return 0;
	//int oldSize = _size;
	//ListNodePosi(T) p = header;
	//Rank r = 0;
	//while (trailer != (p = p->succ))
	//{
	//	ListNodePosi(T) q = find(p->data, r, p);	//在p的r个前驱中查找重复
	//	q ? remove(q) : r++;
	//}
	int oldSize = _size;
	ListNodePosi(T) p = first();
	for (Rank r = 0; p != trailer; p = p->succ)	//O(n)
		if (ListNodePosi(T) q = find(p->data, r, p))
			remove(q);
		else r++;
	return oldSize - _size;
}

template <typename T>
int
List<T>::uniquify()
{
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first();	//p为各区段起点, q为其后继
	ListNodePosi(T) q;
	while (trailer != (q = p->succ))
	{
		if (p->data != q->data) p = q;	//反复比较紧邻节点对
		else remove(q);
	}
	return oldSize - _size;
}

template <typename T>
void
List<T>::reverse() {
	switch (rand() % 3) {
	case 1:
		reverse1(); break;
	case 2:
		reverse2(); break;
	default:
		reverse3(); break;
	}
}


/***********************************************************************
***********************                          *********************** 
***********************     只读函数接口         ***********************
***********************                          ***********************	
************************************************************************/

//重载下标操作
template <typename T>
T&
List<T>::operator[] (Rank r) const
{
	//assert 0<= r <= _size
	ListNodePosi(T) p = first();
	while (r-- > 0)
		p = p->succ;
	return p->data;
}

//判断是否有序
template <typename T>
int
List<T>::disordered() const
{
	//统计相邻逆序对个数
	int n = 0;
	ListNode<T> *p = first();
	for (int i = 0; i < _size - 1; p = p->succ, i++)
		if (p->data > p->succ->data) n++;
	return n;
}

//无序区间查找
template <typename T>
ListNodePosi(T)
List<T>::find(T const &e, int n, ListNodePosi(T) p) const
{
	//在无序链表的节点p的n个前驱中查找等于e的最后者
	while (n--)
	{
		if ((p = p->pred)->data == e)	//从右至左
			return p;
	}
	return NULL;
}


//有序区间查找
template <typename T>
ListNodePosi(T)
List<T>::search(T const &e, int n, ListNodePosi(T) p) const
{
	//在有序链表p节点的n个前驱中, 查找不大于e的最后者
	printf("searching for ");	print(e); printf(" :\n");
	//while (n-- >= 0)
	//{
	//	if ((p = p->pred)->data <= e) break;
	//}
	do {
		p = p->pred; n--;
		printf("-->%4d", p->data);
	} while ((-1 < n) && (e < p->data));
	return p;
}	//失败时, 返回左边界的前驱, 调用者需通过valid()判断成功与否

template <typename T> //从起始于位置p的n个元素中选出最大者
ListNodePosi(T) 
List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodeListNodePosi(T) max = p; //最大者暂定为首节点p
	for (ListNodePosi(T) cur = p; 1 < n; n--)
		if (!lt((cur = cur - succ)->data, max->data))
			max = cur;
	return max; //返回最大节点位置
}

/***********************************************************************
***********************                          *********************** 
***********************             遍历         ***********************
***********************                          ***********************	
************************************************************************/

template <typename T>
void
List<T>::traverse(void(*visit)(T&))	//函数指针
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T> template <typename VST>	//元素类型, 操作器
void
List<T>::traverse(VST &visit)	//函数对象
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}
