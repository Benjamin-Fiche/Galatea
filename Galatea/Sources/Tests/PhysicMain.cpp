#include <iostream>

#include "Physic/Transform.h"

int main()
{
	using namespace Galatea;

	Transform	trs;
	trs.Display();
	trs = Transform( Vec3{ 1, 2, 3 }, Vec3{ 4, 5, 6 }, Vec3{ 7, 8, 9 } );
	std::cout << trs << std::endl;
	Transform	copy{ trs };
	std::cout << "copy: " << copy << std::endl;
	Transform	copy2;
	std::cout << "copy2: " << copy2 << std::endl;
	copy2 = trs;
	std::cout << "copy2: " << copy2 << std::endl;

	trs.Reset();
	std::cout << "trs: " << trs << std::endl;
	trs.Translate({ 1, 1, 1 });
	std::cout << "trs: " << trs << std::endl;
	trs.Rotate({ 90, 90, 0 });
	std::cout << "trs: " << trs << std::endl;
	trs.Scale({ 2, 2, 2 });
	std::cout << "trs: " << trs << std::endl;
}