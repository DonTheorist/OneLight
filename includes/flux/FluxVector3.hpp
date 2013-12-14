#ifndef FLUX_VECTOR3_H
#define FLUX_VECTOR3_H

#include "FluxVector2.hpp"

#include <iostream>
#include <math.h>

namespace Flux
{
    /** A class representing a 3D vector (in the x, y, z directions).
     * @see
     *  Vector2
     */
    class Vector3
    {
        public:
            /** Default constructor. */
            Vector3();

            /** Constructor taking a Vector2 as the x,y components and supplying the z. */
            Vector3(const Vector2 &v, float z);

            /** Constructor with supplied x, y and z components. */
            Vector3(float x, float y, float z);

            /** Default destructor. */
            ~Vector3();

            Vector3& operator+= (const Vector3 &v);
            Vector3& operator+= (const float &f);
            Vector3& operator-= (const Vector3 &v);
            Vector3& operator-= (const float &f);
            Vector3 operator+ (const Vector3 &v) const;
            Vector3 operator+ (const float &f) const;
            Vector3 operator- (const Vector3 &v) const;
            Vector3 operator- (const float &f) const;
            Vector3 operator- () const;

            /** Checks if two Vector3's are equal. */
            bool operator== (const Vector3 &v) const;

            /** Checks if two Vector3's are not equal. */
            bool operator!= (const Vector3 &v) const;

            friend std::ostream& operator<<(std::ostream &out, const Vector3 &v);

            /** Retruns the cross product of this Vectro3 with another. */
            void cross(const Vector3 &v);

            /** Calulcatue the cross product of two Vector3's. */
            static Vector3 cross(const Vector3 &v1, const Vector3 &v2);

            /** Returns the magnitude of this Vector3. */
            float magnitude() const;

            /** Returns the dot product of this Vector3 with another. */
            float dot(const Vector3 &v) const;

            /** Normalises this Vector3. */
            void normalise();

            /** Returns a new Vector3 which is the normalised input. */
            static Vector3 normalise(const Vector3 &v);

            /** Vector3(1, 1, 1). */
            static const Vector3 UNIT;

            /** Vector3(0, 0, 0). */
            static const Vector3 ZERO;

            /** Vector3(1, 0, 0). */
            static const Vector3 UNITX;

            /** Vector3(0, 1, 0). */
            static const Vector3 UNITY;

            /** Vector3(0, 0, 1). */
            static const Vector3 UNITZ;

            /** Components, made public for easy access. */
            float x, y, z;
    };
}

#endif

