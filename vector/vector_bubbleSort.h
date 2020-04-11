/******************************************************************************************
 * Data Structures in C++
 * treat the bubble sort as the iteration of scan & swap
 * Gene.W
 * Improved the possibility to avoid the time complecity of o(n^2)
 * Copyright (c) 2018-. All rights reserved.
 ******************************************************************************************/

#pragma once
#include "vector_bubble.h"

template <typename T>
void
bubbleSortA(T* A, Rank lo, Rank hi) {   //assert: 0<=lo<hi<=size
    while (lo < --hi) {
        for (Rank i = lo; i < hi; i++)
        {
            if (A[i] > A[i + 1])
                swap(A[i], A[i + 1]);
        }
    }
}
//bubble Sort end in advance
template <typename T>
void
bubbleSortB(T* A, Rank lo, Rank hi)
{
    for (bool sorted = false; sorted = !sorted;)
        for (Rank i = lo; i < hi - 1; i++)
            if (A[i] > A[i + 1])
                swap(A[i], A[i + 1]), sorted = false;
}
//bubble Sort jump
template <typename T>
void
bubbleSortC(T* A, Rank lo, Rank hi)
{
    for (Rank last = --hi; lo < hi; hi = last) {
        for (Rank i = last = lo; i < hi; i++)
            if (A[i] > A[i + 1])
                swap(A[last = i], A[i + 1]);
    }
}

//bubble sort original version
template <typename T>
void
bubbleSortOld(T* A, Rank lo, Rank hi) {
    while (!bubbleFast(A, lo, hi--));
}
