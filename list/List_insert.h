#pragma once
//insert
template <typename T>
ListNodePosi(T)
List<T>::insertAsFirst(T const &e)
{
	_size++;
	return header->InsertAsSucc(e);	//作为头哨兵的后继插入, 即首节点
}

template <typename T>
ListNodePosi(T)
List<T>::insertAsLast(T const &e)
{
	_size++;
	return trailer->InsertAsPred(e);	//作为尾哨兵的前驱插入, 即尾节点
}

template <typename T>
ListNodePosi(T)
List<T>::insertPred(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->InsertAsPred(e);	//作为前驱插入
}

template <typename T>
ListNodePosi(T)
List<T>::insertSucc(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->InsertAsSucc(e);	//作为后继插入
}

