// list.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "list_test.h"

int testID = 0;		//���Ա��

/******************************************************************************************
* ������ɳ���Ϊn���б����п��ܰ����ظ��ڵ㣩
******************************************************************************************/
template <typename T> //Ԫ������
void randomList(List<T> & list, int n) { //��[0, 2n)��ѡ��n��ż������������б�
	Posi(T) p =
		(rand() % 2) ?
		list.insertAsLast(rand() % (T)n * 2) :
		list.insertAsFirst(rand() % (T)n * 2);
	for (int i = 1; i < n; i++)
		p = rand() % 2 ?
		list.insertSucc(p, rand() % (T)n * 2) :
		list.insertPred(p, rand() % (T)n * 2);
}

#define PRINT(x) {print(x); crc(x); checkOrder(x);}
//#define PRINT(x) {print(x);}

template <typename T>
void
testList(int testSize)
{
	printf("\n  ==== Test %2d. Genetate two lists each of size %d by random insertions\n", testID++, testSize);
	List<T> La; randomList(La, testSize); PRINT(La);
	List<T> Lb; randomList(Lb, testSize); PRINT(Lb);

	printf("\n  ==== Test %2d. Call list members by rank\n", testID++);
	for (int i = 0; i < La.size(); i++) print(La[i]); printf("\n");
	for (int i = 0; i < Lb.size(); i++) print(Lb[i]); printf("\n");

	printf("\n  ==== Test %2d. Concatenation\n", testID++);
	PRINT(La);	PRINT(Lb);

	printf("\n  ==== Call list members by rank\n", testID++);
	PRINT(La); 
}




/******************************************************************************************
* �����б�
******************************************************************************************/
int main(int argc, char* argv[]) {
	if (2 > argc) { printf("Usage: %s <size of test>\a\a\n", argv[0]); return 1; }
	srand((unsigned int) time (NULL));
	testList<int>(atoi(argv[1])); //Ԫ�����Ϳ�������������ѡ��
	return 0;
}
