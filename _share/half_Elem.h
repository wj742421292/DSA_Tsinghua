#pragma once

template <typename T>
struct Half {
	virtual void operator()(T& e) { e /= 2; }
};
