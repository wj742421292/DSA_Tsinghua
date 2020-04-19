#pragma once

typedef int Rank;	//��
#define ListNodePosi(T) ListNode<T>*		//�ڵ�λ��

template <typename T>
struct ListNode {	//����ڵ�ģ����(˫������)
	//member
	T data;
	ListNodePosi(T) pred;	//ͷָ��
	ListNodePosi(T) succ;	//βָ��

	//constructor
	ListNode() {}	//for the header and trailer
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		:data(e), pred(p), succ(s) {}	//default constructor

	//interface
	ListNodePosi(T) InsertAsPred(T const &e);
	ListNodePosi(T) InsertAsSucc(T const &e);
};


template <typename T>
ListNodePosi(T)
ListNode<T>::InsertAsPred(T const &e){	//assume header exists
	ListNodePosi(T) x = new ListNode(e, pred, this);	//�����½ڵ�
	pred->succ = x;	//��ǰ�ڵ��ǰ���ĺ��
	this->pred = x;	//��ǰ�ڵ��ǰ��
	return x;
}

template <typename T>
ListNodePosi(T)
ListNode<T>::InsertAsSucc(T const &e){	//assume trailer exists
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	this->succ = x;
	return x;
}
