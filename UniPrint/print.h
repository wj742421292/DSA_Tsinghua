
#pragma once

#include <stdio.h>	//c-style
//#include "huffman/huffChar.h"	//huffman hyper-char
//#include "BinTree/BinTree.h"	//binary tree
//#include "Huffman/HuffTree.h"	//huffman tree
//#include "BST/BST.h"	//binary search tree
//#include "AVL/AVL.h"	//AVL tree
//#include "Splay/Splay.h"	//splay tree
//#include "redBlack/redBlack.h"	//red black tree
//#include "Btree/Btree.h"	//binary search tree
//#include "Entry/Entry.h"	//entry
//#include "Skiplist/Skiplist.h"	//skip list
//#include "Skiplist/Quadlist.h"	//Quad list
//#include "Hashtable/Hashtable.h"	//Hash table 
//#include "PQ_List/PQ_List.h"	//Priority Queue based on list
//#include "PQ_ComplHeap/PQ_ComplHeap.h"	//Priority Queue based on complete heap
//#include "PQ_ComplHeap/PQ_ComplHeap.h"	//Priority Queue based on complete heap
//#include "PQ_LeftHeap/PQ_LeftHeap.h"	//Priority Queue based on left heap
//#include "graph/Graph.h"
//#include "graphMatrix/GraphMatrix.h"	//Graph based on Matrix


template <typename T>
static void
print(T *x)
{
	x ? print(*x) : printf("<NULL>");
}

template <typename T>
static void
print(T &x)
{
	UniPrint::p(x);
}

template <typename T>
static void
print(const T &x)	//for stack
{
	UniPrint::p(x);
}

static void
print(char *x)
{
	printf("%s", x ? x : "<NULL>");
}

static void
print(const char *x)
{
	printf("%s", x ? x : "<NULL>");
}


class UniPrint{
public:
	static void p(int);
	static void p(float);
	static void p(double);
	static void p(char);
	//static void p(HuffChar&);	//Huffman HyperChar
	//static void p(VStatus);	//图顶点
	//static void p(EType);	//图边


	template <typename T> 	static void p(T &);	//向量链表等支持遍历的结构
	template <typename T> 	static void p(T *s)	//所有指针统一转为引用
	{
		s ? p(*s) : print("<NULL>");
	}
};

#include "print_implem.h"