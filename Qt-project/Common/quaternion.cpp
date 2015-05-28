#include "quaternion.h"

using namespace std;

Quaternion::Quaternion(float32 _w,float32 _x,float32 _y,float32 _z)
{
    m_w = _w;
    m_x = _x;
    m_y = _y;
    m_z = _z;
}

Quaternion Quaternion::operator *(const Quaternion& _q) const
{
    float32 newW(0), newX(0), newY(0), newZ(0);

    newW =      m_w * _q.m_w
            +   m_x * _q.m_x * (-1)
            +   m_y * _q.m_y * (-1)
            +   m_z * _q.m_z * (-1);

    newX =      m_w * _q.m_x
            +   m_x * _q.m_w
            +   m_y * _q.m_z
            +   m_z * _q.m_y * (-1);

    newY =      m_w * _q.m_y
            +   m_x * _q.m_z * (-1)
            +   m_y * _q.m_w
            +   m_z * _q.m_x;

    newZ =      m_w * _q.m_z
            +   m_x * _q.m_y
            +   m_y * _q.m_x * (-1)
            +   m_z * _q.m_w;

    return Quaternion(newW, newX, newY, newZ);
}

Vec3 Quaternion::operator*(const Vec3& _vec)
{
    Quaternion conjugate = this->conjugate();
    Quaternion vecQuaternion(0, _vec.m_x, _vec.m_y, _vec.m_z);

    Quaternion result = conjugate * vecQuaternion * (*this);

    return Vec3(result.m_x, result.m_y, result.m_z);
}

Quaternion Quaternion::operator *(float32 _f) const
{
    return Quaternion(_f*m_w,_f*m_x,_f*m_y,_f*m_z);
}

Quaternion Quaternion::operator +(const Quaternion& _q)
{
    return Quaternion(m_w+_q.m_w,m_x+_q.m_x,m_y+_q.m_y,m_z+_q.m_z);
}

float32 Quaternion::dot(const Quaternion &_q) const
{
    return (m_w*_q.m_w + m_x*_q.m_x + m_y*_q.m_y + m_z*_q.m_z);
}

void Quaternion::set(float32 _x, float32 _y, float32 _z)
{
    m_x = _x;
    m_y = _y;
    m_z = _z;
}

void Quaternion::setFromAxis(float32 _angle, float32 _ax, float32 _ay, float32 _az)
{
    m_w = cosf(_angle/2);
    m_x = sinf(_angle/2) * _ax;
    m_y = sinf(_angle/2) * _ay;
    m_z = sinf(_angle/2) * _az;
}

Quaternion Quaternion::slerp(const Quaternion &_q0, const Quaternion &_q1, float32 _t)
{
    float angle = acos(_q0.dot(_q1));
    return Quaternion(      (_q0 * sin((1-_t) * angle) + _q1 * sin(_t * angle))
                           *(1/sin(angle))
                );
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(m_w, -m_x, -m_y, -m_z);
}

void Quaternion::normalize()
{
    float32 n = norme();

    m_w /= n;
    m_x /= n;
    m_y /= n;
    m_z /= n;
}

float32 Quaternion::norme()
{
    return sqrt((m_w*m_w)+(m_x*m_x)+(m_y*m_y)+(m_z*m_z));
}

void Quaternion::setRotationMatrix(float32* _mat)
{
    m_w = sqrt(1 + _mat[0] + _mat[1 + 4] + _mat[2 + 8])/2;
    m_x = (_mat[1+8] - _mat[2 + 4]) / (4*m_w);
    m_y = (_mat[2] - _mat[8]) / (4*m_w);
    m_z = (_mat[4] - _mat[1]) / (4*m_w);
}

ostream& operator <<(ostream& _o, const Quaternion& _q)
{
    _o << _q.m_w;

    if(_q.m_x > 0)
        _o << " + ";
    else
        _o << " ";
    _o << _q.m_x << "i";

    if(_q.m_y > 0)
        _o << " + ";
    else
        _o << " ";
    _o << _q.m_y << "j";

    if(_q.m_z > 0)
        _o << " + ";
    else
        _o << " ";
    _o << _q.m_z << "k";

    _o << endl;

    return _o;
}
