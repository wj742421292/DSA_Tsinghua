#pragma once

typedef int Rank;	//��
#define Posi(T) ListNode<T>*		//�ڵ�λ��

template <typename T>
struct ListNode {	//����ڵ�ģ����(˫������)
	//member
	T data;
	Posi(T) pred;	//ͷָ��
	Posi(T) succ;	//βָ��

	//constructor
	ListNode() {}	//for the header and trailer
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		:data(e), pred(p), succ(s) {}	//default constructor

	//interface
	Posi(T) InsertAsPred(T const &e);
	Posi(T) InsertAsSucc(T const &e);
};


template <typename T>
Posi(T)
ListNode<T>::InsertAsPred(T const &e){	//assume header exists
	Posi(T) x = new ListNode(e, pred, this);	//�����½ڵ�
	pred->succ = x;	//��ǰ�ڵ��ǰ���ĺ��
	this->pred = x;	//��ǰ�ڵ��ǰ��
	return x;
}

template <typename T>
Posi(T)
ListNode<T>::InsertAsSucc(T const &e){	//assume trailer exists
	Posi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	this->succ = x;
	return x;
}
