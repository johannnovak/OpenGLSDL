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
	void set(float a, float b, float c, float d);

	Quaternion operator*(const Quaternion& q) const;
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-(const Quaternion& q) const;
	Quaternion operator/(const Quaternion& q) const;
	void operator=(const Quaternion& q);

	void conjugate();
	void invert();

	void rotate(float _angle, glm::vec3& _axis);

	static Quaternion conjugate(const Quaternion& q);
	static Quaternion invert(const Quaternion& q);

	static float normSquared(const Quaternion& q);

	static std::string toString(const Quaternion& q);

	static Quaternion computeRotationQuaternion(float _angle, glm::vec3& _axis);
	static Quaternion computeRotationQuaternion(float _rx, float _ry, float _rz);

	static void computeRotationQuaternion(float _angle, glm::vec3& _axis, Quaternion& _out);
	static void computeRotationQuaternion(float _rx, float _ry, float _rz, Quaternion& _out);

	explicit operator glm::mat4() const
	{
		return glm::mat4(
			1 - 2*c*c - 2*d*d, 2*b*c - 2*d*a, 2*b*d + 2*c*a, 0,
			2*b*c + 2*d*a, 1 - 2*b*b - 2*d*d, 2*c*d - 2*b*a, 0,
			2*b*d - 2*c*a, 2*c*d + 2*b*a, 1 - 2*b*b - 2*c*c, 0,
			0, 0, 0, 1);
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