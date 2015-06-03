#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Types.h"

#include "glm/glm.hpp"
#include <iostream>
#include <sstream>

/**************************************************************************
* Class: Quaternion
* Description: Class designed to implement the concept of mathematical
*						quaternions.
*
**************************************************************************/
class Quaternion
{
/////////////////////////////// PUBLIC ///////////////////////////////////
    public:

         /* w component of the quaternion. */
         float32 m_a;

         /* x component of the quaternion. */
         float32 m_b;

         /* y component of the quaternion. */
         float32 m_c;

         /* z component of the quaternion. */
         float32 m_d;

/////////////////////////////// PUBLIC ///////////////////////////////////
    public:
    //============================= LIFECYCLE =======================================

        /**************************************************************************
        * Name:  Quaternion()
        * Description: Default constructor.
        * Inputs: none
        **************************************************************************/
        Quaternion();

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
        Quaternion(float32 _a, float32 _b, float32 _c, float32 _d);

        /**************************************************************************
        * Name: ~Quaternion()
        * Description: Default destructor.
        * Inputs: none
        **************************************************************************/
        ~Quaternion();

    //============================= ATTRIBUTE ACCESSORS =====================================

        /**************************************************************************
        * Name: set(float32 _a, float32 _b, float32 _c, float32 _d)
        * Description: Setter for all 4 components of the quaternions.
        * Inputs:
        *				- _a : float32, w component of the Quaternion.
        *				- _b : float32, x component of the Quaternion.
        *				- _c : float32, y component of the Quaternion.
        *				- _d : float32, z component of the Quaternion.
        *	 Returns : none
        **************************************************************************/
        void set(float32 _a, float32 _b, float32 _c, float32 _d);

    //============================= OPERATORS ==============================================

        /**************************************************************************
        * Name:  operator*(const Quaternion& _q) const
        * Description: Overloaded * operator for a Quaternion product.
        * Inputs:
        *				- _q : const Quaternion& to be multiplied by this.
        * Returns:
        *				- Product of the two Quaternions.
        **************************************************************************/
        Quaternion operator*(const Quaternion& _q) const;

        /**************************************************************************
        * Name:  operator+(const Quaternion& _q) const
        * Description: Overloaded + operator for a Quaternion sum.
        * Inputs:
        *				- _q : const Quaternion& to be add to this.
        * Returns:
        *				- Sum of the two Quaternions.
        **************************************************************************/
        Quaternion operator+(const Quaternion& _q) const;

        /**************************************************************************
        * Name:  operator-(const Quaternion& _q) const
        * Description: Overloaded - operator for a Quaternion substraction.
        * Inputs:
        *				- _q : const Quaternion& to be substracted with.
        * Returns:
        *				- Substraction of this - _q.
        **************************************************************************/
        Quaternion operator-(const Quaternion& _q) const;

        /**************************************************************************
        * Name:  operator/(const Quaternion& _q) const
        * Description: Overloaded / operator for a Quaternion division.
        * Inputs:
        *				- _q : const Quaternion& to divide this.
        * Returns:
        *				- Division of this / _q.
        **************************************************************************/
        Quaternion operator/(const Quaternion& _q) const;

        /**************************************************************************
        * Name:  operator=(const Quaternion& _q) const
        * Description: Overloaded = operator for a Quaternion equality.
        * Inputs:
        *				- _q : const Quaternion& to test the equality with.
        * Returns:
        *				- True if all 4 components of each are equal.
        *				- False otherwise.
        **************************************************************************/
        void operator=(const Quaternion& _q);

