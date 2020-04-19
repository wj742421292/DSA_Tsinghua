#pragma once

typedef int Rank;	//秩
#define ListNodePosi(T) ListNode<T>*		//节点位置

template <typename T>
struct ListNode {	//链表节点模板类(双向链表)
	//member
	T data;
	ListNodePosi(T) pred;	//头指针
	ListNodePosi(T) succ;	//尾指针

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
	ListNodePosi(T) x = new ListNode(e, pred, this);	//创建新节点
	pred->succ = x;	//当前节点的前驱的后继
	this->pred = x;	//当前节点的前驱
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
