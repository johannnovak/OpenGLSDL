#include "Quaternion.h" // Implemented Class.

/////////////////////////////// PUBLIC ///////////////////////////////////

//============================= LIFECYCLE =======================================

/**************************************************************************
* Name:  Quaternion()
* Description: Default constructor. Sets he default values to 0.
* Inputs: none
**************************************************************************/
Quaternion::Quaternion() : m_a(0), m_b(0), m_c(0), m_d(0)
{
}

/**************************************************************************
* Name:  Quaternion(float32 _a, float32 _b, float32 _c, float32 _d)
* Description: Parametered constructor defining the 4 components of the 4
*						components of a quaternion.
* Inputs:
*				- _a : float32, w component of the Quaternion.
*				- _b : float32, x component of the Quaternion.
*				- _c : float32, y component of the Quaternion.
*				- _d : float32, z component of the Quaternion.
**************************************************************************/
Quaternion::Quaternion(float32 _a, float32 _b, float32 _c, float32 _d) : m_a(_a), m_b(_b), m_c(_c), m_d(_d)
{
}

/**************************************************************************
* Name: ~Quaternion()
* Description: Default destructor.
* Inputs: none
**************************************************************************/
Quaternion::~Quaternion()
{
}

//============================= ATTRIBUTE ACCESSORS =====================================

/**************************************************************************
* Name: set(float32 _a, float32 _b, float32 _c, float32 _d)
* Description: Setter for all 4 components of the quaternions.
* Inputs:
*				- _a : float32, w component of the Quaternion.
*				- _b : float32, x component of the Quaternion.
*				- _c : float32, y component of the Quaternion.
*				- _d : float32, z component of the Quaternion.
* Returns : none
**************************************************************************/
void Quaternion::set(float32 _a, float32 _b, float32 _c, float32 _d)
{
    this->m_a = _a;
    this->m_b = _b;
    this->m_c = _c;
    this->m_d = _d;
}

//============================= OPERATORS ==============================================

/**************************************************************************
* Name:  operator*(const Quaternion& _q) const
* Description: Overloaded * operator for a Quaternion product.
* Inputs:
*				- _q : const Quaternion& to be multiplied by this.
* Returns:
*				- Product of the two Quaternions.
**************************************************************************/
Quaternion Quaternion::operator*(const Quaternion& _q) const
{
    return Quaternion(m_a*_q.m_a - m_b*_q.m_b - m_c*_q.m_c - m_d*_q.m_d,
                      m_b*_q.m_a + m_a*_q.m_b + m_c*_q.m_d - m_d*_q.m_c,
                      m_c*_q.m_a + m_a*_q.m_c + m_d*_q.m_b - m_b*_q.m_d,
                      m_d*_q.m_a + m_a*_q.m_d + m_b*_q.m_c - m_c*_q.m_b);
}

/**************************************************************************
* Name:  operator+(const Quaternion& _q) const
* Description: Overloaded + operator for a Quaternion sum.
* Inputs:
*				- _q : const Quaternion& to be add to this.
* Returns:
*				- Sum of the two Quaternions.
**************************************************************************/
Quaternion Quaternion::operator+(const Quaternion& _q) const
{
    return Quaternion(m_a + _q.m_a, m_b + _q.m_b, m_c + _q.m_c, m_d + _q.m_d);
}

/**************************************************************************
* Name:  operator-(const Quaternion& _q) const
* Description: Overloaded - operator for a Quaternion substraction.
* Inputs:
*				- _q : const Quaternion& to be substracted with.
* Returns:
*				- Substraction of this - _q.
**************************************************************************/
Quaternion Quaternion::operator-(const Quaternion& _q) const
{
    return Quaternion(m_a - _q.m_a, m_b - _q.m_b, m_c - _q.m_c, m_d - _q.m_d);
}

/**************************************************************************
* Name:  operator/(const Quaternion& _q) const
* Description: Overloaded / operator for a Quaternion division.
* Inputs:
*				- _q : const Quaternion& to divide this.
* Returns:
*				- Division of this / _q.
**************************************************************************/
Quaternion Quaternion::operator/(const Quaternion& _q) const
{
    return (*this)*invert(_q); // equivalent to Q1*invert(Q2)
}

/**************************************************************************
* Name:  operator=(const Quaternion& _q) const
* Description: Overloaded = operator for a Quaternion equality.
* Inputs:
*				- _q : const Quaternion& to test the equality with.
* Returns:
*				- True if all 4 components of each are equal.
*				- False otherwise.
**************************************************************************/
void Quaternion::operator=(const Quaternion& q)
{
    m_a = q.m_a;
    m_b = q.m_b;
    m_c = q.m_c;
    m_d = q.m_d;
}

