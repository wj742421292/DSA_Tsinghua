#pragma once

template <typename T>
struct Crc {
	T& c;
	Crc(T& crc) :c(crc) {};
	virtual void operator()(T& e) { c += e; };
};
