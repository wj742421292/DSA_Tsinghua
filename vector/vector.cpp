// vector.cpp : 定义控制台应用程序的入口点。
//

#include "vector_test.h"

int testID = 0;

/*************************************************************************
 * 测试: 无序向量的查找
 *************************************************************************/
template <typename T>
void TestFind(Vector<T>& V, int n) {

	for (int i = 0; i < V.size(); i++)
	{
		T e = V[i];
		print(e);
		Rank r = V.find(e);
		if (r < 0)	printf(" : not found until rank V[%d] <> %d", r, e);
		else printf(" : found at rank V[%d] = %d", r, e);
		printf("\n");
	}

	for (int i = 0; i < V.size(); i++)
	{
		T a = (0 < i) ? V[i - 1] : -INT_MAX / 2;
		T b = (i < V.size()) ? V[i ] : INT_MAX / 2;
		T e = (a + b) / 2;
		print(e);
		Rank r = V.find(e);
		if (r < 0)	printf(" : not found until rank V[%d] <> %d", r, e);
		else printf(" : found at rank V[%d] = %d", r, V[r]);
		printf("\n");
	}
}

/*************************************************************************
 * 测试: 有序向量的查找(binSearch or fibSearch)
 *************************************************************************/
template <typename T>
void TestSearch(Vector<T>& V) {
	for(int i=0; i<V.size(); i++)
	{
		T e = V[i];
		printf("Looking for");
		print(e);
		printf("in ...\n");
		print(V);
		Rank r = V.search(e);
		if (V[r] == e)	printf(" found at rank V[%d] = %d", r, V[r]);
		else printf(" found at rank V[%d] = %d <> %d", r, V[r], e);
		printf("\n\n");
	}

	for(int i=0; i<V.size(); i++)
	{
		T a = (0 < i) ? V[i - 1] : -INTMAX / 2;
		T a = (i < V.size()) ? V[i] : INTMAX / 2;
		T e = (a+b)/2;
		printf("Looking for");
		print(e);
		printf("in ...\n");
		print(V);
		Rank r = V.search(e);
		printf("V[%3d] =", r);
		(r < 0) ? print("-INF") : print(V[r]); printf(" ~ ");
		printf("V[%3d] =", r+1);
		(r+1 < V.size()) ? print(V[r+1]) : print("+INF"); printf(" ~ ");
		bool ordered = true;
		if (V[r] > e && r>=0)	ordered = false;
		if (V[r+1] <= e && r+1<=V.size())	ordered = false;
		if(!ordered) printf(" \tincorrect search\a\a");
		printf("\n\n");
	}
}

/*************************************************************************
 * 测试: 有序向量的插入
 *************************************************************************/
template <typename T>
void TestOrderedInsertion(Vector<T>& V, int n) {
	while (2 * n > V.size())
	{
		T e = dice((T)n * 2);
		printf("Inserting "); print(e); printf(" ...\n");
		V.insert(V.search(e) + 1, e);
		print(V);
	}
}

/*************************************************************************
 * 测试向量
 *************************************************************************/
#define PRINT(x) {print(x), crc(x), checkOrder(x);}
template <typename T>
void testVector(int testSize)
{
	printf("\n ==== Test %2d. Generate a random vector\n", testID++);
	Vector<T> V;
	for (int i = 0; i < testSize; i++) V.insert(dice(i + 1), dice((T)testSize * 3));	//在[0,3n)选择n个随机插入
	PRINT(V);
	permute(V);	PRINT(V);
	printf("\n ==== Test %2d. Lowpass on\n", testID++);	PRINT(V);
	int i = V.size(); while (0 < --i) { V[i - 1] += V[i]; V[i - 1] >> 1; }	PRINT(V);
	printf("\n ==== Test %2d. Increase \n", testID++);	PRINT(V);
	increase(V);	PRINT(V);
	printf("\n ==== Test %2d. FIND in\n", testID++);	PRINT(V);
	TestFind(V, testSize);	PRINT(V);
}
int main(int argc, char* argv[])
{
	if (2 > argc) { printf("Usage %s <size of test>\a\a\n", argv[0]); return 1; }
	srand((unsigned)time(NULL));	//set random seed
	testVector<int>(atoi(argv[1]));
	return 0;
}