/**************************************************************************
* Name:  toString(const Quaternion& _q)
* Description: toString method of Quaternion that return a String definition
*						of a Quaternion.
* Inputs:
*				- _q : const Quaternion&, Quaternion to print.
* Returns:
*				- std::string containing the string definition of the Quaternion.
**************************************************************************/
std::string Quaternion::toString(const Quaternion& _q)
{
    std::stringstream str;
    str << "[ " << _q.m_a << " " << _q.m_b << " " << _q.m_c << " " << _q.m_d << " ]";
    return str.str();
}

//============================= OPERATIONS ==============================================

/**************************************************************************
* Name: conjugate()
* Description: Returns the conjugate of the Quaternion.
* Inputs: none
* Returns:
*				- Conjugate Quaternion (all components are mulitplied by -1 except w).
**************************************************************************/
void Quaternion::conjugate()
{
    m_b = -m_b;
    m_c = -m_c;
    m_d = -m_d;
}

/* TODO */
void Quaternion::invert()
{
    float32 norm = normSquared(*this);
    m_a = m_a / norm;
    m_b = m_b / norm;
    m_c = m_c / norm;
    m_d = m_d / norm;
}

/**************************************************************************
* Name: rotate(float32 _angle, glm::vec3& _axis)
* Description: Rotation of a Quaternion.
* Inputs:
*				- _angle : float32, angle to rotate with.
*				- _axis  : glm::vec3&, axis to rotate around.
* Returns: none.
**************************************************************************/
void Quaternion::rotate(float32 _angle, glm::vec3& _axis)
{
    Quaternion q = computeRotationQuaternion(_angle, _axis);
    set(m_a*q.m_a - m_b*q.m_b - m_c*q.m_c - m_d*q.m_d,
        m_b*q.m_a + m_a*q.m_b + m_d*q.m_c - m_c*q.m_d,
        m_c*q.m_a + m_a*q.m_c + m_b*q.m_d - m_d*q.m_b,
        m_d*q.m_a + m_a*q.m_d + m_c*q.m_b - m_b*q.m_c);

    normalize();
}

/**************************************************************************
* Name:  normalize()
* Description: Normalize the Quaternion.
* Inputs: none.
* Returns: none.
**************************************************************************/
void Quaternion::normalize()
{
    float32 norm = normSquared(*this);
    set(m_a / norm, m_b / norm, m_c / norm, m_d / norm);
}

/**************************************************************************
* Name: conjugate(const Quaternion& _q)
* Description: Returns the conjugate of the Quaternion passed in parameter.
* Inputs:
*				- _q : const Quaternion&, Quaternion to get the conjugate from.
* Returns:
*				- Conjugate Quaternion (all components are mulitplied by -1 except w).
**************************************************************************/
Quaternion Quaternion::conjugate(const Quaternion& q)
{
    return Quaternion(q.m_a, -q.m_b, -q.m_c, -q.m_d);
}

/* TODO */
Quaternion Quaternion::invert(const Quaternion& _q)
{
    float32 normSquared = Quaternion::normSquared(_q);
    return Quaternion(_q.m_a / normSquared, -_q.m_b / normSquared, -_q.m_c / normSquared, -_q.m_d / normSquared);
}

/**************************************************************************
* Name: normSquared(const Quaternion& _q)
* Description: Returns the squared norm of the quaternion.
* Inputs:
*				- _q : const Quaternion&, quaternion from which the quared norm is
*							returned.
* Returns:
*				- float32 reprensenting the squared norm of the quaternion.
**************************************************************************/
float32 Quaternion::normSquared(const Quaternion& _q)
{
    return _q.m_a*_q.m_a + _q.m_b*_q.m_b + _q.m_c*_q.m_c + _q.m_d*_q.m_d;
}

/**************************************************************************
* Name: computeRotationQuaternion(float32 _angle, glm::vec3& _axis)
* Description: Creates a Quaternion associated with a rotation composed
*						from the angle '_angle' around the axis '_axis'.
* Inputs:
*				- _angle : angle the returned Quaternion is associated with.
*				- _axis  : axis around which the returned Quaternion rotates.
* Returns:
*				- Quaternion rotation around '_axis' with an angle '_angle'.
**************************************************************************/
Quaternion Quaternion::computeRotationQuaternion(float32 _angle, glm::vec3& _axis)
{
    glm::vec3 axisNorm = glm::normalize(_axis);
    float32 halfAngle = _angle / 2.0f;
    float32 sinAngle = sinf(halfAngle);
    return Quaternion(cosf(halfAngle), sinAngle*_axis.x, sinAngle*_axis.y, sinAngle*_axis.z);
}

