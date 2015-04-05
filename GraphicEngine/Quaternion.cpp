#include "Quaternion.h"


Quaternion::Quaternion() : a(0), b(0), c(0), d(0)
{
}

Quaternion::Quaternion(float a, float b, float c, float d) : a(a), b(b), c(c), d(d)
{
}


Quaternion::~Quaternion()
{
}

Quaternion Quaternion::conjugate(const Quaternion& q)
{
	return Quaternion(q.a, -q.b, -q.c, -q.d);
}

void Quaternion::operator=(const Quaternion& q)
{
	a = q.a;
	b = q.b;
	c = q.c;
	d = q.d;
}

void Quaternion::conjugate()
{
	b = -b;
	c = -c;
	d = -d;
}

void Quaternion::invert()
{
	float norm = normSquared(*this);
	a = a / norm;
	b = b / norm;
	c = c / norm;
	d = d / norm;
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	return Quaternion(a*q.a - b*q.b - c*q.c - d*q.d,
		b*q.a + a*q.b + c*q.d - d*q.c,
		c*q.a + a*q.c + d*q.b - b*q.d,
		d*q.a + a*q.d + b*q.c - c*q.b);
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(a - q.a, b - q.b, c - q.c, d - q.d);
}

Quaternion Quaternion::operator/(const Quaternion& q) const
{
	return (*this)*invert(q); // equivalent to Q1*invert(Q2)
}

float Quaternion::normSquared(const Quaternion& q)
{
	return q.a*q.a + q.b*q.b + q.c*q.c + q.d*q.d;
}

Quaternion Quaternion::invert(const Quaternion& q)
{
	float normSquared = Quaternion::normSquared(q);
	return Quaternion(q.a / normSquared, -q.b / normSquared, -q.c / normSquared, -q.d / normSquared);
}

std::string Quaternion::toString(const Quaternion& q)
{
	std::stringstream str;
	str << "[ " << q.a << " " << q.b << " " << q.c << " " << q.d << " ]";
	return str.str();
}

Quaternion Quaternion::quat_rotate(float _angle, glm::vec3& _axis)
{
	glm::vec3 axisNorm = glm::normalize(_axis);
	float sinAngle = sinf(_angle / 2.0f);
	float cosAngle = cosf(_angle / 2.0f);

	return Quaternion(cosAngle, sinAngle*axisNorm.x, sinAngle*axisNorm.y, sinAngle*axisNorm.z);

}