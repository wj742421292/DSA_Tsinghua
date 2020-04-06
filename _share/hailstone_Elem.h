#pragma once

template <typename T>
struct Hailstone {
	virtual void operator()(T& e) {	//按照Hailstone规则转化一个T类对象
		int step = 0;
		while (1 != e) {	//按奇偶逐步转换直至为1
			(e % 2) ? e = 3 * e + 1 : e /= 2;
			step++;
		}
		e = step;	//返回转换所经步数
	}
};