        /**************************************************************************
        * Name:  operator glm::mat4() const
        * Description: Overloaded conversion operator to glm::mat4.
        * Inputs: none
        * Returns:
        *				- glm::mat4 Rotation matrix associated with the 'this' Quaternion.
        **************************************************************************/
        explicit operator glm::mat4() const
        {
            return glm::mat4(
                        1 - 2*m_c*m_c - 2*m_d*m_d, 2*m_b*m_c - 2*m_d*m_a, 2*m_b*m_d + 2*m_c*m_a, 0,
                        2*m_b*m_c + 2*m_d*m_a, 1 - 2*m_b*m_b - 2*m_d*m_d, 2*m_c*m_d - 2*m_b*m_a, 0,
                        2*m_b*m_d - 2*m_c*m_a, 2*m_c*m_d + 2*m_b*m_a, 1 - 2*m_b*m_b - 2*m_c*m_c, 0,
                        0, 0, 0, 1);
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
        static std::string toString(const Quaternion& _q);

        /**************************************************************************
        * Name: operator<<(std::ostream& out, const Quaternion& _q)
        * Description: Overloaded << operator printing the Quaternion.
        * Inputs:
        *				- _out : std::ostream&, stream where to print the Quaternion components.
        *				- _q   : const Quaternion&, Quaternion to print.
        * Returns:
        *				- std::string containing the string definition of the Quaternion.
        **************************************************************************/
        friend std::ostream& operator<<(std::ostream& _out, const Quaternion& _q)
        {
            _out << "[ " << _q.m_a << " " << _q.m_b << " " << _q.m_c << " " << _q.m_d << " ]";
            return _out;
        }

    //============================= OPERATIONS ==============================================

        /**************************************************************************
        * Name: conjugate()
        * Description: Returns the conjugate of the Quaternion.
        * Inputs: none
        * Returns:
        *				- Conjugate Quaternion (all components are mulitplied by -1 except w).
        **************************************************************************/
        void conjugate();

        /* TODO */
        void invert();

        /**************************************************************************
        * Name: rotate(float32 _angle, glm::vec3& _axis)
        * Description: Rotation of a Quaternion.
        * Inputs:
        *				- _angle : float32, angle to rotate with.
        *				- _axis  : glm::vec3&, axis to rotate around.
        * Returns: none.
        **************************************************************************/
        void rotate(float32 _angle, glm::vec3& _axis);

        /**************************************************************************
        * Name:  normalize()
        * Description: Normalize the Quaternion.
        * Inputs: none.
        * Returns: none.
        **************************************************************************/
        void normalize();

        /**************************************************************************
        * Name: conjugate(const Quaternion& _q)
        * Description: Returns the conjugate of the Quaternion passed in parameter.
        * Inputs:
        *				- _q : const Quaternion&, Quaternion to get the conjugate from.
        * Returns:
        *				- Conjugate Quaternion (all components are mulitplied by -1 except w).
        **************************************************************************/
        static Quaternion conjugate(const Quaternion& _q);

        /* TODO */
        static Quaternion invert(const Quaternion& _q);

        /**************************************************************************
        * Name: normSquared(const Quaternion& _q)
        * Description: Returns the squared norm of the quaternion.
        * Inputs:
        *				- _q : const Quaternion&, quaternion from which the quared norm is
        *							returned.
        * Returns:
        *				- float32 reprensenting the squared norm of the quaternion.
        **************************************************************************/
        static float32 normSquared(const Quaternion& _q);

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
        static Quaternion computeRotationQuaternion(float32 _angle, glm::vec3& _axis);

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
        static void computeRotationQuaternion(float32 _angle, glm::vec3& _axis, Quaternion& _q);

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
        static Quaternion quat_rotate(float32 _angle, glm::vec3& _axis);

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
        static Quaternion computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz);

        /**************************************************************************
        * Name:  computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz, Quaternion& _q)
        * Description: Sets the Quaternion _q components as above.
        * Inputs:
        *				- _rx : float32, angle of the rotation along the x axis.
        *				- _ry : float32, angle of the rotation along the y axis.
        *				- _rz : float32, angle of the rotation along the z axis.
        *				- _q  : Quaternion whose components are set by the rotation defined
        *								by '_angle' and '_axis'.
        * Returns:
        *				- Quaternion associated with the three angles defining a 3D rotation.
        **************************************************************************/
        static void computeRotationQuaternion(float32 _rx, float32 _ry, float32 _rz, Quaternion& _q);
};

#endif // __QUATERNION_H__
