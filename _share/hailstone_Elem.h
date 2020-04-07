#pragma once

template <typename T>
struct Hailstone {
	virtual void operator()(T& e) {	//����Hailstone����ת��һ��T�����
		int step = 0;
		while (1 != e) {	//����ż��ת��ֱ��Ϊ1
			(e % 2) ? e = 3 * e + 1 : e /= 2;
			step++;
		}
		e = step;	//����ת����������
	}
};
