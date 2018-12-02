#pragma once

#include <iostream>
namespace Vector {

	template<class T>
	class vecInterface {
	public:
		virtual void Print() = 0;
		virtual ~vecInterface() = default;
	};

	template<class T>
	std::ostream &operator<<(std::ostream &os, vecInterface<T> &value) {
		value.Print();
		return os;
	}

}