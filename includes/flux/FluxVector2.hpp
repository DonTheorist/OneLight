#ifndef FLUX_VECTOR2_H
#define FLUX_VECTOR2_H
#include <iostream>
#include <math.h>

namespace Flux
{
    /** A class representing a 2D vector (in the x, y directions).
     @see
        Vector3
     */
    class Vector2
    {
        public:
            /** Default constructor. */
            Vector2();

            /** A constructor for specifying x and y. */
            Vector2(float x, float y);

            /** Default destructor. */
            ~Vector2();

            /** Adds two Vector2 */
            Vector2& operator+= (const Vector2 &v);

            /** Adds a scalar value to x and y */
            Vector2& operator+= (const float &s);

            /** Subtracts two Vector2 */
            Vector2& operator-= (const Vector2 &v);

            /** Subtracts a scalar value from x and y */
            Vector2& operator-= (const float &s);

            /** Multiply x and y by a scalar value */
            Vector2& operator*= (const float &s);

            /** Divide x and y by a scalar value */
            Vector2& operator/= (const float &s);

            /** Adds two Vector2 */
            Vector2 operator+ (const Vector2 &v) const;

            /** Adds a scalar value to x and y */
            Vector2 operator+ (const float &s) const;

            /** Subtracts two Vector2 */
            Vector2 operator- (const Vector2 &v) const;

            /** Subtracts a scalar value to x and y */
            Vector2 operator- (const float &s) const;

            /** Unary operator, negates both x and y */
            Vector2 operator- () const;

            /** Multiply x and y by a scalar value */
            Vector2 operator* (const float &s) const;

            /** Divide x and y by a scalar value */
            Vector2 operator/ (const float &s) const;

            /** Checks if two Vector2 are equal i.e (x == x & y == y) */
            bool operator==(const Vector2 &v) const;

            /** Checks if two Vector2 are not equal i.e (x != x | y != y) */
            bool operator!=(const Vector2 &v) const;

            /** Write the vector to a stream. Handy for debugging. */
            friend std::ostream& operator<<(std::ostream &out, const Vector2 &v);

            /** Returns the distance between this Vector2 and another. */
            float distance(const Vector2 &v) const;

            /** static method for calculating the distance between two Vector2 */
            static float distance(const Vector2 &v1, const Vector2 &v2);

            /** Vector2(1, 1) */
            static const Vector2 UNIT;
            /** Vector2(0, 0) */
            static const Vector2 ZERO;
            /** Vector2(1, 0) */
            static const Vector2 UNITX;
            /** Vector2(0, 1) */
            static const Vector2 UNITY;

            /** x and y component of the vector.
             * Public for easy access.
             */
            float x, y;
    };
}
#endif

