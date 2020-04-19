#pragma once
//insert
template <typename T>
ListNodePosi(T)
List<T>::insertAsFirst(T const &e)
{
	_size++;
	return header->InsertAsSucc(e);	//��Ϊͷ�ڱ��ĺ�̲���, ���׽ڵ�
}

template <typename T>
ListNodePosi(T)
List<T>::insertAsLast(T const &e)
{
	_size++;
	return trailer->InsertAsPred(e);	//��Ϊβ�ڱ���ǰ������, ��β�ڵ�
}

template <typename T>
ListNodePosi(T)
List<T>::insertPred(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->InsertAsPred(e);	//��Ϊǰ������
}

template <typename T>
ListNodePosi(T)
List<T>::insertSucc(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->InsertAsSucc(e);	//��Ϊ��̲���
}

