#pragma once

#include <typeinfo.h>

/*****************************************************************************
 * �б�, �����Ƚṹ�ڵĽڵ��п��Դ�Ż������ͻ�������
 * ����Ч�ʵĿ���, ���ں�һ���ͨ��ֻ��������ָ��
 * ���, ������ṹ����֮ǰ, ��Ҫ�����ͷ���Щ��Ա������ռ�Ŀռ�
 * �˴�, ����C++ ��ƫ�ػ��������������������, ������Ӧ����
 *
 *****************************************************************************/

template <typename T>
struct Cleaner {
    static void clean(T x) { //�൱�ڵݹ��
#ifdef _DEBUG
        static int n = 0;
        if (7 > strlen(typeid(T).name())) { //��������һ�ź���, ֻ�����������
            printf("\t<%s>[%d]=", typeid(T).name(), ++n);
            print(x);
            printf(" purged\n");
        }
#endif
    }
};

template <typename T> struct Cleaner<T*> {
    static void clean(T* x) {
        if (x) { delete x; }
#ifdef _DEBUG
        static int n = 0;
        printf("\t<%s>[%d] released\n", typeid(T*).name(), ++n);
#endif
    }
};

template <typename T>
void release(T x) { Cleaner<T>::clean(x); }