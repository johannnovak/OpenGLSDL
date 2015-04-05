#pragma once

#include <iostream>
#include <sstream>
#include <glm\glm.hpp>

class Quaternion
{
public:
	Quaternion();
	Quaternion(float a, float b, float c, float d);
	~Quaternion();

public:
	Quaternion operator*(const Quaternion& q) const;
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-(const Quaternion& q) const;
	Quaternion operator/(const Quaternion& q) const;
	void operator=(const Quaternion& q);

	void conjugate();
	void invert();

	static Quaternion conjugate(const Quaternion& q);
	static Quaternion invert(const Quaternion& q);

	static float normSquared(const Quaternion& q);

	static std::string toString(const Quaternion& q);

	explicit operator glm::mat4() const
	{
		return glm::mat4(
			a, -b, -c, -d,
			b, a, -d, c,
			c, d, a, -b,
			d, -c, b, a);
	};

	friend std::ostream& operator<<(std::ostream& out, const Quaternion& q)
	{
		out << "[ " << q.a << " " << q.b << " " << q.c << " " << q.d << " ]";
		return out;
	};

	static Quaternion quat_rotate(float _angle, glm::vec3& _axis);

public:
	float a;
	float b;
	float c;
	float d;
};