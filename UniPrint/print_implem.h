#pragma once

//print traversable
// for Vector & List's traverse()
template <typename T>
void
UniPrint::p(T &s)
{
	printf("%s[%d]*%d:\n", typeid(s).name(), (int)&s, s.size());
	s.traverse(print);
	printf("\n");
}


//print traversable
// BinTree Node
template <typename T>
void
UniPrint::p(BinNode<T>& node) {
	p(node.data);

#if defined(DSA_LEFTHEAP)
	printf("(%-2d)", node.npl);
#elif defined(DSA_BST)
	printf("(%-2d)", node.height);
#elif defined(DSA_AVL)
	printf("(%-2d)", node.height);
#elif defined(DSA_REDBLACK)
	printf("(%-2d)", node.height);
#elif defined(DSA_SPLAY)
	printf("(%-2d)", node.height);
#endif

	printf(
		((node.lc && &node != node.lc->parent) ||
		(node.rc && &node != node.rc->parent))
		? "@" : " "
	);


#if defined(DSA_REDBLACK)
	printf(node.color == RB_BLACK ? "B" : " ");
#endif

#if defined(DSA_PQ_COMPLHEAP)

#elif defined(DSA_PQ_LEFTHEAP)
	printf(
		(node.rc && &node.npl != 1 + node.rc->npl) ||
		(node.lc && &node.npl > 1 + node.lc->npl)
		? "%%" : " "
	);
}
#elif defined(DSA_REDBLACK)
	printf(BlackHeightUpdated(node) ? " " : "!");
#else
	printf(HeightUpdated(node) ? " " : "!");
#endif


#if defined(DSA_AVL)
	if (!AvlBalanced(node)) printf("X");
	else if (0 < BalFac(node)) printf("\\");
	else if (BalFac(node) < 0) printf("/");
	else printf("-");
#elif defined(DSA_REDBLACK)
	if (!Balanced(node)) printf("X");
	else if (0 < BalFac(node)) printf("\\");
	else if (BalFac(node) < 0) printf("/");
	else printf("-");
#else

#endif

