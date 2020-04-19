#pragma once

#include "listNode.h"

template < typename T>
class List {
private:
	int	_size;
	ListNodePosi(T) header;	//ͷ�ڱ�
	ListNodePosi(T) trailer;	//β�ڱ�

protected:
	void init();	//��ʼ��
	int clear();	//������нڵ�
	void copyNode(ListNodePosi(T) p, int n);		//���������д�λ��p��ʼ��n��
	void merge(ListNodePosi(T) &, int, List<T>&, ListNodePosi(T), int);
	void mergeSort(ListNodePosi(T) &, int);	//�Դ�λ��p��ʼ������n���ڵ�鲢����
	void selectSort(ListNodePosi(T), int);
	void insertSort(ListNodePosi(T), int);

public:
	//constructor
	List() { init(); }	//dewfault constructor
	List(List<T> const &L);	//copy constructor
	List(List<T> const &L, Rank r, int n);	//���������r�ʼ��n��
	List(ListNodePosi(T) p, int n);	//������λ��p��ʼ����n��

	~List();

	//Read-Only interface
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;	//����, ֧��Ѱ�ȷ���(��Ч)
	ListNodePosi(T) first() const { return header->succ; }	//�׽ڵ�λ��
	ListNodePosi(T) last() const { return trailer->pred; }	//ĩ�ڵ�λ��
	//�ж�λ��p�Ƿ�Ϸ�
	bool valid(ListNodePosi(T) p)
	{	return p && (trailer != p) && (header != p);	}
	int disordered() const;
	//�������
	ListNodePosi(T) find(T const &e) const
	{	return find(e, _size, trailer);	}
	//�����������
	ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;
	//�������
	ListNodePosi(T) search(T const &e) const
	{	return search(e, _size, trailer);	}
	//�����������
	ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);	//�ڴ�p��ʼ��n���ڵ��ҳ����
	ListNodePosi(T) selectMax(){ return selectMax(header->succ, _size); }	//�������

	//Write-Enable
	ListNodePosi(T) insertAsFirst(T const &e);
	ListNodePosi(T) insertAsLast(T const &e);
	ListNodePosi(T) insertPred(ListNodePosi(T) p, T const &e);	//��e��Ϊp��ǰ������
	ListNodePosi(T) insertSucc(ListNodePosi(T) p, T const &e);	//��e��Ϊp�ĺ�̲���
	T remove(ListNodePosi(T) p);	//ɾ��p���ڵ㲢����
	void merge(List<T> &L) { merge(first(), size, L, L.first(), L._size); }	//???
	void sort(ListNodePosi(T) p, int n);	//��������
	void sort() { sort(first(), _size); }
	int deduplicate();
	int uniquify();	//����ȥ��
	void reverse();

	//traverse
	void traverse(void(*visit) (T&));

	template <typename VST>
	void traverse(VST &);

};	//List

#include "List_implementation.h"