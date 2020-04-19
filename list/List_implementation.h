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
	header = new ListNode < T > ;	//����ͷ�ڱ�
	trailer = new ListNode < T > ;//����β�ڱ�
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;	//��ģ
}

//clear
template <typename T>
int
List<T>::clear()
{
	int oldSize = _size;
	while (_size > 0)
	{
		remove(header->succ);	//����ɾ���׽ڵ�
	}
	return oldSize;
}

// copy
template <typename T>
void
List<T>::copyNode(ListNodePosi(T) p, int n)
{
	init();	//����ͷβ�ڱ�����ʼ��
	while (n--)
	{
		insertAsLast(p->data);	//��Ϊĩ�ڵ����
		p = p->succ;	//ȡ��һ�ڵ�
	}
}

//��������鲢, ��ǰ������p���n��Ԫ�� �� ����L��q��m��Ԫ�ع鲢
template <typename T>
void
List<T>::merge(ListNodePosi(T) &p, int n, List<T> &L, ListNodePosi(T) q, int m)
{
	//assert this.valid(p)&& rank(p)+n<=size && this.sorted(p,n) p�Ϸ������n���ڵ����������, ������
	//assert L.valid(q) && rank(q)+m<=L._size && L.sorted(q,m)

	ListNodePosi(T) pp = p->pred;	//ǰ����header
	while (m>0)	//q����������
		if ((n > 0) && p->data <= q->data)
		{
			if (q == (p = p->succ))	//p����ϲ��������, ���滻Ϊ��ֱ�Ӻ��
				break;
			n--;
		}
		else //p�ѳ���� q��ֵС
		{
			insertPred(p, L.remove((q = q->succ)->pred));	//qת����p֮ǰ
			m--;
		}
	p = pp->succ;	//ȷ���Ĺ鲢��������

}

//��������鲢, ��ǰ������p���n��Ԫ�� �� ����L��q��m��Ԫ�ع鲢
template <typename T>
void
List<T>::mergeSort(ListNodePosi(T) &p, int n)
{
	//assert valid(p) && rank(p) + n <=_size
	//printf("\tMerge Sort [%3d]\n", n);
	if (n < 2) return;
	int m = n >> 1;	//���е�Ϊ��
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)
		q = q->succ;	//��������
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);	//�鲢
	
}//�����, p��Ȼָ�������

//ѡ������, ����ʼ��p��n��Ԫ������
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

//��������, ����ʼ��p��n��Ԫ������
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
***********************     ������������         ***********************
***********************                          ***********************	
************************************************************************/

template <typename T>
List<T>::List(List<T> const &L)	//���帴��
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
	//�������, �ͷ�ͷβ�ڱ�
	clear();
	delete header;
	delete trailer;
}


/***********************************************************************
***********************                          *********************** 
***********************     �ɶ���д�ӿ�         ***********************
***********************                          ***********************	
************************************************************************/


//remove
template <typename T>
T
List<T>::remove(ListNodePosi(T) p)
{	//ɾ����Ч�ڵ�p, ��������ֵ
	T e = p->data;	//���ݸýڵ�����, ��������T��ֱ�Ӹ�ֵ
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T>
void
List<T>::sort(ListNodePosi(T) p, int n)	//��������
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
	//	ListNodePosi(T) q = find(p->data, r, p);	//��p��r��ǰ���в����ظ�
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
	ListNodePosi(T) p = first();	//pΪ���������, qΪ����
	ListNodePosi(T) q;
	while (trailer != (q = p->succ))
	{
		if (p->data != q->data) p = q;	//�����ȽϽ��ڽڵ��
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
***********************     ֻ�������ӿ�         ***********************
***********************                          ***********************	
************************************************************************/

//�����±����
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

//�ж��Ƿ�����
template <typename T>
int
List<T>::disordered() const
{
	//ͳ����������Ը���
	int n = 0;
	ListNode<T> *p = first();
	for (int i = 0; i < _size - 1; p = p->succ, i++)
		if (p->data > p->succ->data) n++;
	return n;
}

//�����������
template <typename T>
ListNodePosi(T)
List<T>::find(T const &e, int n, ListNodePosi(T) p) const
{
	//����������Ľڵ�p��n��ǰ���в��ҵ���e�������
	while (n--)
	{
		if ((p = p->pred)->data == e)	//��������
			return p;
	}
	return NULL;
}


//�����������
template <typename T>
ListNodePosi(T)
List<T>::search(T const &e, int n, ListNodePosi(T) p) const
{
	//����������p�ڵ��n��ǰ����, ���Ҳ�����e�������
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
}	//ʧ��ʱ, ������߽��ǰ��, ��������ͨ��valid()�жϳɹ����

template <typename T> //����ʼ��λ��p��n��Ԫ����ѡ�������
ListNodePosi(T) 
List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodeListNodePosi(T) max = p; //������ݶ�Ϊ�׽ڵ�p
	for (ListNodePosi(T) cur = p; 1 < n; n--)
		if (!lt((cur = cur - succ)->data, max->data))
			max = cur;
	return max; //�������ڵ�λ��
}

/***********************************************************************
***********************                          *********************** 
***********************             ����         ***********************
***********************                          ***********************	
************************************************************************/

template <typename T>
void
List<T>::traverse(void(*visit)(T&))	//����ָ��
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T> template <typename VST>	//Ԫ������, ������
void
List<T>::traverse(VST &visit)	//��������
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}