/**************************************************************************
* Name: computeRotationQuaternion(float32 _angle, glm::vec3& _axis, Quaternion& _q)
* Description: Sets the Quaternion _q rotation as above.
* Inputs:
*				- _angle : angle the returned Quaternion is associated with.
*				- _axis  : axis around which the returned Quaternion rotates.
*				- _q     : Quaternion whose components are set by the rotation defined
*								by '_angle' and '_axis'.
* Returns: none
**************************************************************************/
void Quaternion::computeRotationQuaternion(float32 _angle, glm::vec3& _axis, Quaternion& _q)
{
    glm::vec3 axisNorm = glm::normalize(_axis);
    float32 halfAngle = _angle / 2.0f;
    float32 sinAngle = sin(halfAngle);
    _q.set(cosf(halfAngle), sinAngle*_axis.x, sinAngle*_axis.y, sinAngle*_axis.z);
}

/**************************************************************************
* Name:  quat_rotate(float32 _angle, glm::vec3& _axis)
* Description: Creates a Quaternion associated with a rotation composed
*						from the angle '_angle' around the axis '_axis'.
* Inputs:
*				- _angle : angle the returned Quaternion is associated with.
*				- _axis  : axis around which the returned Quaternion rotates.
* Returns:
*				- Quaternion rotation around '_axis' with an angle '_angle'.
**************************************************************************/
Quaternion Quaternion::quat_rotate(float32 _angle, glm::vec3& _axis)
{
    glm::vec3 axisNorm = glm::normalize(_axis);
    float32 sinAngle = sinf(_angle / 2.0f);
    float32 cosAngle = cosf(_angle / 2.0f);

    return Quaternion(cosAngle, sinAngle*axisNorm.x, sinAngle*axisNorm.y, sinAngle*axisNorm.z);

}


/**************************************************************************
* Name:  computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz)
* Description: Creates a Quaternion associated with three components of
*						a rotation (along x axis, along y axis and along z axis).
* Inputs:
*				- _rx : float32, angle of the rotation along the x axis.
*				- _ry : float32, angle of the rotation along the y axis.
*				- _rz : float32, angle of the rotation along the z axis.
* Returns:
*				- Quaternion associated with the three angles defining a 3D rotation.
**************************************************************************/
Quaternion Quaternion::computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz)
{
    float32 halfrx = _rx / 2.0f;
    float32 halfry = _ry / 2.0f;
    float32 halfrz = _rz / 2.0f;

    float32 cosrx = cosf(halfrx);
    float32 sinrx = sinf(halfrx);
    float32 cosry = cosf(halfry);
    float32 sinry = sinf(halfry);
    float32 cosrz = cosf(halfrz);
    float32 sinrz = sinf(halfrz);

    return Quaternion(cosrx*cosry*cosrz - sinrx*sinry*sinrz,
                      cosry*cosrz*sinrx + cosrx*sinry*sinrz,
                      cosrx*cosrz*sinry - cosry*sinrx*sinrz,
                      cosrx*cosry*sinrz + cosrz*sinrx*sinry);
}

/**************************************************************************
* Name:  computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz, Quaternion& _q)
* Description: Sets the Quaternion _q components as above.
* Inputs:
*				- _rx : float32, angle of the rotation along the x axis.
*				- _ry : float32, angle of the rotation along the y axis.
*				- _rz : float32, angle of the rotation along the z axis.
*				- _q     : Quaternion whose components are set by the rotation defined
*								by '_angle' and '_axis'.
* Returns:
*				- Quaternion associated with the three angles defining a 3D rotation.
**************************************************************************/
void Quaternion::computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz, Quaternion& _q)
{
    float32 halfrx = _rx / 2.0f;
    float32 halfry = _ry / 2.0f;
    float32 halfrz = _rz / 2.0f;

    float32 cosrx = cosf(halfrx);
    float32 sinrx = sinf(halfrx);
    float32 cosry = cosf(halfry);
    float32 sinry = sinf(halfry);
    float32 cosrz = cosf(halfrz);
    float32 sinrz = sinf(halfrz);

    _q.set(cosrx*cosry*cosrz - sinrx*sinry*sinrz,
             cosry*cosrz*sinrx + cosrx*sinry*sinrz,
             cosrx*cosrz*sinry - cosry*sinrx*sinrz,
             cosrx*cosry*sinrz + cosrz*sinrx*sinry);
}
