#include <iostream>
#include "src/v3Header.h"
#include "src/v2Header.h"
#include "src/vector.h"
using namespace Vector;

int main() {
	Vec3<int> vec3D;
	std::cin >> vec3D;
	try {
		vec3D /= 0;
	}
	catch (DivideByZero& e) {
		std::cout << "An divide by zero ex occured in " << e.what() << "\nThe culprit is :" << e.getCulprit() << '\n';
	}
	catch (...) {
		std::cout << "Wut??!!";
	}

	std::cout << vec3D;
	system("pause");
	return 0;
}