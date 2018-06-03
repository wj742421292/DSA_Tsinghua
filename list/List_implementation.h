#pragma once

#include "crc_list.h"
#include "checkOrder_list.h"
#include "increase_list.h"
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
List<T>::copyNode(Posi(T) p, int n)
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
List<T>::merge(Posi(T) &p, int n, List<T> &L, Posi(T) q, int m)
{
	//assert this.valid(p)&& rank(p)+n<=size && this.sorted(p,n) p�Ϸ������n���ڵ����������, ������
	//assert L.valid(q) && rank(q)+m<=L._size && L.sorted(q,m)

	Posi(T) pp = p->pred;	//ǰ����header
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
List<T>::mergeSort(Posi(T) &p, int n)
{
	//assert valid(p) && rank(p) + n <=_size
	printf("\tMerge Sort [%3d]\n", n);
	if (n < 2) return;
	int m = n >> 1;	//���е�Ϊ��
	Posi(T) q = p;
	for (int i = 0; i < m; i++)
		q = q->succ;	//��������
	mergeSort(p, m);
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);	//�鲢
	
}//�����, p��Ȼָ�������

//ѡ������, ����ʼ��p��n��Ԫ������
template <typename T>
void
List<T>::selectSort(Posi(T) p, int n)
{
	//assert valid(p) && rank(p)+n <= _size
	printf("Selection Sort.. \n");
}

//��������, ����ʼ��p��n��Ԫ������
template <typename T>
void
List<T>::insertSort(Posi(T) p, int n)
{
	//assert valid(p) && rank(p)+n <= _size
	printf("Insertion Sort.. \n");
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
List<T>::List(Posi(T) p, int n)
{
	copyNode(p, n);
}

template <typename T>
List<T>::List(List<T> const &L, int r, int n)
{
	copyNode(L[r], n);
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
List<T>::remove(Posi(T) p)
{	//ɾ����Ч�ڵ�p, ��������ֵ
	T e = p->data;	//���ݸýڵ�����, ��������T��ֱ�Ӹ�ֵ
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

//insert
template <typename T>
Posi(T)
List<T>::insertAsFirst(T const &e)
{
	_size++;
	return header->InsertAsSucc(e);	//��Ϊͷ�ڱ��ĺ�̲���, ���׽ڵ�
}

template <typename T>
Posi(T)
List<T>::insertAsLast(T const &e)
{
	_size++;
	return trailer->InsertAsPred(e);	//��Ϊβ�ڱ���ǰ������, ��β�ڵ�
}

template <typename T>
Posi(T)
List<T>::insertPred(Posi(T) p, T const &e)
{
	_size++;
	return p->InsertAsPred(e);	//��Ϊǰ������
}

template <typename T>
Posi(T)
List<T>::insertSucc(Posi(T) p, T const &e)
{
	_size++;
	return p->InsertAsSucc(e);	//��Ϊ��̲���
}

template <typename T>
void
List<T>::sort(Posi(T) p, int n)	//��������
{
	/*switch (rand() % 3)
	{
	case 1:
		insertSort(p, n) break;
	case 2:
		selectSort(p, n) break;
	default:
		mergeSort(p, n); break;
	}*/
	mergeSort(p, n);
}

template <typename T>
int
List<T>::deduplicate()
{
	if (_size < 2)	return 0;
	int oldSize = _size;
	Posi(T) p = header;
	Rank r = 0;
	while (trailer != (p = p->succ))
	{
		Posi(T) q = find(p->data, r, p);	//��p��r��ǰ���в����ظ�
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template <typename T>
int
List<T>::uniquify()
{
	if (_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first();	//pΪ���������, qΪ����
	Posi(T) q;
	while (trailer != (q = p->succ))
	{
		if (p->data != q->data) p = q;	//�����ȽϽ��ڽڵ��
		else remove(q);
	}
	return oldSize - _size;
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
	Posi(T) p = first();
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
Posi(T)
List<T>::find(T const &e, int n, Posi(T) p) const
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
Posi(T)
List<T>::search(T const &e, int n, Posi(T)) const
{
	//����������p�ڵ��n��ǰ����, ���Ҳ�����e�������
	printf("searching for ");
	while (n-- >= 0)
	{
		if ((p = p->pred)->data <= e) break;
	}
	return p;
}	//ʧ��ʱ, ������߽��ǰ��, ��������ͨ��valid()�жϳɹ����

template <typename T> //����ʼ��λ��p��n��Ԫ����ѡ�������
Posi(T) 
List<T>::selectMax(Posi(T) p, int n) const{
	ListNodePosi(T) max = p; //������ݶ�Ϊ�׽ڵ�p
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
	for (Posi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T> template <typename VST>	//Ԫ������, ������
void
List<T>::traverse(VST &visit)	//��������
{
	for (Posi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}
