#pragma once

#include "listNode.h"

template < typename T>
class List {
private:
	int	_size;
	Posi(T) header;	//ͷ�ڱ�
	Posi(T) trailer;	//β�ڱ�

protected:
	void init();	//��ʼ��
	int clear();	//������нڵ�
	void copyNode(Posi(T), int);		//���������д�λ��p��ʼ��n��
	void merge(Posi(T) &, int, List<T>&, Posi(T), int);
	void mergeSort(Posi(T) &, int);	//�Դ�λ��p��ʼ������n���ڵ�鲢����
	void selectSort(Posi(T), int);
	void insertSort(Posi(T), int);

public:
	//constructor
	List() { init(); }	//dewfault constructor
	List(List<T> const &L);	//copy constructor
	List(List<T> const &L, Rank r, int n);	//���������r�ʼ��n��
	List(Posi(T) p, int n);	//������λ��p��ʼ����n��

	~List();

	//Read-Only interface
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;	//����, ֧��Ѱ�ȷ���(��Ч)
	Posi(T) first() const { return header->succ; }	//�׽ڵ�λ��
	Posi(T) last() const { return trailer->pred; }	//ĩ�ڵ�λ��
	//�ж�λ��p�Ƿ�Ϸ�
	bool valid(Posi(T) p)
	{	return p && (trailer != p) && (header != p);	}
	int disordered() const;
	//�������
	Posi(T) find(T const &e) const
	{	return find(e, _size, trailer);	}
	//�����������
	Posi(T) find(T const &e, int n, Posi(T) p) const;
	//�������
	Posi(T) search(T const &e) const
	{	return search(e, _size, trailer);	}
	//�����������
	Posi(T) search(T const &e, int n, Posi(T) p) const;
	Posi(T) selectMax(Posi(T) p, int n) const;	//�ڴ�p��ʼ��n���ڵ��ҳ����
	Posi(T) selectMax() const { return selectMax(header->succ, _size); }	//�������

	//Write-Enable
	Posi(T) insertAsFirst(T const &e);
	Posi(T) insertAsLast(T const &e);
	Posi(T) insertPred(Posi(T) p, T const &e);	//��e��Ϊp��ǰ������
	Posi(T) insertSucc(Posi(T) p, T const &e);	//��e��Ϊp�ĺ�̲���
	T remove(Posi(T) p);	//ɾ��p���ڵ㲢����
	void merge(List<T> &L) { merge(first(), size, L, L.first(), L._size); }	//???
	void sort(Posi(T) p, int n);	//��������
	void sort() { sort(first(), _size); }
	int deduplicate();
	int uniquify();	//����ȥ��
	void reverse();

	//traverse
	void traverse(void(*) (T&));

	template <typename VST>
	void traverse(VST &);

};	//List

#include "List_implementation.h"