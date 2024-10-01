#include <iostream>

#include "Maths/Quaternion.h"

int main()
{
	using namespace Galatea;

	/*Quaternion	q{ 81, 73, 6, 268 };
	Vec3		v{ 39, 3, 18 };

	std::cout << "q: " << q << std::endl;
	q.Normalize();
	std::cout << "q: " << q << std::endl;
	std::cout << "Quat to Euler: " << Maths::QuaternionToEulerAngles(q) << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "Euler to Quat: " << Maths::EulerAnglesToQuaternion(v) << std::endl;
	*/
	Vec3	v{ 3, 6, 69};

	std::cout << "v = " << v << std::endl;
	
	Quaternion q{ Maths::EulerAnglesToQuaternion(v) };

	std::cout << "Euler to quaternion: " << q << std::endl;

	std::cout << "Quaternion to euler: " << Maths::QuaternionToEulerAngles(q) << std::endl;

	/*Quaternion	q { 91, 24, 81, 6 };

	std::cout << "q: " << q << std::endl;

	Mat4	m{ q.ToMatrix() };
	std::cout << "m: " << m << std::endl;
	std::cout << "euler: " << m.ToEulerAngles() << std::endl;
	*/
	return EXIT_SUCCESS;
}