#pragma once

template <typename T>
void
reverse3() {
	if (_size < 2) return;
	ListNodePosi(T) p;
	ListNodePosi(T) q;
	for (p = header, q = p->succ; p != trailer; p = q, q = p->succ)
		p->pred = q;
	trailer->pred = NULL;
	for (p = header, q = p->succ; p != trailer; p = q, q = p->pred)
		q->succ = p;
	header->succ = NULL;
	swap(header, trailer);
}

template <typename T>
void
reverse1() {
	ListNodePosi(T) p=header;
	ListNodePosi(T) q=trailer;
	for (int i = 1; i < _size; i += 2)
		swap((p = p->succ)->data, (q = q->pred)->data);
}

template <typename T>
void
reverse2() {
	if (_size < 2) return;
	for (ListNodePosi(T) p = header; p; p = p->pred)
		swap(p->pred, p->succ);
	swap(header, trailer);
}
